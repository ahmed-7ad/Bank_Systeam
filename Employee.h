#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Person.h"
#include "Validation.h"
#include "Client.h"
using namespace std;

class Employee : public Person
{
protected:
    double salary;

public:
    Employee(int id, const string& name, const string& password, double salary)
        : Person(id, name, password)
    {
        set_salary(salary);
    }

    void set_salary(double salary)
    {
        if (Validation::valid_salary(salary))
            this->salary = salary;
        else
            this->salary = 5000;
    }

    double get_salary() const
    {
        return salary;
    }

    static inline vector<Client> clientsList;

    void addClient(const Client& client)
    {
        clientsList.push_back(client);
        cout << "Client added successfully.\n";
    }

    Client* searchClient(int id)
    {
        for (auto& client : clientsList)
        {
            if (client.get_id() == id)
                return &client;
        }
        return nullptr;
    }

    void listClients() const
    {
        cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=- List of Clients =-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n";

        if (clientsList.empty())
        {
            cout << "No clients found.\n";
            return;
        }

        for (const auto& client : clientsList)
        {
            client.display();
            cout << "\n\n-------------------------------------------------------------------\n\n";
        }
    }

    void displayClient(int id)
    {
        Client* client = searchClient(id);

        if (client)
            client->display();
        else
            cout << "Error: Client with ID " << id << " not found!\n";
    }

    void editClient(int id, const string& newName, const string& newPassword, double newBalance)
    {
        Client* client = searchClient(id);

        if (client)
        {
            client->set_name(newName);
            client->set_password(newPassword);
            client->set_balance(newBalance);
            cout << "Client information updated successfully \n\n";
        }
        else
        {
            cout << "Error: Client with ID " << id << " not found\n\n";
        }
    }

    void deleteClient(int id)
    {
        auto it = remove_if(clientsList.begin(), clientsList.end(),
            [id](const Client& client)
            {
                return client.get_id() == id;
            });

        if (it != clientsList.end())
        {
            clientsList.erase(it, clientsList.end());
            cout << "Client with ID " << id << " deleted successfully\n";
        }
        else
        {
            cout << "Error: Client with ID " << id << " not found\n\n";
        }
    }

    void depositToClient(int id, double amount)
    {
        Client* client = searchClient(id);

        if (client)
            client->deposit(amount);
        else
            cout << "Error: Client with ID " << id << " not found\n\n";
    }

    void withdrawFromClient(int id, double amount)
    {
        Client* client = searchClient(id);

        if (client)
            client->withdraw(amount);
        else
            cout << "Error: Client with ID " << id << " not found\n\n";
    }

    void checkClientBalance(int id)
    {
        Client* client = searchClient(id);

        if (client)
            client->check_balance();
        else
            cout << "Error: Client with ID " << id << " not found!\n\n";
    }

    void display() const override
    {
        cout << "=-=-=-= Employee Info =-=-=-=\n\n";
        Person::display();
        cout << "Salary = " << get_salary() << "\n\n";
    }
};