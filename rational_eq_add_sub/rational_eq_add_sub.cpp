// rational_eq_add_sub.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
using namespace std;

int FindNod(int a, int b) {
	while (a > 0 && b > 0) {
		if (a > b) {
			a %= b;
		}
		else {
			b %= a;
		}
	}
	return a + b;
}

class Rational {
public:
	Rational() {
		p = 0;
		q = 1;
	}

	Rational(int numerator, int denominator) {
		
		if (numerator < 0 && denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}

		bool is_negative = (numerator < 0 || denominator < 0);

		

		if (is_negative) {
			numerator = abs(numerator);
			denominator = abs(denominator);
		}

		int nod = FindNod(numerator, denominator);
		
		p = is_negative ? -numerator / nod : numerator / nod;
		q = denominator / nod;

	}

	int Numerator() const {
		return p;
	}

	int Denominator() const {
		return q;
	}

private:
	int p;
	int q;


};

bool operator == (Rational lhs, Rational rhs) {

	return (lhs.Denominator() == rhs.Denominator() && lhs.Numerator() == rhs.Numerator());
}

Rational operator+ (const Rational& lhs, const Rational& rhs) {

	int nod = FindNod(lhs.Denominator(), rhs.Denominator());

	return Rational(rhs.Denominator() / nod * lhs.Numerator() + lhs.Denominator() / nod * rhs.Numerator(), lhs.Denominator() / nod * rhs.Denominator());
}

Rational operator- (Rational lhs, Rational rhs) {
	int nod = FindNod(lhs.Denominator(), rhs.Denominator());

	return Rational(rhs.Denominator() / nod * lhs.Numerator() - lhs.Denominator() / nod * rhs.Numerator(), lhs.Denominator() / nod * rhs.Denominator());
}

int main() {
	{
		Rational r1(1, 6);
		Rational r2(2, 3);
		bool equal = r1 == r2;
		if (!equal) {
			cout << "4/6 != 2/3" << endl;
			return 1;
		}
	}

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a + b;
		bool equal = c == Rational(2, 1);
		if (!equal) {
			cout << "2/3 + 4/3 != 2" << endl;
			return 2;
		}
	}

	{
		Rational a(5, 7);
		Rational b(2, 9);
		Rational c = a - b;
		bool equal = c == Rational(31, 63);
		if (!equal) {
			cout << "5/7 - 2/9 != 31/63" << endl;
			return 3;
		}
	}

	cout << "OK" << endl;
	return 0;
}
