#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Client.h"
#include "Employee.h"
#include "Admin.h"
#include "Parser.h"
using namespace std;

class FilesHelper
{
public:

    static inline vector<Employee> employees;
    static inline vector<Client> clients;

    static void saveLast(string fileName, int id)
    {
        ofstream file(fileName, ios::out | ios::trunc);
        if (file.is_open())
        {
            file << id;
            file.close();
        }
    }

    static int getLast(string fileName)
    {
        ifstream file(fileName, ios::in);
        int id = 0;
        if (file.is_open())
        {
            file >> id;
            file.close();
        }
        return id;
    }

    static void saveClient(Client c)
    {
        int id = getLast("ClientLastId.txt");
        if (c.get_id() == 0)
        {
            id++;
            c.set_id(id);
        }
        else if (c.get_id() > id)
        {
            id = c.get_id();
        }
        saveLast("ClientLastId.txt", id);

        ofstream file("Clients.txt", ios::app);
        if (file.is_open())
        {
            file << c.get_id() << "&" << c.get_name() << "&" << c.get_password() << "&" << c.get_balance() << "\n";
            file.close();
        }
    }

    static void saveEmployee(string fileName, string lastIdFile, Employee e)
    {
        int id = getLast(lastIdFile);

        if (e.get_id() == 0)
        {
            id++;
            e.set_id(id);
        }
        else if (e.get_id() > id)
        {
            id = e.get_id();
        }
        saveLast(lastIdFile, id);

        ofstream file(fileName, ios::app);
        if (file.is_open())
        {
            file << e.get_id() << "&" << e.get_name() << "&" << e.get_password() << "&" << e.get_salary() << "\n";
            file.close();
        }
    }


    static void saveAllClients(const vector<Client>& list)
    {
        ofstream file("Clients.txt", ios::out | ios::trunc);
        if (!file.is_open()) return;

        for (const auto& c : list)
        {
            file << c.get_id() << "&" << c.get_name() << "&" << c.get_password() << "&" << c.get_balance() << "\n";
        }
        file.close();
    }

    static void saveAllEmployees(const vector<Employee>& list)
    {
        ofstream file("Employee.txt", ios::out | ios::trunc);

        if (!file.is_open()) return;

        for (const auto& e : list)
        {
            file << e.get_id() << "&" << e.get_name() << "&" << e.get_password() << "&" << e.get_salary() << "\n";
        }
        file.close();
    }

    static void saveAdmin(const Admin& a)
    {
        ofstream file("Admin.txt", ios::out | ios::trunc);
        if (!file.is_open()) return;

        file << a.get_id() << "&" << a.get_name() << "&" << a.get_password() << "&" << a.get_salary() << "\n";
        file.close();
    }


    static vector<Client> getClients()
    {
        clients.clear();

        ifstream file("Clients.txt");

        if (!file.is_open())
        {
            return clients;
        }

        string line;

        while (getline(file, line))
        {
            if (!line.empty())
            {
                Client c = Parser::parseToClient(line);

                if (c.get_id() != 0)
                    clients.push_back(c);
            }
        }

        file.close();

        return clients;
    }

    static vector<Employee> getEmployees()
    {
        employees.clear();

        ifstream file("Employee.txt");

        if (!file.is_open())
        {
            return employees;
        }

        string line;

        while (getline(file, line))
        {
            if (!line.empty())
            {
                Employee e = Parser::parseToEmployee(line);

                if (e.get_id() != 0)
                    employees.push_back(e);
            }
        }

        file.close();

        return employees;
    }

    static vector<Admin*> getAdmins()
    {
        vector<Admin*> admins;
        ifstream file("Admin.txt");

        if (!file.is_open())
        {
            return admins;
        }

        string line;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                Admin* a = Parser::parseToAdmin(line);
                if (a != nullptr)
                {
                    admins.push_back(a);
                }
            }
        }
        file.close();
        return admins;
    }

    static void loadAdmin()
    {
        ifstream file("Admin.txt");
        string line;

        if (file.is_open() && getline(file, line) && !line.empty())
        {
            Parser::parseToAdmin(line);
        }
        else
        {
            Admin::getInstance()->updateData(1, "Admin", "12345678", 10000);
        }
        file.close();
    }

    static void clearFile(string fileName, string lastIdFile)
    {
        ofstream file(fileName, ios::out | ios::trunc);
        file.close();

        if (!lastIdFile.empty())
        {
            saveLast(lastIdFile, 0);
        }
    }
};