#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Elem
{
    int coefficient;
    int exponent;
} Elem;

typedef struct Multi
{
    Elem *head;
    int len;
} Multi;

