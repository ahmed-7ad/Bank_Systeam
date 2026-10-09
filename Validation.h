#pragma once
#include <iostream>
#include <string>
#include <cctype>     
using namespace std;

class Validation
{
public:
	static bool valid_name(const string& name)
	{
		if (name.length() < 3 || name.length() > 20) { return false; }

		 for (char c : name)
		 {
			if (!isalpha(c) && !isspace(c)) { return false; }
		 }
		return true;
	}

	static bool valid_Password(const string& password)
	{
		if (password.length() < 8 || password.length() > 20) { return false; }
		return true;
	}

	static bool valid_balance(double balance)
	{
		return (balance >= 1500);
	}

	static bool valid_salary(double salary)
	{
		return (salary >= 5000);
	}
};