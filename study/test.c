#include <stdio.h>

void add(long *a, long *b)
{
    *a = 2 * *a;
}

int main(int argc, char const *argv[])
{
    long a = 2;
    add(&a, &a);
    printf("%ld", a);
    return 0;
}
