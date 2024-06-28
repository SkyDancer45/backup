#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct node {
  int num;
  struct node *next;
};
struct node *home;
struct node *tail;
void insert(int x) {
  struct node *newNode = (struct node *)malloc(sizeof(struct node));
  if (newNode == NULL) {

    printf("Error Creating Node");

  } else {
    newNode->num = x;

    if (home == NULL) {
      home = tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
  }
}
int searchNode(int x) {
  if (home == NULL) {
    printf("Error Node not found list empty");
    return -1;

  } else {
    struct node *presentPtr = home;
    int counter = 1;

    while (presentPtr != NULL) {

      if (presentPtr->num == x) {

        return counter;
      } else {
        counter++;
        presentPtr = presentPtr->next;
      }
    }
  }
  printf("Error Number Not found");
  return -1;
}
void deletion(int x) {
  if (home == NULL) {

    printf("ERROR LINKED LIST empty");
  } else {
    if (home == tail) {
      if (home->num == x) {
        free(home);
        home = tail = NULL;

      } else {
        printf("ERROR NOT FOUND");
      }

    } else {
      if (home->num == x) {
        struct node *temp = home;
        home = home->next;
        free(temp);
        return;
      }

      struct node *newnode = home->next;
      struct node *prevNode = home;
      while (newnode != NULL) {
        if (newnode->num == x) {
          prevNode->next = newnode->next;
          free(newnode);
          if (prevNode->next == NULL) {
            tail = prevNode;
          }
          return;
        }
        prevNode = prevNode->next;
        newnode = newnode->next;
      }
      if (newnode == NULL) {
        printf("ERROR 404 ");
        return;
      }
    }
  }
}
void traverse() {
  for (struct node *ptr = home; ptr != NULL; ptr = ptr->next) {
    printf("%d\n", ptr->num);
  }
}
struct node *findPredecessor(struct node *ptr) {
  if (ptr == home) {
    return NULL;

  } else {
    struct node *result = home;
    for (; result->next != ptr; result = result->next)
      ;
    return result;
  }
}
void reverseTraverse(struct node *ptr) {
  printf("%d", ptr->num);
  if (ptr != home) {
    reverseTraverse(findPredecessor(ptr));
  }
}
int main() {
  struct node *node1 = (struct node *)malloc(sizeof(struct node));
  node1->num = 1;
  struct node *node2 = (struct node *)malloc(sizeof(struct node));
  node2->num = 2;
  node1->next = node2;
  home = node1;
  tail = node2;
  // struct node *node3 = (struct node *)malloc(sizeof(struct node));
  // node3->num = 3;
  // node2->next = node3;
  // home = node1;
  // tail = node3;
  // insert(4);
  // int x = searchNode(3);
  /* deletion(1); */
  // printf("%d", home->num);
  // printf("%d", home->next->num);
  // printf("%d", home->next->next->num);
  /*  printf("%d", home->num); */
  /* traverse(); */

  deletion(2);
  printf("%d\n", tail->num);
  // reverseTraverse(tail);
}
