#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"
#include "Employee.h"
#include "Admin.h"
#include "ClientManger.h"
#include "EmployeeManager.h"
#include "AdminManager.h"
#include "FilesHelper.h"
#include "Utils.h"

using namespace std;

class Screens
{
public:

	static void welcome()
	{
		cout << "\n\n\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t*       *  ********  *         ******   ******   *       *  ********\n";
		cout << "\t\t\t*       *  *         *        *        *      *  **     **  *       \n";
		cout << "\t\t\t*   *   *  ******    *        *        *      *  * *   * *  ******  \n";
		cout << "\t\t\t * * * *   *         *        *        *      *  *  * *  *  *       \n";
		cout << "\t\t\t  *   *    ********  ********  ******   ******   *   *   *  ********\n";
		Utils::pause();
		Utils::clearScreen();
	}

	static void loginOptions()
	{
		cout << "\n =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Bank System -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n";
		cout << "\n Login as: \n\n"
			<< "1- Client\n\n"
			<< "2- Employee\n\n"
			<< "3- Admin\n\n"
			<< "0- Exit\n\n"
		 << "\n =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n"
			<< "Your choice: \n\n";
	}

	static int loginAs()
	{
		int Choice;
		cin >> Choice;
		return Choice;
	}

	static void invalid(int Choice)
	{
		cout << "\nInvalid choice (" << Choice << ") Please,try again\n\n";
		Utils::pause();
	}

	static void logout()
	{
		cout << "\nLogged out successfully\n\n";
		Utils::pause();
	}

	static void wrongLogin()
	{
		cout << "\nWrong ID or Password.\n\n";
		Utils::pause();
	}

	static void loginScreen(int Choice)
	{
		int Id = 0;
		string Pass;

		Utils::clearScreen();

		cout << "Please,Enter ID: ";
		cin >> Id;

		cout << "Please,Enter Password: ";
		cin >> Pass;

		switch (Choice)
		{
		case 1:
		{
			Client* client = ClientManger::login(Id, Pass);
			if (client == nullptr)
			{
				wrongLogin();
				return;
			}
			while (ClientManger::clientOptions(client))
			{
			}
			break;
		}
		case 2:
		{
			Employee* employee = EmployeeManager::login(Id, Pass);
			if (employee == nullptr)
			{
				wrongLogin();
				return;
			}
			while (EmployeeManager::employeeOptions(employee))
			{
			}
			break;
		}
		case 3:
		{
			Admin* admin = AdminManager::login(Id, Pass);
			if (admin == nullptr)
			{
				wrongLogin();
				return;
			}
			while (AdminManager::AdminOptions(admin))
			{
			}
			break;
		}
		}
		logout();
	}

	static void loadData()
	{
		Employee::clientsList = FilesHelper::getClients();
		EmployeeManager::employees = FilesHelper::getEmployees();

		vector<Admin*> admins = FilesHelper::getAdmins();

		if (!admins.empty())
		{
			Admin* a = admins[0];
			Admin::getInstance(a->get_id(), a->get_name(), a->get_password(), a->get_salary());
		}
	}

	static void runApp()
	{
		loadData();

		while (true)
		{
			Utils::clearScreen();

			welcome();

			loginOptions();

			int Choice = loginAs();

			if (Choice == 0)
			{
				break;
			}

			if (Choice >= 1 && Choice <= 3)
			{
				loginScreen(Choice);
			}
			else
			{
				invalid(Choice);
			}
		}

		Utils::clearScreen();

		cout << "Thanks\n\n";
	}

};