#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Addition {
public:
	static void createFiles() {
		ofstream clientfile("Client.txt", ios::app);
		ofstream employeefile("Employee.txt", ios::app);
		ofstream adminfile("Admin.txt", ios::app);

		if (!clientfile.is_open())
			cout << "Not Valid Client.txt \n";
		else
			cout << "Client.txt is undercontrol \n";

		if (!employeefile.is_open())
			cout << "Not Valid Employee.txt \n";
		else
			cout << "Employee.txt is undercontrol \n";

		if (!adminfile.is_open())
			cout << "Not Valid Admin.txt \n";
		else
			cout << "Admin.txt is undercontrol \n";

		clientfile.close();
		employeefile.close();
		adminfile.close();
	}
};
