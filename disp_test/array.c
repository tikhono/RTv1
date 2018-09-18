#include "test.h"

static int	stack_array_top (struct Stack *s) { /* ... */ }
static void	stack_array_pop (struct Stack *s) { /* ... */ }
static void	stack_array_push (struct Stack *s, int x) {printf("pushed in array\n");}
static int	stack_array_full (struct Stack *s) { /* ... */ }
static void	stack_array_destroy (struct Stack *s) { /* ... */ }

static int	stack_array_empty (struct Stack *s)
{
    struct StackArray *sa = (void *)s;
    return sa->idx == 0;
}

struct	Stack * stack_array_create (void)
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
