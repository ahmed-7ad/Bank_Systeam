#pragma once
#include <iostream>
#include <string>
#include "Validation.h"
using namespace std;

class Person
{
protected:
	int id;
	string name, password;

public:
	Person(int id, const string& name, const string& password)
	{
		set_id(id);
		set_name(name);
		set_password(password);
	}

	virtual ~Person() {}

	void set_id(int id)
	{
		this->id = id;
	}

	void set_name(const string& name)
	{
		Validation::valid_name(name);
		this->name = name;
	}

	void set_password(const string& password)
	{
		Validation::valid_Password(password);
		this->password = password;
	}

	int get_id() const
	{
		return id;
	}
	string get_name() const
	{
		return name;
	}
	string get_password() const
	{
		return password;
	}

	virtual void display() const
	{
		cout << "ID.. = " << id << "\n\n";
		cout << "Name = " << name << "\n\n";
	}
};