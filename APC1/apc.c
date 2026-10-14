/*
 * Name: C Manu, date:
 * Project Title: Arbitrary Precision Calculator (APC)
 *
 * This file has the basic building blocks for the project -
 * inserting/removing nodes from the digit list, printing it out,
 * and comparing two numbers.
 */

#include <stdio.h>
#include <stdlib.h>
#include "apc.h"


// Adds a new digit to the end of the list (used when we're reading
// digits left to right from the input string).
void insertlast(n **head, n **tail, int data)
{
    n *new = malloc(sizeof(n));   // grab memory for the new node
    if (new == NULL)
    {
        printf("No nodes available\n");   // ran out of memory, bail out
        return;
    }

    new->data = data;    // store the digit
    new->nxt = NULL;      // this will be the last node for now

    if (*head == NULL && *tail == NULL)   // list is currently empty
    {
        new->prev = NULL;
        *head = *tail = new;   // head and tail both point here
    }
    else
    {
        new->prev = *tail;      // link back to whatever was the last node
        (*tail)->nxt = new;     // old tail now points to the new node
        *tail = new;             // and the new node becomes the tail
    }
}

// Adds a new digit to the front of the list. We use this a lot while
// building results, since we usually compute digits from the least
// significant end and need to push them to the front to keep the
// number in the right order.
void insertfirst(n **head, n **tail, int data)
{
    n *new = malloc(sizeof(n));   // grab memory for the new node
    if (new == NULL)
    {
        printf("No nodes available\n");   // ran out of memory, bail out
        return;
    }

    new->data = data;    // store the digit
    new->prev = NULL;     // this will be the first node for now

    if (*head == NULL && *tail == NULL)   // list is currently empty
    {
        new->nxt = NULL;
        *head = *tail = new;
    }
    else
    {
        new->nxt = *head;        // new node points forward to old head
        (*head)->prev = new;     // old head points back to the new node
        *head = new;               // new node becomes the head
    }
}

// Walks through the list and prints every digit, so we get the
// number back out as normal text on the screen.
void printlist(n *head)
{
    while (head)
    {
        printf("%d", head->data);
        head = head->nxt;
    }
    printf("\n");
}

// Figures out which of two numbers is bigger just by looking at
// the linked lists (no converting to int, since the whole point
// is these numbers might not even fit in one).
int list_compare(n *list1, n *list2)
{
    int list1_count = 0, list2_count = 0;
    n *temp1 = list1;
    n *temp2 = list2;

    // first pass: just count how many digits each number has
    while (temp1)
    {
        list1_count++;
        temp1 = temp1->nxt;
    }

    while (temp2)
    {
        list2_count++;
        temp2 = temp2->nxt;
    }

    // more digits automatically means a bigger number (assuming no
    // leading zeros, which we strip out elsewhere)
    if (list1_count > list2_count)
        return 1;
    else if (list1_count < list2_count)
        return -1;
    else
    {
        // same number of digits, so we have to compare them one by one
        temp1 = list1;
        temp2 = list2;
        while (temp1 && temp2)
        {
            if (temp1->data > temp2->data)
                return 1;
            else if (temp1->data < temp2->data)
                return -1;
            temp1 = temp1->nxt;
            temp2 = temp2->nxt;
        }
        return 0;   // every digit matched, so the numbers are equal
    }
}

// Frees every node in the list once we're finished with it, so we're
// not leaking memory every time we build a temporary result.
int deletelist(n **headR, n **tailR)
{
    n *temp = *headR;
    while (temp != NULL)
    {
        n *next = temp->nxt;   // hang on to the next node before we free this one
        free(temp);
        temp = next;
    }
    *headR = NULL;
    *tailR = NULL;
    return 0;
}
