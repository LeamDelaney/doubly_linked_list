#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dlist.h"

/* dlist_init */

void
dlist_init(DList *list, void (*destroy)(void*data))
{
    /* Initialize the values within the list */
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
    
    return;
}

/* dlist_remove */
void
dlist_destroy(DList *list)
{
    /* void pointer to "data" */
    void *data;

    /* Removing all elements */
    while (dlist_size(list) > 0)
    {
        if (dlist_remove(list, dlist_tail(list), (void**)&data) == 0 
            && list->destroy != NULL)
        {
            /* Call the user defined function which will free the memory */
            list->destroy(data);
        }
    }
    /* No operations are permitted on this list now, clearing the structure
     * to be safe. */
    memset(list, 0, sizeof(DList));
    
    return;
}

int
dlist_insert_next(DList *list, DListElement *element, const void *data)
{
    /* Pointer to DListElement */
    DListElement *newElement;

    /* Never allow developer to add a NULL element unless the list is empty */
    if (element == NULL && dlist_size(list) !=0)
    {
        printf("dlist_insert_next :: Failed on null argument\n");
        return -1;
    }
    
    /* Allocate storage for the element in memory */
    if ((newElement = (DListElement *)malloc(sizeof(DListElement))) == NULL)
    {
        printf("dlist_insert_next :: Failed to allocate memory");
        return -1;
    }

    /* Add the new element to the list */
    newElement->data = (void *)data;

    if (dlist_size(list) == 0)
    {
        /* Adding to an empty list */
        list->head = newElement;
        list->head->prev = NULL;
        list->head->next = NULL;

        /* Only one element, so the new element is both head AND tail. */
        list->tail = newElement;
    }
    else
    {
        /* Adding to a list which is NOT empty. */
        newElement->next = element->next;
        newElement->prev = element;

        if (element->next == NULL)
        {
            list->tail = newElement;
        }
        else
        {
            element->next->prev = newElement;
        }

        element->next = newElement;
    }
    /* Update the size of the list, now that the element has been added */
    list->size++;
    
    return 0;
}

int
dlist_insert_prev(DList *list, DListElement *element, const void *data)
{
    /* Pointer to a new element */
    DListElement *newElement;

    /* Adding a NULL element is not allowed unless the list is empty. */
    if (element == NULL && dlist_size(list) != 0)
    {
        printf("dlist_insert_prev :: Failed adding NULL element\n");
        return -1;
    }

    if ((newElement = (DListElement *)malloc(sizeof(DListElement))) == NULL)
    {
        printf("dlist_insert_prev :: Failed to allocate memory\n");
    }
    /* Add the new element to the list */
    newElement->data = (void *)data;    
    
    if (dlist_size(list) == 0 )
    {
        /* Adding to an empty list */
        list->head = newElement;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = NULL;
    }
    else
    {
        /* Add to a list that is NOT empty */
        newElement->next = element;
        newElement->prev = element->prev;
        
        if (element->prev == NULL)
        {
            list->head = newElement;
        }
        else
        {
            element->prev->next = newElement;
        }

        element->prev = newElement;
    }

    /* Update the size of the list in accordance with adding the element */
    
    list->size++;

    return 0;
}

int
dlist_remove(DList *list, DListElement *element, void **data)
{
    /* Removing a NULL element is not allowed when the list is empty */
    if (element == NULL || dlist_size(list) == 0)
    {
        printf("dlist_remove :: Failed trying to remove NULL element\n");
        return -1;
    }
    
    /* remove the element from the list. */
    *data = element->data;

    if (element == list->head)
    {
        /* Remove the element at the head of the list */
        list->head = element->next;
        
        if (list->head == NULL)
        {
            list->tail == NULL;
        }
        else
        {
            element->next->prev = NULL;
        }
        
    }
    else
    {
        /* Remove the element from somewhere other than head. */
        element->prev->next = element->next;

        if (element->next == NULL)
        {
            list->tail = element->prev;
        }
        else
        {
            element->next->prev = element->prev;
        }
    }
    /* Freeing up memory allocated for the element*/
    free (element);

    /* Update the size of the list to allow for removal of element. */
    list->size--;
    
    return 0;
}

int
dlist_size(DList *list)
{
    return list->size;
}

int
dlist_is_head(DListElement *element)
{
    if (element->prev == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int
dlist_is_tail(DListElement *element)
{
    if (element->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

DListElement*
dlist_head(DList* list)
{
    if (list->head != NULL)
    {
        return list->head;
    }
}

DListElement*
dlist_tail(DList *list)
{
    if (list->tail != NULL)
    {
        return list->tail;
    }
}

DListElement*
dlist_next(DListElement *element)
{
    if (element->next != NULL)
    {
        return element->next;
    }
}

DListElement*
dlist_prev(DListElement* element)
{
    if (element->prev != NULL)
    {
        return element->prev;
    }
}

void*
dlist_data(DListElement *element)
{
    if (element->data != NULL)
    {
        return element->data;
    }
}
