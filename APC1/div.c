/*
 * Name: C Manu, date:
 * Project Title: Arbitrary Precision Calculator (APC)
 *
 * Divides list1 by list2 the same way we'd do long division on
 * paper: bring down one digit at a time, subtract the divisor from
 * the running remainder as many times as it'll go, and whatever's
 * left over at the end is the remainder.
 */

#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

// Divides list1 by list2, giving back a quotient list and a remainder list.
void divnumber(n *head1, n *tail1, n *head2, n *tail2, n **headQ, n **tailQ, n **headRem, n **tailRem)
{
    // can't divide by zero, so check for that first
    if (head2 == NULL)
    {
        printf("Error: Division by zero\n");
        *headQ = NULL; *tailQ = NULL;
        *headRem = NULL; *tailRem = NULL;
        return;
    }

    *headQ = NULL; *tailQ = NULL;
    *headRem = NULL; *tailRem = NULL;

    n *remHead = NULL, *remTail = NULL;   // running remainder, starts off empty

    // go through the dividend one digit at a time, just like long division
    for (n *curr = head1; curr != NULL; curr = curr->nxt)
    {
        insertlast(&remHead, &remTail, curr->data);   // bring down the next digit

        // trim off any leading zeros so the comparison below works properly
        while (remHead && remHead->data == 0 && remHead->nxt != NULL)
        {
            n *tmp = remHead;
            remHead = remHead->nxt;
            remHead->prev = NULL;
            free(tmp);
        }

        int count = 0;   // how many times the divisor fits in here

        // subtract the divisor over and over until it no longer fits
        while (list_compare(remHead, head2) >= 0)
        {
            n *tmpHead = NULL, *tmpTail = NULL;
            subnumber(remHead, remTail, head2, tail2, &tmpHead, &tmpTail);
            deletelist(&remHead, &remTail);   // done with the old remainder
            remHead = tmpHead;
            remTail = tmpTail;
            count++;
        }

        insertlast(headQ, tailQ, count);   // this becomes the next digit of the quotient
    }

    *headRem = remHead;   // whatever's left over once we run out of digits
    *tailRem = remTail;

    // clean up leading zeros on the quotient too
    while (*headQ && (*headQ)->data == 0 && (*headQ)->nxt != NULL)
    {
        n *tmp = *headQ;
        *headQ = (*headQ)->nxt;
        (*headQ)->prev = NULL;
        free(tmp);
    }
}
