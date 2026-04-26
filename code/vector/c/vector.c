#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int32_t *data;
  size_t length;
  size_t capacity;
} Vector;

int size(Vector *v) { return v->length; }

int capacity(Vector *v) { return v->capacity; }

bool is_empty(Vector *v) { return v->length == 0; }

// dereference pointer + index
int32_t at(Vector *v, size_t index) {
  if (index >= v->length) {
    return -1;
  }
  return *(v->data + index);
}

void resize(Vector *v) {
  if (v->length >= v->capacity) {
    if (v->capacity == 0) {
      v->capacity = 2;
    } else {
      v->capacity *= 2;
    }
  } else if (v->length <= (size_t)v->capacity / 4) {
    v->capacity /= 2;
  }
  int32_t *temp = realloc(v->data, v->capacity * sizeof(int32_t));

  if (temp != NULL) {
    v->data = temp;
  }
}

void push(Vector *v, int32_t value) {
  // data pointer + (length+1), deref and assign
  resize(v);
  *(v->data + (v->length++)) = value;
}

void insert(Vector *v, size_t index, int32_t value) {
  if (index > v->length)
    return;

  resize(v);
  for (size_t i = v->length; i > index; i--) {
    *(v->data + i) = *(v->data + (i - 1));
  }

  *(v->data + index) = value;
  v->length++;
}

void prepend(Vector *v, int32_t value) { insert(v, 0, value); }

int32_t pop(Vector *v) {
  int32_t item = *(v->data + (v->length - 1));
  *(v->data + v->length) = 0;
  v->length--;
  resize(v);
  return item;
}

void delete(Vector *v, size_t index) {
  if (index >= v->length)
    return;
  // replace current value with value ahead
  for (size_t i = index; i < v->length - 1; i++) {
    *(v->data + i) = *(v->data + (i + 1));
  }

  v->length--;
  resize(v);
}

void remove_item(Vector *v, int32_t item) {
  for (size_t i = 0; i < v->length; i++) {
    if (*(v->data + i) == item) {
      delete(v, i);
      break;
    }
  }
}

int32_t find(Vector *v, int32_t item) {
  for (size_t i = 0; i < v->length; i++) {
    if (*(v->data + i) == item) {
      return i;
    }
  }
  return -1;
}

void print_vector(Vector *v) {
  printf("Vector:\n");
  for (size_t i = 0; i < v->length; i++) {
    printf("%d ", *(v->data + i));
  }
}

int main(void) {
  Vector v = {0};

  printf("Initial state\n");
  printf("Size: %d\n", size(&v));
  printf("Capacity: %d\n", capacity(&v));
  printf("Is empty: %s\n\n", is_empty(&v) ? "true" : "false");

  // push test
  printf("Testing push()\n");
  push(&v, 5);
  push(&v, 10);
  push(&v, 15);
  push(&v, 20);
  print_vector(&v);
  printf("\nSize: %d Capacity: %d\n\n", size(&v), capacity(&v));

  // at test
  printf("Testing at()\n");
  printf("Element at index 2: %d\n\n", at(&v, 2));

  // insert test
  printf("Testing insert(index=1, value=99)\n");
  insert(&v, 1, 99);
  print_vector(&v);
  printf("\n");

  // prepend test
  printf("Testing prepend(100)\n");
  prepend(&v, 100);
  print_vector(&v);
  printf("\n");

  // find test
  printf("Testing find(15)\n");
  printf("Found at index: %d\n\n", find(&v, 15));

  // delete test
  printf("Testing delete(index=2)\n");
  delete(&v, 2);
  print_vector(&v);
  printf("\n");

  // remove test
  printf("Testing remove(value=20)\n");
  remove_item(&v, 20);
  print_vector(&v);
  printf("\n");

  // pop test
  printf("Testing pop()\n");
  int popped = pop(&v);
  printf("Popped value: %d\n", popped);
  print_vector(&v);
  printf("\n");

  printf("Final size: %d\n", size(&v));
  printf("Final capacity: %d\n", capacity(&v));

  free(v.data);
  return 0;
}
