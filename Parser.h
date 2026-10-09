#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "Client.h"
#include "Employee.h"
#include "Admin.h"
using namespace std;

class Parser
{

private:

    static vector<string> split(const string& line)
    {
        vector<string> result;
        string token;
        stringstream stream(line);

        while (getline(stream, token, '&'))
        {
            result.push_back(token);
        }

        return result;
    }

public:

    static Client parseToClient(const string& line)
    {
        vector<string> parts = split(line);

        if (parts.size() < 4)
        {
            cout << "Invalid client line format: " << line << "\n";
            return Client(0, "Invalid", "00000000", 0);
        }

        try
        {
            return Client(stoi(parts[0]), parts[1], parts[2], stod(parts[3]));
        }
        catch (const exception&)
        {
            cout << "Invalid client data: " << line << "\n";
            return Client(0, "Invalid", "00000000", 0);
        }
    }

    static Employee parseToEmployee(const string& line)
    {
        vector<string> parts = split(line);

        if (parts.size() < 4)
        {
            cout << "Invalid employee line format: " << line << "\n\n";
            return Employee(0, "Invalid", "00000000", 0);
        }

        try
        {
            return Employee(stoi(parts[0]), parts[1], parts[2], stod(parts[3]));
        }
        catch (const exception&)
        {
            cout << "Invalid employee data: " << line << "\n";
            return Employee(0, "Invalid", "00000000", 0);
        }
    }

    static Admin* parseToAdmin(const string& line)
    {
        vector<string> parts = split(line);

        if (parts.size() < 4)
        {
            cout << "Invalid admin line format: " << line << "\n";
            return nullptr;
        }

        try
        {
            Admin* admin = Admin::getInstance();
            admin->updateData(stoi(parts[0]), parts[1], parts[2], stod(parts[3]));
            return admin;
        }
        catch (const exception&)
        {
            cout << "Invalid admin data: " << line << "\n";
            return nullptr;
        }
    }
};