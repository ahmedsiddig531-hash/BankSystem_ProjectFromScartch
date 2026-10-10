#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainMenuScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:

    static  bool _Login()
    {
        bool LoginFaild = false;
		short Trails = 0;
        
        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                Trails++;
                cout << "\nInvlaid Username/Password!\n\n";
				cout << "You have " << 3 - Trails << " Trails left!\n\n";
                 
            }

			if (Trails == 3)
			{
				cout << "\nYou have exceeded the maximum number of login attempts.\n";
				return false;
			}

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser.RegisterLogin();
        clsMainScreen::ShowMainMenue();

        return true;
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();

    }

};

