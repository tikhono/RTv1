#include "test.h"

int		main(void)
{
	struct Stack *s1 = stack_array_create();
	struct Stack *s2 = stack_list_create();

	stack_push(s1, 1);
	stack_push(s2, 1);
	return (0);
}

