#pragma once
#include <string>
#include <iostream>
#include "Person.h"
using namespace std;

class Client : public Person
{
private:
	double balance;

public:
	Client(int id, string name, string password, double balance)
		: Person(id, name, password)
	{
		set_balance(balance);
	}

	void set_balance(double balance)
	{
		Validation::valid_balance(balance);
		this->balance = balance;
	}

	double get_balance() const
	{
		return balance;
	}

	void deposit(double amount)
	{
		if (amount <= 0)
		{
			cout << "Deposit not Valid\n\n";
			return;
		}
		balance += amount;
		cout << "Deposit is Done\nNew balance = " << balance << "\n\n";
	}

	void withdraw(double amount)
	{
		if (amount <= 0)
		{
			cout << "Withdraw not Valid\n\n";
			return;
		}
		if (amount > balance)
		{
			cout << "Insufficient balance\n\n";
			return;
		}
		balance -= amount;
		cout << "Withdraw successful \n New balance = " << balance << "\n\n";
	}

	void transfer_to(double amount, Client& recipient)
	{
		if (amount <= 0)
		{
			cout << "Transfer amount not Valid\n\n";
			return;
		}
		if (amount > balance)
		{
			cout << "Insufficient balance for transfer\n\n";
			return;
		}

		balance -= amount;
		recipient.deposit(amount);

		cout << "Transferred " << amount << " to " << recipient.get_name() << "\n\n";
	}

	void check_balance() const
	{
		cout << "Current Balance = " << balance << "\n\n";
	}

	void display() const override
	{
		cout << "=-=-=-= Client Info =-=-=-=\n\n";
		Person::display();
		cout << "Balance = " << balance << "\n\n";
	}
};