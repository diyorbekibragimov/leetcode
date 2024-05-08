
//Definition for singly-linked list.
    struct ListNode {
    int val;
    struct ListNode *next;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct list_wrapper lst;
struct list_wrapper {
    struct ListNode* val;
    lst* next;
};

struct stack_header {
    lst* top;
    lst* floor;
};
typedef struct stack_header stack;

stack* stack_new() {
    stack* S = malloc(sizeof(stack));
    S->top = calloc(1, sizeof(lst));
    S->floor = S->top;
    return S;
}

void push(stack* S, struct ListNode* new_data) {
    lst* tmp = calloc(1, sizeof(lst));
    tmp->val = new_data;
    tmp->next = S->top;
    S->top = tmp;
}

struct ListNode* pop(stack* S) {
    if (S->top != S->floor) {
        lst* tmp = S->top;
        struct ListNode* ret = tmp->val;
        S->top = tmp->next;
        free(tmp);
        return ret;
    }
    return NULL;
}

bool stack_empty(stack* S) {
    return S->top == S->floor;
}

int get_number_length(int number) {
    if (number == 0) return 1;
    else return 1 + (int)floor(log10(number));
}

struct ListNode* doubleIt(struct ListNode* head){
    stack* S = stack_new();
    for (struct ListNode* current = head; current != NULL; current = current->next) {
        push(S, current);
    }

    int carry = 0;
    while (!stack_empty(S)) {
        struct ListNode* node = pop(S);
        int number = node->val * 2;
        node->val = number % 10 + carry;
        if (carry == 1) carry -= 1;
        if (get_number_length(number) == 2) {
            carry += 1;
        }
    }
    if (carry == 1) {
        struct ListNode* new = malloc(sizeof(struct ListNode));
        new->val = carry;
        new->next = head;
        return new;
    }
    return head;
}