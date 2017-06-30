// rational_io.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <sstream>
using namespace std;

class Rational {
public:
	Rational() {
		p = 0;
		q = 1;
	}

	Rational(int numerator, int denominator) {
		bool is_negative = (numerator * denominator < 0);

		if (numerator < 0 && denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}

		if (is_negative) {
			numerator = abs(numerator);
			denominator = abs(denominator);
		}

		int a = numerator;
		int b = denominator;

		while (a > 0 && b > 0) {
			if (a > b) {
				a %= b;
			}
			else {
				b %= a;
			}
		}
		int nod = a + b;

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

ostream& operator << (ostream& s, Rational& r) {
	s << r.Numerator() << "/" << r.Denominator();
	return s;
}

istream& operator >> (istream& s, Rational& r) {
	int numerator = 0;
	int denominator = 1;

	s >> numerator;
	s.ignore(1);
	s >> denominator;

	r = Rational(numerator, denominator);

	return s;
}

int main() {
	
	const Rational r = Rational(1, 2) * Rational(1, 3) / Rational(1, 4);
	
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}
	
	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 3;
		}
	}
	cout << "OK" << endl;
	return 0;
}
