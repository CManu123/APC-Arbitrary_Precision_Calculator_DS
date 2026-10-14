/*
 * Name: C Manu, date:
 * Project Title: Arbitrary Precision Calculator (APC)
 *
 * This header just holds the node definition for our digit list
 * and the prototypes for every function used across the project.
 */

#ifndef APC_H
#define APC_H

// Each node holds one digit of a number. We link them together
// both ways (prev/nxt) so we can walk the number from either end,
// which makes carrying/borrowing a lot easier to code.
typedef struct node
{
    int data;          // the actual digit (0-9)
    struct node *prev;  // link to the previous digit
    struct node *nxt;   // link to the next digit
} n;


// All the list + arithmetic functions we use in main.c
void insertlast(n **head, n **tail, int data);   // add a digit at the end of the list
void insertfirst(n **head, n **tail, int data);  // add a digit at the front of the list
void printlist(n *head);                         // print out every digit in order
void addnumber(n *head1, n *tail1, n *head2, n *tail2, n **headR, n **tailR);   // add two numbers
int list_compare(n *list1, n *list2);            // check which of two numbers is bigger
void subnumber(n *head1, n *tail1, n *head2, n *tail2, n **headR, n **tailR);   // subtract one number from another
void mulnumber(n *head1, n *tail1, n *head2, n *tail2, n **headR, n **tailR);   // multiply two numbers
int deletelist(n **headR, n **tailR);            // free up a list once we're done with it
void divnumber(n *head1, n *tail1, n *head2, n *tail2, n **headQ, n **tailQ, n **headRem, n **tailRem); // divide list1 by list2

#endif
