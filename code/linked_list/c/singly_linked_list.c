#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int32_t data;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  // Node* tail;
  size_t length;
} LinkedList;

int32_t size(LinkedList *l) { return l->length; }

bool is_empty(LinkedList *l) { return l->length == 0; }

int32_t value_at(LinkedList *l, size_t index) {
  assert(index < l->length);
  Node *dummy = l->head;
  for (size_t i = 0; i < index; i++) {
    dummy = dummy->next;
  }
  return dummy->data;
}

void push_front(LinkedList *l, int32_t value) {
  Node *n = malloc(sizeof(Node));

  if (n == NULL) {
    return;
  }

  n->data = value;
  n->next = l->head;
  l->head = n;
  l->length++;
}

int32_t pop_front(LinkedList *l) {
  assert(!is_empty(l));

  Node *tmp = l->head;
  int32_t val = tmp->data;
  l->head = l->head->next;
  free(tmp);
  l->length--;
  return val;
}

void push_back(LinkedList *l, int32_t value) {
  Node *new_node = malloc(sizeof(Node));

  if (new_node == NULL) {
    return;
  }

  new_node->next = NULL;
  new_node->data = value;

  if (l->head == NULL) {
    l->head = new_node;
    l->length++;
    return;
  }

  Node *dummy = l->head;

  while (dummy->next != NULL) {
    dummy = dummy->next;
  }

  dummy->next = new_node;
  l->length++;
}

int32_t pop_back(LinkedList *l) {
  assert(!is_empty(l));

  // only one node
  if (l->head->next == NULL) {
    int32_t val = l->head->data;
    free(l->head);
    l->head = NULL;
    return val;
  }

  Node *curr = l->head;
  Node *prev = l->head;
  while (curr->next != NULL) {
    prev = curr;
    curr = curr->next;
  }

  int32_t val = curr->data;
  prev->next = NULL;
  free(curr);
  l->length--;
  return val;
}

int32_t front(LinkedList *l) { return l->head->data; }

int32_t back(LinkedList *l) {
  Node *dummy = l->head;
  while (dummy->next != NULL) {
    dummy = dummy->next;
  }

  return dummy->data;
}

// insert in any index + back
void insert(LinkedList *l, size_t index, int32_t value) {
  assert(index <= l->length);

  if (index == 0) {
    push_front(l, value);
    return;
  }

  Node *new_node = malloc(sizeof(Node));
  if (new_node == NULL) {
    return;
  }

  new_node->data = value;

  Node *prev = l->head;

  for (size_t i = 0; i < index - 1; i++) {
    prev = prev->next;
  }

  new_node->next = prev->next;
  prev->next = new_node;
  l->length++;
}

void erase(LinkedList *l, size_t index) {
  assert(index < l->length);

  Node *tmp;

  if (index == 0) {
    tmp = l->head;
    l->head = l->head->next;
    free(tmp);
    l->length--;
    return;
  }

  Node *prev = l->head;

  for (size_t i = 0; i < index - 1; i++) {
    prev = prev->next;
  }

  tmp = prev->next;
  prev->next = tmp->next;
  free(tmp);

  l->length--;
}

int32_t value_n_from_end(LinkedList *l, size_t index) {
  assert(index > 0);

  Node *fast = l->head;
  Node *slow = l->head;

  for (size_t i = 0; i < index; i++) {
    assert(fast != NULL);
    fast = fast->next;
  }

  while (fast != NULL) {
    fast = fast->next;
    slow = slow->next;
  }

  return slow->data;
}

void reverse(LinkedList *l) {
  Node *prev = NULL;
  Node *curr = l->head;
  Node *next = NULL;

  while (curr != NULL) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  l->head = prev;
}

void remove_value(LinkedList *l, int32_t value) {
  if (l->head == NULL) {
    return;
  }

  Node *curr = l->head;
  Node *prev = NULL;

  if (curr->data == value) {
    l->head = curr->next;
    free(curr);
    return;
  }

  while (curr != NULL && curr->data != value) {
    prev = curr;
    curr = curr->next;
  }

  if (curr == NULL) {
    return;
  }

  prev->next = curr->next;
  free(curr);
  l->length--;
}

int main(void) {
    LinkedList l = {0};

    // -------------------------
    // push_front + value_at
    // -------------------------
    push_front(&l, 3); // 3
    push_front(&l, 2); // 2 -> 3
    push_front(&l, 1); // 1 -> 2 -> 3

    assert(size(&l) == 3);
    assert(value_at(&l, 0) == 1);
    assert(value_at(&l, 1) == 2);
    assert(value_at(&l, 2) == 3);

    // -------------------------
    // push_back
    // -------------------------
    push_back(&l, 4); // 1 2 3 4
    assert(size(&l) == 4);
    assert(back(&l) == 4);

    // -------------------------
    // pop_front
    // -------------------------
    assert(pop_front(&l) == 1); // 2 3 4
    assert(size(&l) == 3);
    assert(front(&l) == 2);

    // -------------------------
    // pop_back
    // -------------------------
    assert(pop_back(&l) == 4); // 2 3
    assert(size(&l) == 2);
    assert(back(&l) == 3);

    // -------------------------
    // insert
    // -------------------------
    insert(&l, 1, 99); // 2 99 3
    assert(value_at(&l, 1) == 99);
    assert(size(&l) == 3);

    // -------------------------
    // erase
    // -------------------------
    erase(&l, 1); // remove 99 -> 2 3
    assert(value_at(&l, 1) == 3);
    assert(size(&l) == 2);

    // -------------------------
    // remove_value
    // -------------------------
    push_back(&l, 3); // 2 3 3
    remove_value(&l, 3); // removes first 3 -> 2 3
    assert(size(&l) == 2);
    assert(value_at(&l, 1) == 3);

    // -------------------------
    // value_n_from_end
    // list: 2 -> 3
    // -------------------------
    assert(value_n_from_end(&l, 1) == 3); // last
    assert(value_n_from_end(&l, 2) == 2); // second last

    // -------------------------
    // reverse
    // -------------------------
    reverse(&l); // 3 -> 2
    assert(value_at(&l, 0) == 3);
    assert(value_at(&l, 1) == 2);

    printf("All tests passed!\n");

    return 0;
}
