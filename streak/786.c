/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct heap_header heap;
typedef struct elem_header elem;
typedef bool has_higher_priority_fn(elem* e1, elem* e2);

struct elem_header {
    int i;
    int j;
};

struct heap_header {
    int limit;
    int next;
    elem** arr; // \length(arr) == limit;
    has_higher_priority_fn* prior;
};

heap* heap_new(int capacity, has_higher_priority_fn* prior) {
    heap* H = malloc(sizeof(heap));
    H->limit = capacity + 1;
    H->next = 1;
    H->arr = malloc(sizeof(elem*) * H->limit);
    H->prior = prior;
    return H;
}

bool pq_empty(heap* H) {
    return H->next == 1;
}

bool has_higher_priority(elem* e1, elem* e2) {
    float x = (float)(e1->i) / (float)(e1->j);
    float y = (float)(e2->i) / (float)(e2->j);
    return x < y;
}

bool ok_above(heap* H, int parent_idx, int child_idx) {
    elem* parent = H->arr[parent_idx];
    elem* child = H->arr[child_idx];
    return !(*(H->prior))(child, parent);
}

void swap_up(heap* H, int parent_idx, int child_idx) {
    elem* tmp = H->arr[parent_idx];
    H->arr[parent_idx] = H->arr[child_idx];
    H->arr[child_idx] = tmp;
}

bool done_sifting_down(heap* H, int parent_idx) {
    int left_child = parent_idx * 2;
    int right_child = left_child + 1;
    return ok_above(H, parent_idx, left_child)
        && (right_child >= H->next ||
            ok_above(H, parent_idx, right_child));
}

void pq_add(heap* H, elem* x) {
    H->arr[H->next] = x;
    ++(H->next);
    int i = H->next - 1;
    while (i > 1) {
        int parent_idx = (int)(i / 2);
        if (ok_above(H, parent_idx, i)) return;
        swap_up(H, parent_idx, i);
        i = parent_idx;
    }
}

int child_to_swap_up(heap* H, int parent_idx) {
    int left_child = parent_idx * 2;
    int right_child = left_child + 1;

    if (right_child >= H->next ||
        ok_above(H, left_child, right_child)) {
        return left_child;
    }

    return right_child;
}

void sift_down(heap* H) {
    int i = 1;
    while (2 * i < H->next) {
        if (done_sifting_down(H, i)) return;

        int left_child = 2 * i;
        int right_child = left_child + 1;

        int p = child_to_swap_up(H, i);
        swap_up(H, i, p);
        i = p;
    }
}

elem* pq_rem(heap* H) {
    elem* result = H->arr[1];
    --(H->next);

    if (H->next > 1) {
        H->arr[1] = H->arr[H->next];
        sift_down(H);
    }

    return result;
}

int* kthSmallestPrimeFraction(int* arr, int arrSize, int k, int* returnSize) {
    heap* H = heap_new((int)(arrSize * (arrSize - 1) / 2), &has_higher_priority);

    for (int i = 0; i < arrSize - 1; i++) {
        for (int j = i + 1; j < arrSize; j++) {
            elem* x = malloc(sizeof(elem));
            x->i = arr[i];
            x->j = arr[j];
            pq_add(H, x);
        }
    }

    int* result = malloc(sizeof(int) * 2);
    *returnSize = 2;
    while (!pq_empty(H)) {
        elem* x = pq_rem(H);
        k--;
        if (k == 0) {
            result[0] = x->i;
            result[1] = x->j;
            free(x);
            break;
        }
        free(x);
    }

    free(H->arr);
    free(H);
    
    return result;
}