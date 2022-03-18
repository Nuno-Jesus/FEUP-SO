#include <stdio.h>
#include "list.h"

int main(){
  list* l1 = list_new();
  list* l2 = list_new_random(10, 10);

  list_add_first(2, l1);
  list_add_first(1, l1);
  list_add_last(3, l1);

  list_print(l1);
  list_print(l2);

  list_remove_first(l1);
  printf("L1 after removing first: \n");
  list_print(l1);

  list_remove_last(l1);
  printf("L1 after removing last: \n");
  list_print(l1);

  list_remove_first(l1);
  printf("L1 after removing first: \n");
  list_print(l1);

  printf("L2: \n");
  list_print(l2);
}