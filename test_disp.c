#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "test.h"

int stack_top (struct Stack *s) { return s->vtable->top(s); }
void stack_pop (struct Stack *s) { s->vtable->pop(s); }
void stack_push (struct Stack *s, int x) { s->vtable->push(s, x); }
int stack_empty (struct Stack *s) { return s->vtable->empty(s); }
int stack_full (struct Stack *s) { return s->vtable->full(s); }
void stack_destroy (struct Stack *s) { s->vtable->destroy(s); }


static int stack_array_top (struct Stack *s) { /* ... */ }
static void stack_array_pop (struct Stack *s) { /* ... */ }
static void stack_array_push (struct Stack *s, int x) {printf("pushed in array\n");}
static int stack_array_full (struct Stack *s) { /* ... */ }
static void stack_array_destroy (struct Stack *s) { /* ... */ }

static int stack_array_empty (struct Stack *s)
{
    struct StackArray *sa = (void *)s;
    return sa->idx == 0;
}

struct Stack * stack_array_create ()
{
    static const struct StackInterface vtable = {
        stack_array_top, stack_array_pop, stack_array_push,
        stack_array_empty, stack_array_full, stack_array_destroy
    };
    static struct Stack base = { &vtable };
    struct StackArray *sa = malloc(sizeof(*sa));
    memcpy(&sa->base, &base, sizeof(base));
    sa->idx = 0;
	printf("stack array created\n");
    return &sa->base;
}


static int stack_list_top (struct Stack *s) { /* ... */ }
static void stack_list_pop (struct Stack *s) { /* ... */ }
static void stack_list_push (struct Stack *s, int x) {printf("pushed in list\n");}
static int stack_list_full (struct Stack *s) { /* ... */ }
static void stack_list_destroy (struct Stack *s) { /* ... */ }

static int stack_list_empty (struct Stack *s)
{
    struct StackList *sl = (void *)s;
    return sl->head == 0;
}

struct Stack * stack_list_create () {
    static const struct StackInterface vtable = {
        stack_list_top, stack_list_pop, stack_list_push,
        stack_list_empty, stack_list_full, stack_list_destroy
    };
    static struct Stack base = { &vtable };
    struct StackList *sl = malloc(sizeof(*sl));
    memcpy(&sl->base, &base, sizeof(base));
    sl->head = 0;
	printf("stack list created\n");
    return &sl->base;
}

int		main(void)
{
	struct Stack *s1 = stack_array_create();
	struct Stack *s2 = stack_list_create();

	stack_push(s1, 1);
	stack_push(s2, 1);
}

