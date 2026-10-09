#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Employee.h"
using namespace std;

class Admin : public Employee
{
private:
	Admin(int id = 0, const string& name = "", const string& password = "", double salary = 0.0)
		: Employee(id, name, password,salary) {
	}

public:
	Admin(const Admin&) = delete;
	Admin& operator=(const Admin&) = delete;


	void updateData(int id, const string& name, const string& password, double salary)
	{
		this->set_id(id);
		this->set_name(name);
		this->set_password(password);
		this->set_salary(salary);
	}

	static Admin* getInstance(int id = 0, const string& name = "", const string& password = "", double salary = 0.0)
	{
		//once:
		static Admin instance(id, name, password, salary);

		if (id != 0 || !name.empty())
		{
			instance.updateData(id, name, password,salary);
		}

		return &instance;
	}

	void addEmployee(vector<Employee>& employees, const Employee& employee)
	{
		employees.push_back(employee);
		cout << "Employee added successfully\n";
	}

	Employee* findEmployee(vector<Employee>& employees, int employeeId)
	{
		for (auto& employee : employees)
		{
			if (employee.get_id() == employeeId)
			{
				return &employee;
			}
		}
		return nullptr;
	}

	void editEmployee(vector<Employee>& employees, int employeeId, const string& newName, const string& newPassword,double newSalary)
	{
		Employee* employee = findEmployee(employees, employeeId);
		if (employee)
		{
			employee->set_name(newName);
			employee->set_password(newPassword);
			employee->set_salary(newSalary);
			cout << "Employee information updated successfully\n\n";
		}
		else
		{
			cout << "Error: Employee with ID " << employeeId << " not found\n\n";
		}
	}

	void listEmployees(const vector<Employee>& employee) const
	{
		cout << "\n=-=-=-=-=-=-=-=--=--=-=-- List of Employees =-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n";
		if (employee.empty())
		{
			cout << "No employees found.\n\n";
			return;
		}
		cout << "List of Employees:\n\n";
		for (const auto& employee : employee)
		{
			employee.display();
			cout << "\n\n------------------------------------------------------------------\n\n";
		}
	}

	void deleteEmployee(vector<Employee>& employees, int employeeId)
	{
		auto it = find_if(employees.begin(), employees.end(), [employeeId](const Employee& employee) {
			return employee.get_id() == employeeId;
			});
		if (it != employees.end())
		{
			employees.erase(it);
			cout << "Employee with ID " << employeeId << " deleted successfully\n\n";
		}
		else
		{
			cout << "Error: Employee with ID " << employeeId << " not found\n\n";
		}
	}



	void display() const override
	{
		cout << "=-=-=-= Admin Info =-=-=-=\n\n";
		Employee::display();
	}
};