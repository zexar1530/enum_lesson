#include "Counter1.h"

Counter1::Counter1() : count{ 1 }{};

Counter1::Counter1 (int a) : count{ a } {};

void Counter1::Plus() { count++; };

void Counter1::Minus() { count--; };

int Counter1::ResultCounter() { return count; };
