#include <iostream>

using namespace std;

void Plus(int* a, int* b) {
	cout << *a << " + " << *b << " = " << *a + *b << endl;
}

void Minus(int* a, int* b) {
	cout << *a << " - " << *b << " = " << *a - *b << endl;
}

void Mul(int* a, int* b) {
	cout << *a << " * " << *b << " = " << *a * *b << endl;
}

void Del(int* a, int* b) {
	if (*b) cout << *a << " / " << *b << " = " << *a / *b << endl;
}

void Mul_ab(int* a, int* b) {
	int _a = *a;
	if (!(*b)) {
		cout << *a << " в степени " << *b << " равно " << "1" << endl;
		return;
	}
	for (int i{ 1 }; i < *b; i++) { _a = _a * (*a); };
	cout << *a << " в степени " << *b << " равно " << _a << endl;

}