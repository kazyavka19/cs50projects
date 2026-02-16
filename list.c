#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}node;

int main(void)
{
     // Create a pointer to the first node of the list
    // Initially the list is empty
    node *list = NULL;

    // Loop 3 times to add 3 numbers to the linked list
    for (int i = 0; i < 3; i++)
    {
        // Allocate memory for a new node
        node *n = malloc(sizeof(node));

        // Check if memory allocation failed
        if (n == NULL)
        {
            free(n);
            return 1;   // Exit program with error code
        }

         // Ask the user for a number and store it in the node
        n->number = get_int("Number: ");

        // New node does not point to anything yet
        n->next = NULL;

        // CASE 1: The list is currently empty
        if (list == NULL)
        {
            // Make the new node the first node in the list
            list = n;
        }

        else if (n->number < list->number)
        {
           n->next = list;
           list = n;
        }

        // CASE 2: The list already has at least one node
        else
        {
            // Start from the beginning of the list
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // If this is the last node in the list
                if (ptr->next == NULL)
                {
                    // Attach the new node to the end
                    ptr->next = n;
                    break;  // Stop looping once added
                }

                if(n->number < list->number)
                {
                     n->next = list;
                     list = n;
                     break; 
                }
            }
        }
    }

    for ( node *ptr = list; ptr != NULL; ptr = ptr->next)
    {  
        printf("%i\n", ptr->number);
        ptr->number;
    }

    node *ptr = list;
    while (ptr != NULL)
    {
      node *next = ptr->next;
      free(ptr);
      ptr = next;
    }
    
    return 0;
    
  
}
