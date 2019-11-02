#include <stdio.h>

#include "stack.cpp"

int main()
{
        Stack<char> *stk = (Stack<char> *) malloc(sizeof(Stack<char>));
	stk->Init();
        int c = '\0';
        while ((c = getchar()) != '\n')
                stk->push(c - '0');

        putchar('\n');

        while (c = stk->pop())
                printf("%d\n", c);
	
	stk->Delete();
	free(stk);
}
