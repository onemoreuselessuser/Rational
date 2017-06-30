
#include "stdafx.h"

#include <iostream>
#include <exception>
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

		if (denominator == 0) {
			throw invalid_argument("0");
		}

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

	if (rhs.Numerator() == 0) {
		throw domain_error("0");
	}
	return Rational(lhs.Numerator(), rhs.Numerator()) * Rational(rhs.Denominator(), lhs.Denominator());
}


int main() {
	try {
		Rational r(1, 0);
		cout << "Doesn't throw in case of zero denominator" << endl;
		return 1;
	}
	catch (invalid_argument&) {
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		cout << "Doesn't throw in case of division by zero" << endl;
		return 2;
	}
	catch (domain_error&) {
	}

	cout << "OK" << endl;
	return 0;
}
