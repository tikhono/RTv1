#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STACK_ARRAY_MAX 10

struct		Stack
{
    const struct	StackInterface *const vtable;
};

struct		StackInterface
{
    int		(*top)(struct Stack *);
    void	(*pop)(struct Stack *);
    void	(*push)(struct Stack *, int);
    int		(*empty)(struct Stack *);
    int		(*full)(struct Stack *);
    void	(*destroy)(struct Stack *);
};

struct StackArray
{
    struct	Stack base;
    int		idx;
    int		array[STACK_ARRAY_MAX];
};

struct StackList
{
    struct Stack		base;
    struct StackNode	*head;
};

struct StackNode
{
    struct	StackNode *next;
    int		data;
};

int		stack_top (struct Stack *s);
void	stack_pop (struct Stack *s);
void	stack_push (struct Stack *s, int x);
int		stack_empty (struct Stack *s);
int		stack_full (struct Stack *s); 
void	stack_destroy (struct Stack *s);

struct	Stack * stack_list_create (void);
struct	Stack * stack_array_create (void);
