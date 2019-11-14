#include <stdio.h>

#include "stack.h"

void print(const char *ptr)
{
	printf("%c\n", *ptr);
}

int main()
{
        Stack<char> *stk = new Stack<char>;
	stk->Init();
        int c = '\0';
        while ((c = getchar()) != '\n')
                stk->push(c);

        putchar('\n');
	stk->dump(print);

//        while (c = stk->pop())
//        	printf("%d\n", c);
	
	stk->Delete();
	delete stk;
}
