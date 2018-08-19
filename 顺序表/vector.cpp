#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector {
    int *data;
    int size, length;
} Vector;

Vector *init(int n) {
    Vector *p = (Vector *)malloc(sizeof(Vector));
    p->data = (int *)malloc(sizeof(int) *n);
    p->size = n;
    p->length = 0;
    return p;
}

int expand(Vector *v) {
    int *data = (int *)realloc(v->data, sizeof(int) * (v->size * 2));
    if (data == NULL) return 0;
    v->data = data;
    v->size *= 2;
    //if (data == NULL) return 0;
    //memcpy(data, v->data, sizeof(int) * v->length);
    //v->size *= 2;
    //free(v->data);
    //v->data = data;
    printf("Vector expand\n ");
    return 1;
}

int insert(Vector *v, int x, int ind) {
    if (v->length >= v->size) {
        if (!expand(v)) {
            return 0;
        }
    }
    if (ind < 0 || ind > v->length) {
        return 0;
    } //memove
    for (int i = v->length - 1; i >= ind; i--) {
        v->data[i + 1] = v->data[i];
    }
    v->data[ind] = x;
    v->length += 1;
    return 1;
}

int delete_element(Vector *v, int ind) {
    if (ind >= v->length || ind < 0) {
        return 0;
    }
    for (int i = ind + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->length -= 1;
    return 1;
}

void output(Vector *v) {
    printf("[");
    for (int i = 0; i < v->length; i++) {
        printf("%d", v->data[i]);
    }
    printf("]\n");
    return;
}

void clear(Vector *v) {
  if (v ==NULL) return ;
  free(v->data);
  free(v);
  return;
}
int main() {
    srand(time(0));
    Vector *v = NULL;
    v = init(1);
    for  (int i = 0; i < 10; i++) {
        int x = rand() % 100, ind = rand() % (i + 3) - 1;
        printf("%d : insert(%d, %d) = ", i, x, ind);
        int ret = insert(v, x, ind);
        printf("%d : ", ret);
        output(v);
    }
/*    for (int i = 0; i < 5; i++) {
        int ind = rand() % (v->length + 2) - 1;
        printf("%d : delete_element(%d) = ", i + 1, ind);
        int ret = delete_element(v, ind);
        printf("%d : \n", ret);
        output(v);
    }
*/
    return 0;
}
