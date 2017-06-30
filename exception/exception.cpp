// exception.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void EnsureEqual(const string& left, const string& right) {
	if (left != right) {
		throw runtime_error(left + " != " + right);
	}
}

int main()
{
	try {
		EnsureEqual("abc", "ac");
	}
	catch (exception ex) {
		cout << ex.what();
	}
	return 0;
}

