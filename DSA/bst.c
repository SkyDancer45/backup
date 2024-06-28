
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
struct Node {
  int num;
  struct Node *left;
  struct Node *right;
};
struct Node *Insert(struct Node *ptr, int num) {
  if (ptr == NULL) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->num = num;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  } else {
    if (ptr->num > num) {
      ptr->left = Insert(ptr->left, num);
    } else if (ptr->num < num) {
      ptr->right = Insert(ptr->right, num);
    }
    return ptr;
  }
}
struct Node *search(int num, struct Node *ptr) {
  if (ptr->num == num) {
    return ptr;

  } else {
    if (ptr->num > num) {
      return search(num, ptr->left);
    }
    if (ptr->num < num) {
      return search(num, ptr->right);

    } else {
      return NULL;
    }
  }
}
void inorderTreeTraversal(struct Node *root) {
  if (root != NULL) {
    inorderTreeTraversal(root->left);
    printf("%d", root->num);
    inorderTreeTraversal(root->right);
  }
}

void preorderTreeTraversal(struct Node *root) {
  if (root != NULL) {
    printf("%d", root->num);
    preorderTreeTraversal(root->left);
    preorderTreeTraversal(root->right);
  }
}
void postorderTreeTraversal(struct Node *root) {
  if (root != NULL) {
    postorderTreeTraversal(root->left);
    postorderTreeTraversal(root->right);
    printf("%d", root->num);
  }
}
void swap(struct Node *node1, struct Node *node2) {
  int temp = node1->num;
  node1->num = node2->num;
  node2->num = temp;
}
// struct Node *delete(int num, struct Node *root) {
//   if (root == NULL) {
//
//     return NULL;
//   } else if (root->num > num) {
//     root->left = delete (num, root->left);
//     return root;
//
//   } else if (root->num < num) {
//     root->right = delete (num, root->right);
//     return root;
//
//   } else if (root->num == num) {
//     if (root->left == NULL) {
//       struct Node *temp = root->right;
//       free(root);
//       return temp;
//     } else if (root->right == NULL) {
//       struct Node *temp = root->left;
//       free(root);
//       return temp;
//     }
//     struct Node *succParent = root;
//     struct Node *succ = root->right;
//     while (succ->left != NULL) {
//       succParent = succ;
//       succ = succ->left;
//     }
//     root->num = succ->num;
//     if (succParent != root) {
//       succParent->left = delete (succ->num, succParent->left);
//
//     } else {
//       succParent->right = delete (succ->num, succParent->right);
//     }
//   }
//   return root;
// }
struct Node *delete(struct Node *node, int val) {
  if (node == NULL) {
    return NULL;
  }
  if (node->num > val) {
    node->left = delete (node->left, val);
  } else if (node->num < val) {
    node->right = delete (node->right, val);
  } else {
    if (node->left == NULL && node->right == NULL) {
      free(node);
      return NULL;
    }
    if (node->right == NULL || node->left == NULL) {
      struct Node *temp = node->left ? node->left : node->right;
      free(node);
      return temp;
    }
    if (node->right != NULL && node->left != NULL) {
      struct Node *temp = node->right;
      while (temp->left != NULL) {
        temp = temp->left;
      }
      node->num = temp->num;
      node->right = delete (node->right, node->num);
    }
  }
  return node;
}
struct Node *findParent(struct Node *root, int value) {
  if (root == NULL) {
    return NULL;

  } else {
    if (root->num == value) {
      return NULL;
    }
    if (root->num > value) {
      if (root->left == NULL) {

        return NULL;
      }
      if (root->left->num == value) {
        return root;

      } else {

        return findParent(root->left, value);
      }

    } else {
      if (root->right == NULL) {
        return NULL;
      }
      if (root->right->num == value) {
        return root;

      } else {
        return findParent(root->right, value);
      }
    }
    return NULL;
  }
}
// struct Node *findParent(struct Node *node, int val) {
//   if (node == NULL) {
//
//     return NULL;
//   }
//
//   if (node->num == val) {
//     return NULL;
//   }
//   if (node->num > val) {
//     if (node->left->num == val) {
//       return node;
//     } else {
//       return findParent(node->left, val);
//     }
//   } else {
//     if (node->right == NULL) {
//       return NULL;
//
//     } else if (node->right->num == val) {
//       return node;
//     } else {
//       return findParent(node->right, val);
//     }
//   }
// }
//
// struct Node *findParent(struct Node *parent, int value) {}
int main(void) {
  struct Node *home = NULL;
  home = Insert(home, 50);
  Insert(home, 70);
  Insert(home, 30);
  Insert(home, 20);
  Insert(home, 60);

  Insert(home, 40);
  Insert(home, 80);
  delete (home, 40);
  postorderTreeTraversal(home);
}
