// calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

// один из способов вычисления наибольшего общего делителя (НОД) — рекурсивный:
// вместо цикла функция будет вызывать себя же, но с другими аргументами
int GreatestCommonDivisor(int a, int b) {
	if (b == 0) {
		return a;
	}
	else {
		return GreatestCommonDivisor(b, a % b);
	}
}

class Rational {
public:
	Rational(const string& r) {
		stringstream stream_str(r);
		int p, q;
		stream_str >> p;
		if (stream_str.peek() != '/') {
			throw exception("Invalid argument");
		}
		stream_str.ignore(1);
		stream_str >> q;

		const int gcd = GreatestCommonDivisor(p, q);
		// сократим дробь, разделив числитель и знаменатель на их НОД
		numerator = p / gcd;
		denominator = q / gcd;
		// знаменатель должен быть положительным
		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		}

	}
	Rational() {  // дробь по умолчанию — 0/1
		numerator = 0;
		denominator = 1;
	}
	Rational(int new_numerator, int new_denominator) {
		if (new_denominator == 0) {
			// бросаем исключение в случае нулевого знаменателя
			throw invalid_argument("Invalid argument");
		}
		const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
		// сократим дробь, разделив числитель и знаменатель на их НОД
		numerator = new_numerator / gcd;
		denominator = new_denominator / gcd;
		// знаменатель должен быть положительным
		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		}
	}

	int Numerator() const {
		return numerator;
	}

	int Denominator() const {
		return denominator;
	}

private:
	int numerator;
	int denominator;
};

// поскольку дроби сокращены, достаточно сравнить числители и знаменатели
bool operator == (const Rational& lhs, const Rational& rhs) {
	return lhs.Numerator() == rhs.Numerator() &&
		lhs.Denominator() == rhs.Denominator();
}

// используем обычную формулу сложения дробей, основанную на приведении слагаемых к общему знаменателю
Rational operator + (const Rational& lhs, const Rational& rhs) {
	return {
		lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator()
	};
}

// вычитание реализуем аналогично сложению
// дублирования кода можно было избежать, определив для класса Rational операцию унарного минуса: тогда разность lhs и rhs можно было бы вычислить           как lhs + (-rhs)
Rational operator - (const Rational& lhs, const Rational& rhs) {
	return {
		lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator()
	};
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
	return {
		lhs.Numerator() * rhs.Numerator(),
		lhs.Denominator() * rhs.Denominator()
	};
}

// деление равносильно умножению на обратную («перевёрнутую») дробь
Rational operator / (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("");
	}
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

istream& operator >> (istream& is, Rational& r) {
	int n, d;
	char c;
	is >> n >> c >> d;
	if (is && c == '/') {
		r = Rational(n, d);
	}
	return is;
}

ostream& operator << (ostream& os, const Rational& r) {
	return os << r.Numerator() << '/' << r.Denominator();
}

// чтобы сравнить lhs с rhs, сравним их разность с нулём, что равносильно сравнению с нулём числителя
bool operator < (const Rational& lhs, const Rational& rhs) {
	return (lhs - rhs).Numerator() < 0;
}

int main()
{
	string cin_rationalA;
	string cin_rationalB;
	string operation;
	try {

		cin >> cin_rationalA >> operation >> cin_rationalB;
		if (operation != "+" && operation != "-" && operation != "*" && operation != "/") {
			throw exception("Unrecognized operation");
		}

		Rational rationalA(cin_rationalA);
		Rational rationalB(cin_rationalB);
		Rational res;

		if (operation == "/" && rationalB.Numerator() == 0) {
			throw exception("Division by zero");
		}
		
		if (operation == "+") {
			res = rationalA + rationalB;
		}
		else if (operation == "-") {
			res = rationalA - rationalB;
		}
		else if (operation == "*") {
			res = rationalA * rationalB;
		}
		else if (operation == "/") {
			res = rationalA / rationalB;
		}

		cout << res.Numerator() << "/" << res.Denominator() << endl;

	}
	catch (exception ex) {
		cout << ex.what() << endl;;
	}
	
	return 0;
}


