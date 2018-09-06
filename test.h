
#define STACK_ARRAY_MAX 10

struct Stack
{
    const struct StackInterface * const vtable;
};

struct StackInterface
{
    int (*top)(struct Stack *);
    void (*pop)(struct Stack *);
    void (*push)(struct Stack *, int);
    int (*empty)(struct Stack *);
    int (*full)(struct Stack *);
    void (*destroy)(struct Stack *);
};

struct StackArray
{
    struct Stack base;
    int idx;
    int array[STACK_ARRAY_MAX];
};

struct StackList
{
    struct Stack base;
    struct StackNode *head;
};

struct StackNode
{
    struct StackNode *next;
    int data;
};
