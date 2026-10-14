/*
 * Name: C Manu, date:
 * Project Title: Arbitrary Precision Calculator (APC)
 *
 * Handles addition of two numbers stored as digit lists. Basically
 * the same column-addition method we all learned in school, just
 * done on linked lists instead of on paper.
 */

#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

void addnumber(n *head1, n *tail1, n *head2, n *tail2, n **headR, n **tailR)
{
    int carry = 0;        // whatever we need to carry over to the next column
    n *temp1 = tail1;      // start from the tail since that's the least significant digit
    n *temp2 = tail2;

    // keep going as long as either number still has digits left
    while (temp1 != NULL || temp2 != NULL)
    {
        int data = carry;   // start this column with the carry from before

        if (temp1 != NULL && temp2 != NULL)
        {
            // both numbers still have a digit here, add them plus the carry
            data = data + temp1->data + temp2->data;
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        else if (temp1 != NULL)
        {
            // list2 ran out first, just carry list1's digit forward
            data = data + temp1->data;
            temp1 = temp1->prev;
        }
        else if (temp2 != NULL)
        {
            // list1 ran out first, so do the same for list2
            data = data + temp2->data;
            temp2 = temp2->prev;
        }

        insertfirst(headR, tailR, data % 10);   // only the last digit stays in this column
        carry = data / 10;                       // anything above 9 gets carried
    }

    // if there's still a carry once both lists are done, it becomes
    // one extra digit at the front (e.g. 99 + 1 = 100)
    if (carry)
        insertfirst(headR, tailR, carry);
}
