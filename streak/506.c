/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct elem_header elem;
struct elem_header {
    int value;
    int position;
};

typedef bool has_higher_priority_fn(elem* x, elem* y);
typedef struct heap_header heap;
struct heap_header {
    int limit;
    int next;
    elem** data;
    has_higher_priority_fn* prior;
};

bool has_higher_priority(elem* x, elem* y) {
    return x->value > y->value;
}

bool pq_empty(heap* H) {
    return H->next == 1;
}

heap* pq_new(int capacity, has_higher_priority_fn* prior) {
    heap* H = malloc(sizeof(heap));
    H->limit = capacity + 1;
    H->next = 1;
    H->data = calloc(H->limit, sizeof(elem*));
    H->prior = prior;
    return H;
}

bool ok_above(heap* H, int parent_idx, int child_idx) {
    elem* parent = H->data[parent_idx];
    elem* child = H->data[child_idx];
    return !(H->prior(child, parent));
}

void swap_up(heap* H, int child) {
    int parent = child / 2;
    elem* tmp = H->data[child];
    H->data[child] = H->data[parent];
    H->data[parent] = tmp;
}

void pq_add(heap* H, elem* x) {
    H->data[H->next] = x;
    (H->next)++;
    int i = H->next - 1;
    while (i > 1 && !ok_above(H, i/2, i)) {
        swap_up(H, i);
        i = i / 2;
    }
}

bool done_sifting_down(heap* H, int i) {
    int left = 2 * i;
    int right = left + 1;
    return ok_above(H, i, left)
        && (right >= H->next || ok_above(H, i, right));
}

int child_to_swap_up(heap* H, int i) {
    int left = 2 * i;
    int right = left + 1;
    if (right >= H->next || ok_above(H, left, right)) return left;
    return right;

}

void sift_down(heap* H) {
    int i = 1;
    while (2 * i < H->next) {
        if (done_sifting_down(H, i)) return;
        int p = child_to_swap_up(H, i);
        swap_up(H, p);
        i = p;
    }
}

elem* pq_rem(heap* H) {
    elem* max = H->data[1];
    (H->next)--;
    if (H->next > 1) {
        H->data[1] = H->data[H->next];
        sift_down(H);
    }
    return max;
}

int get_number_length(int n) {
    if (n == 0) return 1;
    return 1 + floor(log10(n));
}

char** findRelativeRanks(int* score, int scoreSize, int* returnSize) {
    heap* H = pq_new(scoreSize, &has_higher_priority);
    for (int i = 0; i < scoreSize; i++) {
        elem* x = malloc(sizeof(elem));
        x->value = score[i];
        x->position = i;
        pq_add(H, x);
    }

    char** answer = malloc(scoreSize * sizeof(char*));
    *returnSize = scoreSize;
    int iteration = 0;
    while (!pq_empty(H)) {
        elem* x = pq_rem(H);
        if (iteration == 0) {
            answer[x->position] = "Gold Medal";
        } else if (iteration == 1) {
            answer[x->position] = "Silver Medal";
        } else if (iteration == 2) {
            answer[x->position] = "Bronze Medal";
        } else {
            char* str = malloc((get_number_length(iteration+1)+1) * sizeof(char));
            sprintf(str, "%d", iteration+1); 
            answer[x->position] = str;
        }
        iteration++;
    }
    return answer;
}