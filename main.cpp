#include <stdio.h>

#include "stack.cpp"

int main()
{
        Stack<char> *stk = new Stack<char>;
	stk->Init();
        int c = '\0';
        while ((c = getchar()) != '\n')
                stk->push(c - '0');

        putchar('\n');
	stk->dump();

//        while (c = stk->pop())
//        	printf("%d\n", c);
	
	stk->Delete();
	delete stk;
}
