#include <iostream>

struct Derive
{
    int data;
};

struct Base : Derive
{
    char *name;
};


int main()
{
    Base test;

    test.data = 5;
    test.name = "test";
s}