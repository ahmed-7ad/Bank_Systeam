#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Client.h"
#include "Employee.h"
#include "Admin.h"
using namespace std;

class Interface {
public:

	virtual void addclient(Client obj) = 0;
	virtual void addemployee(Employee obj) = 0;
	virtual void addadmin(Admin& obj) = 0;

	virtual void getallclients() = 0;
	virtual void getallemployees() = 0;
	virtual void getalladmins() = 0;

	virtual void removeallclients() = 0;
	virtual void removeallemployees() = 0;
	virtual void removealladmin() = 0;
};
