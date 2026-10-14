/*
 * Name: C Manu, date:
 * Project Title: Arbitrary Precision Calculator (APC)
 *
 * Multiplies two digit lists using the same approach we'd use doing
 * long multiplication by hand: multiply by one digit of the second
 * number at a time, shift, then add all the partial results together.
 */

#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

void mulnumber(n *head1, n *tail1, n *head2, n *tail2, n **headR, n **tailR)
{
    int shift = 0;       // how many zeros to tack on for this partial product
    n *temp2 = tail2;     // walk list2 from its least significant digit

    *headR = NULL;
    *tailR = NULL;

    while (temp2 != NULL)
    {
        int carry = 0;
        n *temp1 = tail1;                 // walk list1 from its least significant digit each round
        n *headP = NULL, *tailP = NULL;    // holds this round's partial product

        // multiply the whole of list1 by just one digit from list2
        while (temp1 != NULL)
        {
            int prod = temp1->data * temp2->data + carry;
            carry = prod / 10;
            insertfirst(&headP, &tailP, prod % 10);
            temp1 = temp1->prev;
        }

        // don't forget whatever carry is left over at the end
        if (carry > 0)
            insertfirst(&headP, &tailP, carry);

        // pad with zeros on the right based on which digit of list2 we're on
        // (this is the "shifting" part of long multiplication)
        for (int i = 0; i < shift; i++)
            insertlast(&headP, &tailP, 0);

        // fold this partial product into the running total
        if (*headR == NULL)
        {
            *headR = headP;
            *tailR = tailP;
        }
        else
        {
            n *tempHead = NULL, *tempTail = NULL;
            addnumber(*headR, *tailR, headP, tailP, &tempHead, &tempTail);
            deletelist(headR, tailR);   // don't need the old total anymore
            *headR = tempHead;
            *tailR = tempTail;
        }

        temp2 = temp2->prev;   // move to the next digit of list2
        shift++;                 // next partial product needs one more trailing zero
    }

    // strip off any leading zeros the multiplication ended up with
    while (*headR && (*headR)->data == 0 && (*headR)->nxt != NULL)
    {
        n *temp = *headR;
        *headR = (*headR)->nxt;
        (*headR)->prev = NULL;
        free(temp);
    }
}
