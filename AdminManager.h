#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"
#include "Employee.h"
#include "Admin.h"
#include "ClientManger.h"
#include "EmployeeManager.h"
#include "FilesHelper.h"
#include "Utils.h"

using namespace std;

class AdminManager
{
public:

    static void printAdminMenu()
    {
        cout << "\n=-=-=-=-=-=-=-=-=- Admin Menu -=-=-=-=-=-=-=-=-=\n\n"

            << "1- Display My Data\n\n"

            << "2- Add new employee\n\n"

            << "3- List all employees\n\n"

            << "4- Search for employee\n\n"

            << "5- Edit employee info\n\n"

            << "6- Delete employee\n\n"

            << "7- Update password\n\n"

            << "8- Logout\n\n"

            << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n "

            << "Your choice: ";
    }

    static Admin* login(int id, string password)
    {
        Admin* admin = Admin::getInstance();

        if (admin->get_id() == id && admin->get_password() == password)
        {
            return admin;
        }
        return nullptr;
    }

    static bool AdminOptions(Admin* admin)
    {
        Utils::clearScreen();
        printAdminMenu();

        int choice = 0;
        cin >> choice;

        Utils::clearScreen();

        int id = 0;
        string name, pass;
        double salary = 0;

        switch (choice)
        {
        case 1:

            admin->display();

            break;
            

        case 2:
        {
            cout << "Please,Enter employee id: ";
            cin >> id;

            if (admin->findEmployee(EmployeeManager::employees, id) != nullptr)
            {
                cout << "This ID already exists.\n";
                break;
            }

            cin.ignore();
            cout << "Please,Enter employee name: ";
            getline(cin, name);

            while (!Validation::valid_name(name))
            {
                cout << "Invalid name! Alphabetic only, 3-20 chars. Try again: ";
                getline(cin, name);
            }

            cout << "Please,Enter employee password: ";
            cin >> pass;

            while (!Validation::valid_Password(pass))
            {
                cout << "Invalid password! Must be 8-20 chars. Try again: ";
                cin >> pass;
            }

            cout << "Please,Enter employee salary: ";
            cin >> salary;

            while (!Validation::valid_salary(salary))
            {
                cout << "Salary must be at least 5000. Try again: ";
                cin >> salary;
            }

            Employee e(id, name, pass, salary);
            admin->addEmployee(EmployeeManager::employees, e);

            FilesHelper::saveEmployee("Employee.txt", "EmployeeLastId.txt", e);

            break;
        }
   
        case 3:

            admin->listEmployees(EmployeeManager::employees);
            break;

        case 4:
        {
            cout << "Please,Enter employee id: ";
            cin >> id;

            Employee* e = admin->findEmployee(EmployeeManager::employees, id);

            if (e == nullptr)
            {
                cout << "Employee not found.\n";
            }
            else
            {
                e->display();
            }
            break;
        }
        
        case 5:
        {
            cout << "Please,Enter employee id to edit: ";
            cin >> id;

            if (admin->findEmployee(EmployeeManager::employees, id) == nullptr)
            {
                cout << "Employee not found.\n";
                break;
            }

            cin.ignore();
            cout << "Please,Enter new employee name: ";
            getline(cin, name);

            while (!Validation::valid_name(name))
            {
                cout << "Invalid name! Alphabetic only, 3-20 chars. Try again: ";
                getline(cin, name);
            }

            cout << "Please,Enter new employee password: ";
            cin >> pass;

            while (!Validation::valid_Password(pass))
            {
                cout << "Invalid password! Must be 8-20 chars. Try again: ";
                cin >> pass;
            }

            cout << "Please,Enter new employee salary: ";
            cin >> salary;

            while (!Validation::valid_salary(salary))
            {
                cout << "Salary must be at least 5000. Try again: ";
                cin >> salary;
            }

            admin->editEmployee(EmployeeManager::employees, id, name, pass, salary);

            FilesHelper::saveAllEmployees(EmployeeManager::employees);

            break;
        }

        case 6:

            cout << "Please,Enter employee id to delete: ";
            cin >> id;

            admin->deleteEmployee(EmployeeManager::employees, id);

            FilesHelper::saveAllEmployees(EmployeeManager::employees);

            break;

        case 7:

            if (ClientManger::updatePassword(admin))
                FilesHelper::saveAdmin(*admin);

            break;

        case 8:

            return false;

        default:

            cout << "Invalid choice.\n";
        }

        Utils::pause();

        return true;
    }
};