#include <iostream>

class Fraction
{
private:
	int numerator_;
	int denominator_;

public:
	Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}
	bool operator==(const Fraction& fraction) const
	{
		return (numerator_ == fraction.numerator_) && (denominator_ == fraction.denominator_);
	}
	bool operator!=(const Fraction& fraction) const = default;			// через default получилось только здесь? Почему не получается с остальными не пойму(((((?
	bool operator<(const Fraction& fraction) const
	{
		return (static_cast<double>(numerator_ / denominator_) < static_cast<double>(fraction.numerator_ / fraction.denominator_));
	}
	bool operator>(const Fraction& fraction) const
	{
		return (static_cast<double>(numerator_ / denominator_) > static_cast<double>(fraction.numerator_ / fraction.denominator_));
	}
	bool operator<=(const Fraction& fraction) const
	{
		return (static_cast<double>(numerator_ / denominator_) <= static_cast<double>(fraction.numerator_ / fraction.denominator_));
	}
	bool operator>=(const Fraction& fraction) const
	{
		return (static_cast<double>(numerator_ / denominator_) >= static_cast<double>(fraction.numerator_ / fraction.denominator_));
	}
};

int main()
{
	Fraction f1(4, 3);
	Fraction f2(6, 11);

	std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
	std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
	std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
	std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
	std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
	std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';
	return 0;
}