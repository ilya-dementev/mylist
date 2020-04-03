#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MAX_LIST_ITEMS_COUNT INT_MAX

typedef struct list_s
{
        struct list_s *next; /* NULL for the last item in a list */
        int data;
}
list_t;

	/* Counts the number of items in a list.
	 */
int count_list_items_straight(list_t *head) {

    int count = 0;
    list_t *p = head;
    while  (NULL!= p){
        if (count < MAX_LIST_ITEMS_COUNT){
            count++;
            p = p->next;
        } else {
            fprintf(stderr, "List oversize detected while counting items\n");
            return (-1);
        }            
    }
    return (count);    
}

int count_list_items_recurcive (const list_t *head) {
    if (NULL != head){
        return count_list_items_recurcive(head->next) + 1;
	} else {
		return 0;
	}    
}
/*
int count_list_items(const list_t *head) {
	if (head->next) {
		return count_list_items(head->next) + 1;
	} else {
		return 1;
	}
}
*/
/*
1. no check for NULL list
2. for large list overflow of stack can happen so non-recurcive variant can be appropriate
*/

    /* Inserts a new list item after the one specified as the argument.
	 */
list_t *insert_next_to_list(list_t *item, int data) {
    list_t *new_item;
    // Allocation of memory for new_item
    if(NULL == (new_item = malloc(sizeof(list_t)))) {
        fprintf(stderr, "Memory allocation error. New list_t item not inserted\n");        
    } else { // new_item != NULL;
        new_item->data = data;     
        // Init-n of list
        if (NULL == item){
            new_item->next = NULL;
            // no need for item changing
        } else {       
            if(NULL == item->next) { // item is the last one
                new_item->next = NULL;
                item->next = new_item;
            }  else { // item contains pointer to next item
                new_item->next = item->next;
                item->next = new_item;
            }         
        }
    }
    return new_item;    
}
/*
void insert_next_to_list(list_t *item, int data) {
	(item->next = malloc(sizeof(list_t)))->next = item->next;
	item->next->data = data;
}
*/
/*
 1. no checking for NULL pointer of item (= list initialization)
 2. no checking for NULL pointer of malloc result
 3. not considered that item-next can be NULL
 4. incorrect assigning of item->next. First assign new_item->next to item->next, than assign item->next to new_item
*/

    /* Removes an item following the one specificed as the argument.
	 */
void remove_next_from_list(list_t *item) {
    list_t *garbage = item->next;
    if (item->next) {        
        item->next = item->next->next;
        free(garbage);
    }   
}
/*
void remove_next_from_list(list_t *item) {
	 if (item->next) {
		free(item->next);
        item->next = item->next->next;
     }
}
*/
// 1. assigning of item->next must happen before freeing of memory

	/* Returns item data as text.
	 */
void item_data(const list_t *list, char *buf)
{
	sprintf(buf, "%d", list->data);
}
/*
char *item_data(const list_t *list)
{
	char buf[12];

	sprintf(buf, "%d", list->data);
	return buf;
}
*/
// 1. buf is in local scope of item_data function. buf shoud be passed as argument

void free_list(list_t *list){
    list_t *p = list;
    list_t *garbage = NULL;

    while (NULL != p){
        if (NULL != p->next){
            garbage = p;
            p = p->next;
            free(garbage);
            //garbage = NULL;
        } else{
            free(p);
            p = NULL;
        }            
    }
}

void print_all_list_items(list_t *list){
    list_t *p = list;
    int i = 1;
    char str[12]; 

    printf("Printing list values\n");
    while (NULL != p){
        item_data(p,str);
        printf("value #%d == %s\n",i, str);
        p = p->next;
        i++;
    }
}

void main () {
    //printf("Hello World\n");
    list_t *head = insert_next_to_list(NULL,10);
    list_t *p = NULL;    
    int i, count = 0;

    count = count_list_items_recurcive(NULL);
    printf("count r == %d\n",count);
    count = count_list_items_straight(NULL);
    printf("count s == %d\n",count);

    count = count_list_items_recurcive(head);
    printf("count r == %d\n",count);
    count = count_list_items_straight(head);
    printf("count s == %d\n",count);

    insert_next_to_list(head,20);
    count = count_list_items_recurcive(head);
    printf("count r == %d\n",count);
    count = count_list_items_straight(head);
    printf("count s == %d\n",count);

    insert_next_to_list(head,30);
    count = count_list_items_recurcive(head);
    printf("count r == %d\n",count);
    count = count_list_items_straight(head);
    printf("count s == %d\n",count);

    print_all_list_items(head);
    
    remove_next_from_list(head);
    print_all_list_items(head);

    remove_next_from_list(head);
    print_all_list_items(head);

    remove_next_from_list(head);
    print_all_list_items(head);

    free_list(head);
}