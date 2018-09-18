#include "test.h"

static int	stack_list_top (struct Stack *s) { /* ... */ }
static void	stack_list_pop (struct Stack *s) { /* ... */ }
static void	stack_list_push (struct Stack *s, int x) {printf("pushed in list\n");}
static int	stack_list_full (struct Stack *s) { /* ... */ }
static void	stack_list_destroy (struct Stack *s) { /* ... */ }

static int	stack_list_empty (struct Stack *s)
{
    struct StackList *sl = (void *)s;
    return (sl->head == 0);
}

struct Stack	*stack_list_create(void)
{
    static const struct StackInterface vtable = {
        stack_list_top, stack_list_pop, stack_list_push,
        stack_list_empty, stack_list_full, stack_list_destroy
    };
    static struct Stack base = { &vtable };
    struct StackList *sl = malloc(sizeof(*sl));
    memcpy(&sl->base, &base, sizeof(base));
    sl->head = 0;
	printf("stack list created\n");
    return (&sl->base);
}


