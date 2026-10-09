#pragma once
#include <iostream>
#include <vector>
#include "Admin.h"
#include "Client.h"
#include "Interface.h"
#include "FilesHelper.h"
using namespace std;

class FileManager : public Interface
{
public:
	// =-=-= Add =-=-=\\;

	void addclient(const Client& obj)
	{
		FilesHelper::saveClient(obj);
		Employee::clientsList.push_back(obj);
	}

	void addemployee(Employee obj) 
	{
		FilesHelper::saveEmployee("Employee.txt", "EmployeeLastid.txt", obj);
	}
	void addadmin(Admin& obj)
	{
		FilesHelper::saveEmployee("Admin.txt", "AdminLastid.txt", obj);
	}

	// =-=-= Get =-=-=\\;

	void getallclients()
	{
		Employee::clientsList = FilesHelper::getClients();
	}

	void  getallemployees() 
	{
		FilesHelper::getEmployees();
	}
	void getalladmins() 
	{
		FilesHelper::getAdmins();
	}

	// =-=-= Remove =-=-=\\;

	void removeallclients()
	{
		FilesHelper::clearFile("Clients.txt", "ClientLastid.txt");
		Employee::clientsList.clear();
	}
	void removeallemployees() 
	{
		FilesHelper::clearFile("Employee.txt", "EmployeeLastid.txt");
	}
	void removealladmin() 
	{
		FilesHelper::clearFile("Admin.txt", "AdminLastid.txt");
	}
};