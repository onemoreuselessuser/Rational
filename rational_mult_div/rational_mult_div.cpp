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

Rational operator * (Rational lhs, Rational rhs) {
	
	int lhs_num = lhs.Numerator();
	int rhs_num = rhs.Numerator();

	bool is_negative = lhs_num < 0;
	
	if (rhs_num < 0) {
		is_negative = !is_negative;
	}

	lhs_num = abs(lhs_num);
	rhs_num = abs(rhs_num);
	

	int nod1 = FindNod(lhs_num, rhs.Denominator());
	int nod2 = FindNod(lhs.Denominator(), rhs_num);

	return Rational((is_negative ? -1 : 1) * (lhs_num / nod1 * rhs_num / nod2), lhs.Denominator() / nod2 * rhs.Denominator() / nod1);
}

Rational operator / (Rational lhs, Rational rhs) {
	
	return Rational(lhs.Numerator(), rhs.Numerator()) * Rational(rhs.Denominator(), lhs.Denominator());

	/*
	int lhs_num = lhs.Numerator();
	int rhs_num = rhs.Numerator();

	bool is_negative = lhs_num < 0;

	if (rhs_num < 0) {
		is_negative = !is_negative;
	}

	lhs_num = abs(lhs_num);
	rhs_num = abs(rhs_num);

	int nod1 = FindNod(lhs_num, rhs_num);
	int nod2 = FindNod(lhs.Denominator(), rhs.Denominator());

	return Rational(is_negative ? -1 : 1 * (lhs_num / nod1 * rhs.Denominator() / nod2), lhs.Denominator() / nod2 * rhs_num / nod1);
	*/
}



int main() {


	Rational ry = Rational(-1, 6) / Rational(1, 4);

	cout << ry.Numerator() << " " << ry.Denominator() << endl;
	return 0;

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a * b;
		bool equal = c == Rational(8, 9);
		if (!equal) {
			cout << "2/3 * 4/3 != 8/9" << endl;
			return 1;
		}
	}

	{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		if (!equal) {
			cout << "5/4 / 15/8 != 2/3" << endl;
			return 2;
		}
	}

	cout << "OK" << endl;
	return 0;
}
