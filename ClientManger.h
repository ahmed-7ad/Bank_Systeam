#pragma once
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include "Person.h"
#include "Client.h"
#include "Employee.h"
#include "Admin.h"
#include "Utils.h"
#include "FilesHelper.h"
using namespace std;



class ClientManger
{
public:

    static void printClientMenu()
    {
        cout << "\n=-=-=-=-=-=-=-=-=- Client Menu -=-=-=-=-=-=-=-=-=\n\n"

            << "1- Display My Data \n\n"

            << "2- Check balance\n\n"

            << "3- Deposit\n\n"

            << "4- Withdraw\n\n"

            << "5- Transfer to another client\n\n"

            << "6- Update password\n\n"

            << "7- Logout\n\n"

            << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n "

            << "Your choice: ";
    }

   
    static bool updatePassword(Person* person)
    {
        string Npass;

        cout << "Please,Enter Your New Password: ";

        cin >> Npass;

        if (!Validation::valid_Password(Npass))
        {
            cout << "\n\nInvalid password! Must be 8-20 chars.\n\n";

            return false;
        }

        person->set_password(Npass);

        cout << "\n\n Password updated successfully \n\n";

        return true;
    }

    static Client* login(int id, string password)
    {
        for (auto& c : Employee::clientsList)
        {
            if (c.get_id() == id && c.get_password() == password)
            {
                return &c;
            }
        }
        return nullptr;
    }

    static bool clientOptions(Client* client)
    {

        Utils::clearScreen();
        printClientMenu();

        int choice;
        cin >> choice;

        Utils::clearScreen();

        double amount = 0;

        switch (choice)
        {
        case 1:

            client->display();
            break;

        case 2:

            cout << "Your Balance = : " << client->get_balance() << endl;
            break;

        case 3:

            cout << "Please,Enter Amount: ";
            cin >> amount;

            client->deposit(amount);

            FilesHelper::saveAllClients(Employee::clientsList);

            break;

        case 4:

            cout << "Please,Enter Amount: ";
            cin >> amount;

            client->withdraw(amount);

            FilesHelper::saveAllClients(Employee::clientsList);

            break;

        case 5:
        {
            int to_id;
            cout << "Please,Enter Recipient Account ID: ";
            cin >> to_id;

            if (to_id == client->get_id())
            {
                cout << "You can't transfer to your own account.\n";
                break;
            }

            cout << "Please,Enter Amount: ";
            cin >> amount;

            bool Flag = false;

            for (auto& c : Employee::clientsList)
            {
                if (c.get_id() == to_id)
                {
                    client->transfer_to(amount, c);

                    FilesHelper::saveAllClients(Employee::clientsList);
                    Flag = true;

                    break;
                }
            }
            if (!Flag)
            {
                cout << "Client not found.\n";
            }
            break;
        }

        case 6:

            if (updatePassword(client)) {
                FilesHelper::saveAllClients(Employee::clientsList);
            }

            break;

        case 7:

            return false;

        default:
            cout << "Invalid choice.\n";
        }

        Utils::pause();
        return true;
    }
};