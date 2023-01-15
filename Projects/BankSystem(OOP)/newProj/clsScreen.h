#pragma once
#include <iostream>
#include "Global.h"
#include "clsUser.h"
using namespace std;
class clsScreen
{

protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n";
        cout << "\n\t\t\t\t\tUser: " << CurrentUser.GetUserName() << "\n";
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate()) << "\n\n";
    }
    static void _accesDenied() {
        cout << "\n-------------------------------------------------------------\n";
        cout << "Acess isDenied,\nyou don't have permission to do this,\n";
        cout << "Please contact your Admin\n";
        cout << "\n-------------------------------------------------------------\n";
    }
    static bool CheckAccessRights(clsUser::enMainMenuePermissions Permission)
    {

        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }

    }
  
};

