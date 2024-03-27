#include <iostream>

using namespace std;

class Fraction
{
public:
	int numerator_;
	int denominator_;

public:
	Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}
	void CheckFraction(int& a, int& b)
	{
		for (;;)
		{
			if (!((a % 2) || (b % 2)))
			{
				a = a / 2;
				b = b / 2;
			}
			else if (!((a % 3) || (b % 3)))
			{
				a = a / 3;
				b = b / 3;
			}
			else
				return;
		}

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
	Fraction operator+(const Fraction& fraction)
	{
		int common_denominator = denominator_ * fraction.denominator_;
		int common_numerator = (numerator_ * fraction.denominator_) + (denominator_ * fraction.numerator_);
		CheckFraction(common_numerator, common_denominator);
		return Fraction(common_numerator, common_denominator);
	}
	Fraction operator-(const Fraction& fraction)
	{
		int common_denominator = denominator_ * fraction.denominator_;
		int common_numerator = (numerator_ * fraction.denominator_) - (denominator_ * fraction.numerator_);
		CheckFraction(common_numerator, common_denominator);
		return Fraction(common_numerator, common_denominator);
	}
	Fraction operator*(const Fraction& fraction)	
	{
		int common_denominator = denominator_ * fraction.denominator_;
		int common_numerator = numerator_ * fraction.numerator_;
		CheckFraction(common_numerator, common_denominator);			//проверяем и при неоходимости сокращаем
		return Fraction(common_numerator, common_denominator);
	}
	Fraction operator/(const Fraction& fraction)
	{
		int common_denominator = denominator_ * fraction.numerator_;
		int common_numerator = numerator_ * fraction.denominator_;
		CheckFraction(common_numerator, common_denominator);
		return Fraction(common_numerator, common_denominator);
	}
	Fraction operator++()
	{
		numerator_ = numerator_ + denominator_;
		CheckFraction(numerator_, denominator_);
		return *this;// Fraction(numerator_, denominator_);
	}
	Fraction operator--(int)
	{
		Fraction temp(numerator_, denominator_);
		numerator_ = numerator_ - denominator_;
		CheckFraction(numerator_, denominator_);
		return temp;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");

	int a_1{}, b_1{}, a_2{}, b_2{};				//дроби

	cout << "Введите числитель дроби 1: ";
	cin >> a_1;
	cout << "Введите знаменатель дроби 1: ";
	cin >> b_1;
	cout << "Введите числитель дроби 2: ";
	cin >> a_2;
	cout << "Введите знаменатель дроби 2: ";
	cin >> b_2;

	Fraction f1(a_1, b_1);
	Fraction f2(a_2, b_2);

	Fraction sum = f1 + f2;
	cout << f1.numerator_ << "/" << f1.denominator_ << " + " << f2.numerator_ << "/" << f2.denominator_ << " = " << sum.numerator_ << "/" << sum.denominator_ << endl;

	Fraction sub = f1 - f2;
	cout << f1.numerator_ << "/" << f1.denominator_ << " - " << f2.numerator_ << "/" << f2.denominator_ << " = " << sub.numerator_ << "/" << sub.denominator_ << endl;

	Fraction mul = f1 * f2;
	cout << f1.numerator_ << "/" << f1.denominator_ << " * " << f2.numerator_ << "/" << f2.denominator_ << " = " << mul.numerator_ << "/" << mul.denominator_ << endl;

	Fraction del = f1 / f2;
	cout << f1.numerator_ << "/" << f1.denominator_ << " / " << f2.numerator_ << "/" << f2.denominator_ << " = " << del.numerator_ << "/" << del.denominator_ << endl;

	cout << " ++ " << f1.numerator_ << "/" << f1.denominator_;
	Fraction sum_mul = ++f1 * f2;
	cout  << " * " << f2.numerator_ << "/" << f2.denominator_ << " = " << sum_mul.numerator_ << "/" << sum_mul.denominator_ << endl;
	cout << "Значение дроби: " << f1.numerator_ << "/" << f1.denominator_ << endl;
 
	cout << f1.numerator_ << "/" << f1.denominator_;
	Fraction sub_mul = f1-- * f2;
	cout << "-- * " << f2.numerator_ << "/" << f2.denominator_ << " = " << sub_mul.numerator_ << "/" << sub_mul.denominator_ << endl;
	cout << "Значение дроби: " << f1.numerator_ << "/" << f1.denominator_ << endl;



	/*std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
	std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
	std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
	std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
	std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
	std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';*/
	return 0;
}
