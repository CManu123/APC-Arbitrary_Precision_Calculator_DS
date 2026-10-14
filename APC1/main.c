/*
 * Name: C Manu, date:
 * Project Title: Arbitrary Precision Calculator (APC)
 *
 * What this program does:
 * Takes two numbers from the command line and does addition, subtraction,
 * multiplication or division on them - no matter how large they are.
 *
 * Why linked lists:
 * Normal int/long variables can only hold numbers up to a certain size.
 * Here every digit is stored in its own node of a doubly linked list,
 * so the size of the number is basically only limited by memory. All
 * the arithmetic is then done digit by digit, the same way we do it
 * by hand on paper.
 *
 * How the program flows:
 * 1. Read the three command line arguments:
 *      argv[1] -> first number (can start with + or -)
 *      argv[2] -> the operator (+, -, x, or /)
 *      argv[3] -> second number (can start with + or -)
 * 2. Pull off any leading sign from each number and remember it
 *    separately (sign1, sign2), then strip the sign character off
 *    before turning the string into a digit list.
 * 3. Build a linked list for each number, one node per digit.
 *    e.g. "1234" becomes 1 -> 2 -> 3 -> 4
 * 4. Run whichever operation the user asked for:
 *      Addition/Subtraction - handled together since subtracting is
 *      really just addition with the second number's sign flipped.
 *      Multiplication - mulnumber(), sign is sign1 * sign2.
 *      Division - divnumber(), also checks for division by zero first.
 * 5. Print the result with the correct sign in front. Division prints
 *    the quotient (the remainder is available too, just not printed
 *    here).
 *
 * Error handling:
 * Bad input (non-digit characters), dividing by zero, or an operator
 * we don't recognize all just print a message and exit cleanly.
 *
 * Example usage:
 *   ./a.out 1234 + 567
 *   Addition Result: 1801
 *
 *   ./a.out -1234 x +567
 *   Multiplication Result: -699678
 *
 *   ./a.out 1234 / 567
 *   Division Result: 2
 */

#include <stdio.h>
#include <string.h>
#include "apc.h"

int main(int argc, char *argv[])
{
   if (argc < 4)
    {
        printf("Not enough arguments\n");   // need num1, operator, num2 - so at least 4 args
        return 0;
    }

    n *head1 = NULL, *tail1 = NULL;   // digit list for the first number
    n *head2 = NULL, *tail2 = NULL;   // digit list for the second number
    n *headR = NULL, *tailR = NULL;   // digit list for the result

    int sign1 = 1, sign2 = 1;   // assume positive unless we see a '-'

    // pull the sign off the front of each number, if there is one
    if (argv[1][0] == '-')
    {
         sign1 = -1;
         argv[1]++;   // skip past the sign so the digit loop below doesn't choke on it
    }
    else if (argv[1][0] == '+')
    {
        argv[1]++;
    }
    if (argv[3][0] == '-')
     {
        sign2 = -1;
        argv[3]++;
    }
    else if (argv[3][0] == '+')
    {
        argv[3]++;
    }

    // turn the first number's string into a digit list
    char *str = argv[1];
    for (int i = 0; str[i] != '\0'; i++)   // go through every character
     {
        if (str[i] >= '0' && str[i] <= '9')   // basically our own isdigit check
        {
            insertlast(&head1, &tail1, str[i] - '0');
        }
        else
        {
            printf("Invalid character in input: %c\n", str[i]);   // not a digit, stop here
            return 0;
        }
    }

    // same thing for the second number
    str = argv[3];
    for (int i = 0; str[i] != '\0'; i++)
     {
        if (str[i] >= '0' && str[i] <= '9')
        {
            insertlast(&head2, &tail2, str[i] - '0');
        }
        else
        {
            printf("Invalid character in input: %c\n", str[i]);
            return 0;
        }
    }

    int resultSign = 1;   // sign to print in front of the final answer

    // Addition
    if (strcmp(argv[2], "+") == 0)
    {
        if (sign1 == sign2)
        {
            addnumber(head1, tail1, head2, tail2, &headR, &tailR);   // same sign, just add them
            resultSign = sign1;
        }
        else
        {
            int cmp = list_compare(head1, head2);   // need to know which one is bigger first
            if (cmp >= 0)
            {
                subnumber(head1, tail1, head2, tail2, &headR, &tailR);   // subtract the smaller from the bigger
                resultSign = sign1;   // result takes the sign of whichever number is bigger
            }
             else
             {
                subnumber(head2, tail2, head1, tail1, &headR, &tailR);
                resultSign = sign2;
            }
        }
        printf("Addition Result: ");
        if (resultSign == -1)   // only print the minus sign when we need to
        printf("-");
        printlist(headR);
    }

    // Subtraction
    else if (strcmp(argv[2], "-") == 0)
    {
        sign2 = -sign2;   // subtracting is the same as adding a negative
        if (sign1 == sign2)
        {
            addnumber(head1, tail1, head2, tail2, &headR, &tailR);
            resultSign = sign1;
        }
        else
        {
            int cmp = list_compare(head1, head2);
            if (cmp >= 0)
            {
                subnumber(head1, tail1, head2, tail2, &headR, &tailR);
                resultSign = sign1;
            }
            else
            {
                subnumber(head2, tail2, head1, tail1, &headR, &tailR);
                resultSign = sign2;
            }
        }
        printf("Subtraction Result: ");
        if (resultSign == -1)
        printf("-");
        printlist(headR);
    }

    // Multiplication
    else if (strcmp(argv[2], "x") == 0)
    {
        mulnumber(head1, tail1, head2, tail2, &headR, &tailR);
        resultSign = sign1 * sign2;   // negative times positive (or vice versa) gives a negative result
        printf("Multiplication Result: ");
        if (resultSign == -1)
        printf("-");
        printlist(headR);
    }

    // Division
    else if (strcmp(argv[2], "/") == 0)
     {

            // catch dividing by zero before we even try
        if (head2 == NULL|| (head2->data == 0 && head2->nxt == NULL))
        {
            printf("Error: Division by zero\n");
            return 0;
        }
        n *headQ = NULL, *tailQ = NULL;      // quotient
        n *headRem = NULL, *tailRem = NULL;  // remainder
        divnumber(head1, tail1, head2, tail2, &headQ, &tailQ, &headRem, &tailRem);

        resultSign = sign1 * sign2;
        printf("Division Result: ");
        if (resultSign == -1)
         printf("-");
        printlist(headQ);
    }
   else
    {
        printf("Unsupported operation: %s\n", argv[2]);   // operator wasn't one we recognize
    }

    return 0;
}
