#include "dlist.h"
#include <stdio.h>
/* Function prototypes */
void destroy(void *data);

int main(void)
{
    /* Setting up function pointers for the destroy, for later */
    void (*onDestroy)(void*);
    onDestroy = &destroy;
    
        
    printf("----------------------------------------------------\n");
    printf("----     Doubly Linked List Example Program     ----\n");
    printf("----------------------------------------------------\n");

    /* Create a new doubly linked list */
    DList myList;
    
    /* Initialize the doubly linked list */
    dlist_init(&myList, onDestroy);

    /* Print the size of the linked list to screen
     * Remember, it will be '0' for now */
    printf("List size at beginning : %d\n", dlist_size(&myList));

    /*  Adding an element to the list
     *  When there are currently no elements, then the element will be added
     *  as both head AND tail of the list. */

    /*  As an example, my element will just contain a char* with the value
     *  "ElementOne". You can add anything, as the data is actually a void
     *  pointer. */
    dlist_insert_next(&myList, NULL, "ElementOne");

    /*  printing out the new size of the list, now that the new element has
     *  been added to the list. */
    printf("List size after adding element : %d\n", dlist_size(&myList));

    /* Get the head of the list */
    DListElement    *tempElement = dlist_head(&myList);

    /*  Adding a new element, after head. I am still using a simple char*,
     *  but you can use whatever you like. */
    dlist_insert_next(&myList, tempElement, "ElementTwo");  

    /* Iterate forward in the list, and add a new element AFTER elementTwo */
    tempElement = dlist_next(tempElement);
    dlist_insert_next(&myList, tempElement, "ElementThree");
    
    tempElement = dlist_next(tempElement);    

    /* Add an element BEFORE elementThree */
    
    dlist_insert_prev(&myList, tempElement, "ElementBetweenTwoAndThree");
    
    /* Printing all elements, iterating from head to tail (forwards) */
    printf("----------------------------------------------------\n");
    printf("----    Printing doubly linked list forwards    ----\n");    
    printf("----------------------------------------------------\n");
    int i = 0;
    tempElement = dlist_head(&myList);

    for (i; i < dlist_size(&myList); i++)
    {
        printf("Data in element %d : %s\n", i, (char*)dlist_data(tempElement));
        tempElement = dlist_next(tempElement);
    }

    /* Printing all elements, iterating from head to tail (Backwards) */

    printf("----------------------------------------------------\n");
    printf("----    Printing doubly linked list backwards   ----\n");
    printf("----------------------------------------------------\n");
    i = dlist_size(&myList) - 1;
    tempElement = dlist_tail(&myList);

    for (i; i >= 0; i--)
    {
        printf("Data in element %d : %s\n", i, (char*)dlist_data(tempElement));
        tempElement = dlist_prev(tempElement);
    }

    tempElement = dlist_head(&myList);
    tempElement = dlist_next(tempElement);
    tempElement = dlist_next(tempElement);

    dlist_remove(&myList, tempElement, &tempElement->data);
    
    
    printf("----------------------------------------------------\n");
    printf("----   Removed the BetweenTwoAndThree Element   ----\n");    
    printf("----    Printing doubly linked list forwards    ----\n");    
    printf("----------------------------------------------------\n");
    i = 0;
    tempElement = dlist_head(&myList);

    for (i; i < dlist_size(&myList); i++)
    {
        printf("Data in element %d : %s\n", i, (char*)dlist_data(tempElement));
        tempElement = dlist_next(tempElement);
    }

    printf("List size : %d\n", dlist_size(&myList));

    /* Finished playing around now, Time to destroy the list */
    dlist_destroy(&myList);    
    return 0;
}
void destroy(void *data)
{
    printf  ("%s would be destroyed here, if you write destroy functionality\n",
            (char*)data);
}
