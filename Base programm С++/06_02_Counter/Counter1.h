#pragma once

class Counter1
{
private:
    int count;

public:
    Counter1();
    Counter1(int);
    void Plus();
    void Minus();
    int ResultCounter();
};