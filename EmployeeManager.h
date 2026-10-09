#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Person.h"
#include "Client.h"
#include "Employee.h"
#include "Admin.h"
#include "ClientManger.h"
#include "FilesHelper.h"
#include "Utils.h"
using namespace std;

class EmployeeManager
{
public:
    static inline vector<Employee> employees;
    static inline vector<Client> clients;
    static inline vector<Employee> admins;

    static void printEmployeMenu()
    {
        cout << "\n=-=-=-=-=-=-=-=-=- Client Menu -=-=-=-=-=-=-=-=-=\n\n"

            << "1- Display My Data\n\n"

            << "2- Add new client\n\n"

            << "3- List all clients\n\n"

            << "4- Search for client\n\n"

            << "5- Edit client info\n\n"

            << "6- Delete client\n\n"

            << "7- Deposit to client\n\n"

            << "8- Withdraw from client\n\n"

            << "9- Check client balance\n\n"

            << "10- Update password\n\n"

            << "11- Logout\n\n"

            << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n "

            << "Your choice: ";
    }

    static void newClient(Employee* employee)
    {
        int id;
        string name, pass;
        double balance;

        cout << "Please,Enter client id: ";
        cin >> id;

        if (employee->searchClient(id) != nullptr)
        {
            cout << "This ID Already Exists \n\n";
            return;
        }

        cin.ignore();
        cout << "Please,Enter client Name: \n\n";
        getline(cin, name);

        while (!Validation::valid_name(name))
        {
            cout << "Invalid name! Alphabetic only, 3-20 chars. Try again: ";
            getline(cin, name);
        }

        cout << "Please,Enter Client Password: ";
        cin >> pass;

        while (!Validation::valid_Password(pass))
        {
            cout << "Try again: Invalid Password ";
            cin >> pass;
        }

        cout << "Please,Enter Client Balance: ";
        cin >> balance;

        while (!Validation::valid_balance(balance))
        {
            cout << "Try again: Balance must be at least 1500 ";
            cin >> balance;
        }

        Client c (id, name, pass, balance);
        employee->addClient(c);

        FilesHelper::saveClient(c);
    }

    static void listAllClients(Employee* employee)
    {
        employee->listClients();
    }

    static void searchForClient(Employee* employee)
    {
        int id;
        cout << "Enter client id: ";
        cin >> id;

        Client* c = employee->searchClient(id);

        if (c == nullptr)
        {
            cout << "Client not found.\n";
            return;
        }
           c->display();
    }

    static void editClientInfo(Employee* employee)
    {
        int id;
        string name, pass;
        double balance;

        cout << "Please,Enter New Client Id: ";
        cin >> id;

        if (employee->searchClient(id) == nullptr)
        {
            cout << "Client not found.\n\n";
            return;
        }


        cin.ignore();
        cout << "Please,Enter New Client Name: \n\n";
        getline(cin, name);


        while (!Validation::valid_name(name))
        {
            cout << "Try Again: Invalid name ";
            getline(cin, name);
        }

        cout << "Please,Enter New Client Password: ";
        cin >> pass;


        while (!Validation::valid_Password(pass))
        {
            cout << "Try again: Invalid Password ";
            cin >> pass;
        }


        cout << "Please,Enter New Client Balance: ";
        cin >> balance;


        while (!Validation::valid_balance(balance))
        {
            cout << "Try again: Balance must be at least 1500 ";
            cin >> balance;
        }

        employee->editClient(id, name, pass, balance);

        FilesHelper::saveAllClients(Employee::clientsList);
    }

    static Employee* login(int id, string password)
    {
        for (auto& c : employees)
        {
            if (c.get_id() == id && c.get_password() == password)
            {
                return &c;
            }
        }
        return nullptr;
    }

    static bool employeeOptions(Employee* employee)
    {
        Utils::clearScreen();

        printEmployeMenu();

        int choice;
        cin >> choice;

        Utils::clearScreen();

        int id;
        double amount;

        switch (choice)
        {
        case 1:

            employee->display();
            break;

        case 2:

            newClient(employee);
            break;

        case 3:

            listAllClients(employee);
            break;

        case 4:

            searchForClient(employee);
            break;

        case 5:

            editClientInfo(employee);
            break;

        case 6:

            cout << "Please,Enter client id to delete: ";
            cin >> id;

            employee->deleteClient(id);

            FilesHelper::saveAllClients(Employee::clientsList);

            break;

        case 7:
            cout << "Please,Enter client id: ";
            cin >> id;

            cout << "Please,Enter amount: ";
            cin >> amount;

            employee->depositToClient(id, amount);

            FilesHelper::saveAllClients(Employee::clientsList);

            break;

        case 8:
            cout << "Please,Enter client id: ";
            cin >> id;

            cout << "Please,Enter amount: ";
            cin >> amount;

            employee->withdrawFromClient(id, amount);

            FilesHelper::saveAllClients(Employee::clientsList);

            break;

        case 9:
            cout << "Please,Enter client id: ";
            cin >> id;

            employee->checkClientBalance(id);

            break;

        case 10:
            if (ClientManger::updatePassword(employee))
                FilesHelper::saveAllEmployees(employees);

            break;

        case 11:

            return false;

        default:

            cout << "\nInvalid choice.\n";
        }

        Utils::pause();

        return true;
    }
};