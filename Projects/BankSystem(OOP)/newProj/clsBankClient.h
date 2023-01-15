#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
class clsBankClient: public clsPerson
{
private:

	enum enMode {EmptyMode = 0 , UpdateMode = 1, AddNewMode = 2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;
	struct stTransferLogin;
	static stTransferLogin _ConvertLoginTransferLineToRecord(string Line, string Seperator = "#//#")
	{
		stTransferLogin LoginTransfer;

		vector <string> LoginTransferDataLine = clsString::Split(Line, Seperator);
		LoginTransfer.DateTime = LoginTransferDataLine[0];
		LoginTransfer.AccountFrom = LoginTransferDataLine[1];
		LoginTransfer.AccountTo = LoginTransferDataLine[2];
		LoginTransfer.AmountTransfer = stoi(LoginTransferDataLine[3]);
		LoginTransfer.BalanceFrom = stoi(LoginTransferDataLine[4]);
		LoginTransfer.Balanceto = stoi(LoginTransferDataLine[5]);
		LoginTransfer.UserName = LoginTransferDataLine[6];
		return LoginTransfer;
	}
	static  vector <stTransferLogin> _LoadTransferDataFromFile()
	{

		vector <stTransferLogin> vtransfers;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				stTransferLogin trans = _ConvertLoginTransferLineToRecord(Line);
				vtransfers.push_back(trans);
			}

			MyFile.close();
		}
		return vtransfers;
	}
	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#") {
		vector<string> vClientData = clsString::Split(Line,Seperator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3]
			, vClientData[4], vClientData[5],stod(vClientData[6]));
	}
	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.getAccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;

	}
	static  vector <clsBankClient> _LoadClientsDataFromFile()
	{

		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLinetoClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();

		}

		return vClients;

	}
	static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsBankClient C : vClients)
			{
				if (!C._MarkedForDelete) {
					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
				
			}

			MyFile.close();

		}

	}
	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.getAccountNumber() == getAccountNumber())
			{
				C = *this;
				break;
			}

		}

		_SaveCleintsDataToFile(_vClients);
	}
	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
	void _AddNew() {
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}
	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "","", 0);
	}

	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#")
	{
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += getAccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.getAccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;
		return TransferLogRecord;
	}
	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
	{

		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

public:
	clsBankClient() = default;
	clsBankClient(enMode Mode, string firstName, string lastName, string Email, string phone,string accountNumber,string Pincode,double balance)
		: clsPerson(firstName, lastName, Email, phone), _Mode(Mode),_AccountNumber(accountNumber),_PinCode(Pincode),_AccountBalance(balance)
	{}
	struct stTransferLogin {
		string DateTime;
		string AccountFrom;
		string AccountTo;
		double AmountTransfer;
		double BalanceFrom;
		double Balanceto;
		string UserName;
	};
	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}
	// read only 
	string getAccountNumber()const {
		return _AccountNumber;
	}

	void setPinCode(string pin) {
		_PinCode = pin;
	}
	string getPinCode()const {
		return _PinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	void setAccountBalance(double balance) {
		_AccountBalance = balance;
	}
	double getAccountBalance()const {
		return _AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) double AccountBalance;

	/*void Print()
	{
	// no UI method inside class 
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}*/
	static clsBankClient Find(string AccountNumber){
		fstream File;
		File.open("Clients.txt", ios::in); // read mode
		if (File.is_open()) {

			string Line;
			while (getline(File, Line)) {
				clsBankClient clinet = _ConvertLinetoClientObject(Line);
				if (clinet.getAccountNumber() == AccountNumber) {
					File.close();
					return clinet;
				}
			}

		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber,string Password) {
		fstream File;

		File.open("Clients.txt", ios::in); // read mode
		if (File.is_open()) {

			string Line;
			while (getline(File, Line)) {
				clsBankClient clinet = _ConvertLinetoClientObject(Line);
				if (clinet.getAccountNumber() == AccountNumber && clinet.PinCode == Password) {
					File.close();
					return clinet;
				}
			}

		}
		return _GetEmptyClientObject();
	}
	static bool IsClientExists(string AccountNumber) {
		clsBankClient client = Find(AccountNumber);
		return !(client.IsEmpty());
	}

	enum enSaveResult {svFaildEmployeObject = 0 , svSucceeded = 1, svFaildAccountNumberExists = 2};
	enSaveResult Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode: {
			if(IsEmpty())
			return enSaveResult::svFaildEmployeObject;
		}
		case enMode::UpdateMode: {
			_Update();
			return enSaveResult::svSucceeded;
		}
		case enMode::AddNewMode: {
			if (IsClientExists(getAccountNumber()))
				return enSaveResult::svFaildAccountNumberExists;

			_AddNew();
			_Mode = enMode::UpdateMode;
			return enSaveResult::svSucceeded;
		}
	
		}
	}
	static clsBankClient getAddNewClientObject(string accountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
	}
	bool Delete() {
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.getAccountNumber() == getAccountNumber())
			{
				C._MarkedForDelete = true;
				break;
			}

		}

		_SaveCleintsDataToFile(_vClients);
		*this = _GetEmptyClientObject();
		return true  ;
	}
	static vector<clsBankClient> GetClientList() {
		return _LoadClientsDataFromFile();
	}
	static double GetTotalBalances() {
		double TotalBalances = 0;
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient C : vClients)
		{
			TotalBalances += C.AccountBalance;
		}
		return TotalBalances;
	}
	 void Deposite( double amount) {
					this->_AccountBalance += amount;
					Save();
	}
	 bool Withdraw(double amount) {
		 if (amount > this->AccountBalance) {
			 return false;
		 }
		 else {
			 this->_AccountBalance -= amount;
			 Save();
			 return true;
		 }
	 }
	 bool Transfer(int amount, clsBankClient& DestinationClient, string UserName) {
		 if (amount > this->AccountBalance) {
			 return false;
		 }
		 Withdraw(amount);
		 DestinationClient.Deposite(amount);
		 _RegisterTransferLog(amount, DestinationClient, UserName);
		 return true;
	 }
	 static  vector <stTransferLogin> GetTransferterList() {
		 return _LoadTransferDataFromFile();
	 }
};

