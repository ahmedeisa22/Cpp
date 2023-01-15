#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "clsUtil.h"
class clsUser: public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;

	string _UserName;
	string _password;
	int _permission;
	bool _MarkDelete = false;

	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;


		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::decryptedName(LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}
	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += clsUtil::encryptedName(Password) + Seperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}
	static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#") {
		vector<string> vUserData = clsString::Split(Line, Seperator);
		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3]
			, vUserData[4], clsUtil::decryptedName(vUserData[5]), stoi(vUserData[6]));
	}
	static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
	{

		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.UserName + Seperator;
		UserRecord +=clsUtil::encryptedName(User.Password) + Seperator;
		UserRecord += to_string(User.Permissions);
		return UserRecord;
	}
	static  vector <clsUser> _LoadUsersDataFromFile() {
		vector<clsUser> vUsers;
		fstream MyFile("Users.txt", ios::in); // read mode
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser user = _ConvertLinetoUserObject(Line);
				vUsers.push_back(user);
			}
			MyFile.close();
		}
		return vUsers;
	}
	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsUser U : vUsers)
			{
				if (U.MarkedForDeleted() == false)
				{
					//we only write records that are not marked for delete.  
					DataLine = _ConverUserObjectToLine(U);
					MyFile << DataLine << endl;

				}

			}

			MyFile.close();

		}

	}
	void _Update()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == UserName)
			{
				U = *this;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);

	}
	void _AddNew()
	{

		_AddDataLineToFile(_ConverUserObjectToLine(*this));
	}
	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode,"","","","","","",0);
	}
	static string EnctyptedPassword(string Password)
	{
		return clsUtil::encryptedName(Password);
	}
	
public:
	enum enMainMenuePermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2,
		pDeleteClient = 4, pUpdateClients = 8,
		pFindClient = 16, pTranactions = 32,
		pManageUsers = 64, pShowLoginRegister = 128
	};
	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;

	};

	clsUser() = default;
	clsUser(enMode Mode, string firstName, string lastName, string Email, string phone, string userName, string password,int permission)
		: clsPerson(firstName, lastName, Email, phone), _Mode(Mode),_UserName(userName),_password(password),_permission(permission) {}

	bool IsEmpty() {
		return _Mode == enMode::EmptyMode;
	}
	bool MarkedForDeleted() {
		return _MarkDelete;
	}
	string GetUserName() {
		return _UserName;
	}
	void setUserName(string user) {
		this->_UserName = user;
	}
	__declspec(property(get = GetUserName, put = setUserName))string UserName;
	void SetPassword(string Password)
	{
		_password = Password;
	}
	string GetPassword()
	{
		return _password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;
	void SetPermissions(int Permissions)
	{
		_permission = Permissions;
	}
	int GetPermissions()
	{
		return _permission;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string userName) {
		vector<clsUser> vUsers = _LoadUsersDataFromFile();
		for (clsUser U : vUsers) {
			if (U.UserName == userName)
				return U;
		}
		return _GetEmptyUserObject();
	}
	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();

		}
		return _GetEmptyUserObject();
	}
	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };
	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (clsUser::IsUserExists(_UserName))
			{
				return enSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}

	}
	bool Delete()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkDelete = true;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);

		*this = _GetEmptyUserObject();

		return true;

	}
	static bool IsUserExists(string userName) {
		clsUser user = Find(userName);
		return !(user.IsEmpty());
	}
	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}
	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}
	bool CheckAccessPermission(enMainMenuePermissions Permission) {
		if (enMainMenuePermissions::eAll == _permission)
			return true;
		if ((Permission & _permission) == Permission)
			return true;
		return false;
	}
	void RegisterLogIn()
	{

		string stDataLine = _PrepareLogInRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
	static  vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{

				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLoginRegisterRecord.push_back(LoginRegisterRecord);

			}

			MyFile.close();

		}

		return vLoginRegisterRecord;

	}

};

