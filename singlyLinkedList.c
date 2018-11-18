#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cell {
  struct cell *next;
  int data;
};

typedef struct cell *cellPtr;

/*!
 * @brief
 * @param[in]
 * @return
 */
cellPtr list_alloc(int data) {
  cellPtr new = NULL;
  new = (cellPtr)malloc(sizeof(cellPtr));
  if (new == NULL) {
    fprintf(stderr, "Error: list_alloc(): %s\n", strerror(errno));
    return NULL;
  }

  new->next = NULL;
  new->data = data;

  return new;
}

int list_add(cellPtr header, int data) {
  cellPtr next = NULL;
  cellPtr prev = header;

  next = list_alloc(data);
  if (next == NULL)
    return -1;

  while (prev->next != NULL) {
    prev = prev->next;
  }
  prev->next = next;
  return 0;
}

void list_free(cellPtr header) {
  cellPtr temp = header;
  cellPtr swap = NULL;

  while (temp != NULL) {
    swap = temp->next;
    free(temp);
    temp = swap;
  }
}

static void list_print(cellPtr header) {
  cellPtr p = header;
  printf("list{\n");
  while (p != NULL) {
    printf("%d\n", p->data);
    p = p->next;
  }
  printf("}\n");
}

int main(void) {
  int cnt = 0;
  cellPtr header = list_alloc(0);
  if (header == NULL)
    return -1;

  for (cnt = 1; cnt < 10; cnt++) {
    list_add(header, cnt);
  }
  list_print(header);
  list_free(header);

  return 0;
}
