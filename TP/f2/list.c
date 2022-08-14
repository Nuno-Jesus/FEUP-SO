#include <stdio.h>
#include <stdlib.h>
#include "list.h"
/* implementation of the List API */
node *node_new(int val, node *p){
  node *q = (node *)malloc(sizeof(node));
  q->val = val;
  q->next = p;
  return q;
}

list *list_new(){
  list *l = (list *)malloc(sizeof(list));
  l->size = 0;
  l->first = NULL;
  return l;
}

list *list_new_random(int size, int range){
  list *l = list_new();
  int i;
  for (i = 0; i < size; i++)
    list_add_first(rand() % range, l);
  return l;
}

void list_add_first(int val, list *l){
  if(l == NULL)
    return;

  node *n = node_new(val, NULL);
  if(list_size(l) == 0){
    l->first = n;
  }

  else{
    //Connects the new node to the previous head of the list
    n->next = l->first;

    //Replaces the head
    l->first = n;
  }

  l->size++;
}

void list_add_last(int val, list *l){
  node *p = node_new(val, NULL);
  if (l->size == 0)
  {
    l->first = p;
  }
  else
  {
    node *q = l->first;
    while (q->next != NULL)
      q = q->next;
    q->next = p;
  }
  l->size++;
}

int list_get_first(list *l){
  /* assumes list l is not empty */
  return l->first->val;
}

int list_get_last(list *l){
  if(l == NULL)
    return -1;

  node* curr = l->first;

  while(curr->next != NULL)
    curr = curr->next;

  return curr->val;
}

void list_remove_first(list *l){
  /* assumes list l is not empty */
  node *p = l->first;
  l->first = l->first->next;
  l->size--;
  /* free memory allocated for node p */
  free(p);
}

void list_remove_last(list *l){
  node* curr = l->first;
  node* previous;
  for(int i = 0; i < list_size(l) - 1; i++){
    if(i == list_size(l) - 2)
      previous = curr;

    curr = curr->next;
  }

  free(curr);
  previous->next = NULL;
  l->size--;
}

int list_size(list *l){
  return l->size;
}

void list_print(list *l){
  if(l == NULL)
    return;

  node* curr = l->first;

  printf("List size: %d\n", list_size(l));
  
  while(curr != NULL){
    printf("%d -> ", curr->val);
    curr = curr->next;
  }

  printf("NULL\n\n");
}