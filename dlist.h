#ifndef DLIST_H
#define DLIST_H

/*  Structure for the doubly linked list element */

typedef struct DListElement_
{
    void                    *data;  // Data in element.
    struct  DListElement_   *prev; // Pointer to previous element.
    struct  DListElement_   *next; // Pointer to next element.
}DListElement;

/*  Structure for the doubly linked list. */
typedef struct DList_
{
    int size;   // Sise of the list at any given time.

    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    DListElement    *head;  // Pointer to element at HEAD.
    DListElement    *tail;  // Pointer to element at TAIL.
}DList;

/******************************************************************************
 *  INTERFACE FOR DOUBLY LINKED LIST
 *****************************************************************************/

/*  Function :      dlist_init
 *  
 *  Description :   dlist_init is used to initialize the doubly linked list.
 *                  The argument passed to it is a pointer to a DList struct.
 *                  This function ***MUST*** be called on the list before the
 *                  list can perform any other operation.
 *                  
 *  Destroy???      The destroy argument is what we use to allow a developer
 *                  to point to their own function which can be used to free
 *                  up data that they have allocated within list elements.
 *                  If your doubly linked list contains data that should not
 *                  be freed when the list_destroy is called, pass NULL into
 *                  this argument instead.
 */
void
dlist_init(DList *list, void (*destroy)(void *data));


/*  Function :      dlist_destroy
 *  Description :   This function will programatically destroy the list which
 *                  is passed into it with a pointer. Once this operation has
 *                  been performed on a list, no other operation should be
 *                  carried out, unless dlist_init is used again. The function
 *                  passed as destroy during the dlist_init will fire once for
 *                  each element in the doubly linked list as it is removed.
 *                  Assuming that the argument was not NULL.
 */
void
dlist_destroy(DList *list);


/*  Function :      dlist_insert_next
 *  Description :   The dlist_insert_next function will allow a developer to
 *                  insert an element right after the position of the one as
 *                  defined by "element" in the arguments. If this function is
 *                  called to operate on an empty list, element could actually
 *                  point to anywhere, but NULL should be used for the sake of
 *                  good practice.
 *                  
 */
int
dlist_insert_next(DList *list, DListElement *element, const void *data);

/*  Function :      dlist_insert_previous
 *  Description :   The dlist_insert_prev function will allow a developer to
 *                  insert an element right pefore the position of the one as
 *                  defined by "element" in the arguments.If this function is
 *                  called to operate on an empty list, element could actually
 *                  point to anywhere, but NULL should be used for the sake of
 *                  good practice.
 */
int
dlist_insert_prev(DList *list, DListElement *element, const void *data);

/*  Function :      dlist_remove
 *  Description :   The dlist_remove function will remove the element which is
 *                  passed as "element" from the doubly linked list passed as
 *                  "list". When this function returns, data will point to the
 *                  data which was stored in the element that was removed. It
 *                  is the responsibility of the developer to manage the code
 *                  here and clean up this memory.
 */
int
dlist_remove(DList* list, DListElement *element, void **data);

/*  Function :      dlist_size
 *  Description :   the dlist_size function returns the value "size" which is
 *                  stored inside "list" 
 */
int
dlist_size(DList* list);

/*  Function :      dlist_is_head
 *  Description :   The dlist_is_head function will return an integer of 0 or 1
 *                  A return value of '1' will confirm that "element" is at the
 *                  head position of "list", and 0 if it is not.
 */
int
dlist_is_head(DListElement *element);

/*  Function :      dlist_is_tail
 *  Description :   The dlist_is_tail function will return an integer of 0 or 1
 *                  A return value of '1' will confirm that "element" is at the
 *                  tail position of "list", and 0 if it is not.
 */
int
dlist_is_tail(DListElement *element);

/*  Function :      dlist_head
 *  Description :   The dlist_head function will return the element which is at
 *                  the head of "list".
 */
DListElement*
dlist_head(DList *list);

/*  Function :      dlist_tail
 *  Description :   The dlist_tail function will return the element which is at
 *                  the tail of "list".
 */
DListElement *
dlist_tail(DList *list);

/*  Function :      dlist_next
 *  Description :   The dlist_next function will return the element which comes
 *                  AFTER the element defined in the argument "element".
 */
DListElement*
dlist_next(DListElement *element);

/*  Function :      dlist_prev
 *  Description :   the dlist_prev function will return the element which comes
 *                  BEFORE the element defined in the argument "element".
 */
DListElement*
dlist_prev(DListElement *element);

/*  Function :      dlist_data
 *  Description :   The dlist_data function will return the pointer to the data
 *                  which is stored inside an element within the doubly linked
 *                  list.
 */
void*
dlist_data(DListElement* element);

#endif
