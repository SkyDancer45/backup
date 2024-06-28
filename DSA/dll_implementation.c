

#include <stdio.h>
#include <stdlib.h>
struct Node {
  int num;
  struct Node *prev;
  struct Node *next;
};
struct Node *home;
struct Node *tail;
void insertion(int num) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->num = num;
  newNode->prev = newNode->next = NULL;
  if (home == NULL) {
    home = newNode;
    tail = newNode;
  } else {

    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
}
void deletion(int num) {
  if (home == NULL) {
    printf("Error List empty");

  } else {
    struct Node *ptr = home;
    if (home->next == NULL) {
      home = tail = NULL;
    } else {
      if (home->num == num) {
        home = home->next;
        home->prev = NULL;
        free(ptr);
        return;
      }
      for (; ptr != NULL; ptr = ptr->next) {
        if (ptr->num == num) {
          if (ptr->next == NULL) {
            ptr->prev->next = NULL;
            tail = ptr->prev;
            free(ptr);
            return;
          } else {
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;
            free(ptr);
            return;
          }
        }
      }
    }
  }
}
void traverse() {
  for (struct Node *ptr = home; ptr != NULL; ptr = ptr->next) {
    printf("%d", ptr->num);
  }
}
void reverseTraverse() {
  for (struct Node *ptr = tail; ptr != NULL; ptr = ptr->prev) {
    printf("%d\t", ptr->num);
  }
}
int main(void) {
  insertion(1);
  insertion(2);
  insertion(3);
  insertion(4);
  deletion(4);
  // traverse();
  reverseTraverse();
  printf("%d", tail->num);
}
