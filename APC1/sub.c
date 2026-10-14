/*
 * Name: C Manu, date:
 * Project Title: Arbitrary Precision Calculator (APC)
 *
 * Handles subtraction between two digit lists. main.c already makes
 * sure the bigger number is passed in as list1, so we don't have to
 * worry about the result going negative here.
 */

#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

void subnumber(n *head1, n *tail1, n *head2, n *tail2, n **headR, n **tailR)
{
    int borrow = 0;     // tracks whether we need to borrow from the next column
    n *temp1 = tail1;    // start from the least significant digit of each number
    n *temp2 = tail2;

    while (temp1 != NULL || temp2 != NULL)
    {
        int data = -borrow;   // account for anything we borrowed last round

        if (temp1 != NULL && temp2 != NULL)
        {
            // normal case, both numbers still have a digit to subtract here
            data += temp1->data - temp2->data;
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        else if (temp1 != NULL && temp2 == NULL)
        {
            // list2 has run out, so we just bring down list1's digit
            data += temp1->data;
            temp1 = temp1->prev;
        }
        else if (temp1 == NULL && temp2 != NULL)
        {
            // shouldn't normally happen since list1 is the bigger number,
            // but handled just in case
            data -= temp2->data;
            temp2 = temp2->prev;
        }

        // if the column went negative, borrow from the next digit
        if (data < 0)
        {
            data += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        insertfirst(headR, tailR, data);   // this digit is done, add it to the result
    }

    // clean up any leading zeros the subtraction left behind
    // (e.g. 500 - 499 = 001 -> should just be 1)
    while (*headR && (*headR)->data == 0 && (*headR)->nxt != NULL)
    {
        n *temp = *headR;
        *headR = (*headR)->nxt;
        (*headR)->prev = NULL;
        free(temp);
    }
}
