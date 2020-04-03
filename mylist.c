typedef struct list_s
{
        struct list_s *next; /* NULL for the last item in a list */
        int data;
}
list_t;

	/* Counts the number of items in a list.
	 */
int count_list_items(const list_t *head) {
	if (head->next) {
		return count_list_items(head->next) + 1;
	} else {
		return 1;
	}
}

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