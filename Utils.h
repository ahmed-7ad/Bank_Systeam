#pragma once
#include <cstdlib>
#include <iostream>
#include <limits>
using namespace std;

class Utils
{
public:
    static void clearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static void pause()
    {
        //cout << "\n Press Enter to continue \n";

        cin.ignore(numeric_limits < streamsize>::max(), '\n');
        cin.get();
    }
};




 