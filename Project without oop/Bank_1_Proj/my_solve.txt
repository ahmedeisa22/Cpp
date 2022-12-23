
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include<fstream>
#include <cstdlib>
#include <vector>
#include "Header.h"
/**********************************************************************************/
// my solution
/**********************************************************************************/
using namespace std;
const string FileName = "Clients.txt";
struct sClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "" ;
	double AccountBalance = 0;
	bool MarkDelete = false;
};
vector<string>Split(string str,string delimeter="#//#") {
	vector<string> result;
	string sWord = "";
	int pos = 0;

	while ((pos = str.find(delimeter)) != string::npos) {
		sWord = str.substr(0, pos);
		if (sWord != "")
			result.push_back(sWord);

		str.erase(0, pos + delimeter.length());
	}
	if (str != "")
		result.push_back(str);

	return result;
}
sClient ConverLineToRecord(string line, string delimeter = "#//#"){
	sClient clinet;
	vector<string> res = Split(line, delimeter);
	clinet.AccountNumber = res[0];
	clinet.PinCode = res[1];
	clinet.Name = res[2];
	clinet.Phone = res[3];
	clinet.AccountBalance = stod(res[4]);

	return clinet;
}
string ConvertRecordToLine(sClient client, string delimeter = "#//#"){
	string res = "";

	res += client.AccountNumber + delimeter;
	res += client.PinCode + delimeter;
	res += client.Name + delimeter;
	res += client.Phone + delimeter;
	res += to_string(client.AccountBalance);

	return res;
}
vector<sClient> LoadFromFileToVector(string file) {
	vector <sClient> vClients;
	fstream myFile;

	myFile.open(file, ios::in); // read mode
	if (myFile.is_open()) {
		string line;
		sClient client;
		while (getline(myFile, line)) {
			client = ConverLineToRecord(line);
			vClients.push_back(client);
		}
		myFile.close();
	}
	return vClients;
}
void ShowClient(sClient Client) {
	cout << "|" << setw(18) << left << Client.AccountNumber << "";
	cout << "|" << setw(12) << left << Client.PinCode << "";
	cout << "|" << setw(30) << left << Client.Name << "";
	cout << "|" << setw(20) << left << Client.Phone << "";
	cout << "|" << setw(15) << left << Client.AccountBalance << "\n";
	
}
void ShowClientINLines(sClient Client) {
	cout << "\nThe Following are the client details:\n";
	cout << "-------------------------------------------------------------\n";
	cout << "Account Number : "  << Client.AccountNumber << "\n";
	cout << "Code Pin       : " << Client.PinCode << "\n";
	cout << "Name           : " <<Client.Name << "\n";
	cout << "Phone Number   : " << Client.Phone << "\n";
	cout << "AccountBalance : " << Client.AccountBalance << "\n";
	cout << "----------------------------------------------------------------\n";
}
void pressAnyKeyToReturn() {
	cout << "\nPress any key to go back main menu...\n";
	system("pause>nul");
}
void showClients() {
	vector<sClient> vClients;

		// get clients from file
	vClients = LoadFromFileToVector(FileName);
	// show header
	cout << endl;
	cout << setw(60) << "Client List (" << vClients.size() << ") Client(s).\n";
	cout << "_____________________________________________________________________________________________________________________\n\n";
	cout << "|" << setw(18) << left << "AccountNumber" << "";
	cout << "|" << setw(12) << left << "PinCode" << "";
	cout << "|" << setw(30) << left << "Name" << "";
	cout << "|" << setw(20) << left << "Phone" << "";
	cout << "|" << setw(15) << left << "AccountBalance" << "\n";
	cout << "_____________________________________________________________________________________________________________________\n\n";


	// show acount data
	for (auto& acc : vClients) {
		ShowClient(acc);
	}
	cout << "_____________________________________________________________________________________________________________________\n\n\n";

	pressAnyKeyToReturn();

}
void Bank_menu() {
	

	cout << "***********************************************\n";
	cout << " \t\tMain Menu Screen\n";
	cout << "***********************************************\n";
	cout << "\t [1] Show Client List.\n";
	cout << "\t [2] Add New Client.\n";
	cout << "\t [3] Delete Client.\n";
	cout << "\t [4] Update Client.\n";
	cout << "\t [5] Find Client.\n";
	cout << "\t [6] Exit.\n";
	cout << "***********************************************\n";
	
}
sClient ReadClient() {
	sClient client;

	cout << "\nEnter Account Nuumber? ";
	getline(cin >> ws, client.AccountNumber);

	cout << "\nEnter Pin Code? ";
	getline(cin, client.PinCode);

	cout << "\nEnter Name? ";
	getline(cin, client.Name);

	cout << "\nEnter Phone? ";
	getline(cin, client.Phone);

	cout << "\nEnter AccountBalance? ";
	cin >> client.AccountBalance;

	return client;
}
sClient ReadNewClient(string AccountNumber) {
	sClient client;


	 client.AccountNumber = AccountNumber;

	cout << "\nEnter Pin Code? ";
	getline(cin >> ws, client.PinCode);

	cout << "\nEnter Name? ";
	getline(cin, client.Name);

	cout << "\nEnter Phone? ";
	getline(cin, client.Phone);

	cout << "\nEnter AccountBalance? ";
	cin >> client.AccountBalance;

	return client;
}
void saveDataToFile(vector<sClient>& clients, string fileName) {
	fstream myFile;
	//vector<string> res = 
	myFile.open(fileName, ios::out); // write mode
	if (myFile.is_open())
	{
		string line;
		for (auto& emp : clients) {
			if (emp.MarkDelete == false) {
				line = ConvertRecordToLine(emp);
				myFile << line << endl;
			}
		}
		myFile.close();
	}
}
bool findClientAccountNumber(vector<sClient>& clients,string AccountNumber){

	for (auto& emp : clients) {
		if (emp.AccountNumber == AccountNumber) {
			return true;
			break;
		}
	}
	return false;
}
void headerCrud(string header,string another="") {
	cout << "\n\n--------------------------------------\n";
	cout << "\t "<< header <<" Client "<< another <<"Screen\n";
	cout << "--------------------------------------\n";
}
string ReadAccountNumber() {
	string accountNumber;
	cout << "\nEnter Account Number? ";
	cin >> accountNumber;
	return accountNumber;
}
void AddNewClient() {
	// print header of function
	headerCrud("add New");
	cout << "Adding new Client\n";
	sClient client;
	vector<sClient> clients;
	string accountNumber;
	char add = 'y';

	while (tolower(add) == 'y') {
		// read all data from file and save it to vector

		accountNumber = ReadAccountNumber();
		clients = LoadFromFileToVector(FileName);
		while (findClientAccountNumber(clients, accountNumber)) {
			cout << "\nClient with[" << accountNumber << "] already exists, Enter another account number? ";
			cin >> accountNumber;
		}

		client = ReadNewClient(accountNumber);
		clients.push_back(client);

		// write new data to file
		saveDataToFile(clients, FileName);

		cout << "\nData added successfully, Do you want to add more clients(y/n)? ";
		cin >> add;
	}
	pressAnyKeyToReturn();
}
sClient getClientByAccountNumber(vector<sClient>& clients, string AccountNumber) {
	sClient employee;
	for (auto& emp : clients) {
		if (emp.AccountNumber == AccountNumber) {
			employee = emp;
			break;
		}
	}
	return employee;
}
void DeleteCurrentClient(vector<sClient>& clients, string AccountNumber) {
	for (auto& emp : clients) {
		if (emp.AccountNumber == AccountNumber)
			emp.MarkDelete = true;
	}
}
void DeleteClient(){
	headerCrud("Delete");
	string accountNumber;
	sClient client;
	vector<sClient> clients;
	char sure;
	clients = LoadFromFileToVector(FileName);
	accountNumber = ReadAccountNumber();
	if (!findClientAccountNumber(clients, accountNumber)) {
		cout << "\nClient with[" << accountNumber << "] Not Found!\n";
		pressAnyKeyToReturn();
		return;
	}

	client = getClientByAccountNumber(clients, accountNumber);
	ShowClientINLines(client);
	
	cout << "\n\n\nAre you sure you want to delete this account(y/n)? ";
	cin >> sure;

	if (tolower(sure) == 'y')
	{
		DeleteCurrentClient(clients, accountNumber);
		saveDataToFile(clients, FileName); // save new data to file

		cout << "\n\nClient Deleted Succeessfully\n";
	}
	pressAnyKeyToReturn();
}
void UpdateClient() {
	headerCrud("Update","Info ");
	string accountNumber;
	sClient client;
	vector<sClient> clients;
	char sure;
	clients = LoadFromFileToVector(FileName);
	accountNumber = ReadAccountNumber();
	if (!findClientAccountNumber(clients, accountNumber)) {
		cout << "\nClient with[" << accountNumber << "] Not Found!\n";
		pressAnyKeyToReturn();
		return;
	}

	client = getClientByAccountNumber(clients, accountNumber);
	ShowClientINLines(client);

	cout << "\n\n\nAre you sure you want to update this account(y/n)? ";
	cin >> sure;
	if (tolower(sure) == 'y')
	{
		for (auto& emp : clients) {
			if(emp.AccountNumber == accountNumber)
				emp = ReadNewClient(accountNumber);
		}
		saveDataToFile(clients, FileName); // save new data to file

		cout << "\n\nClient Updated Succeessfully\n";
	}
	pressAnyKeyToReturn();
}
void FindClient() {
	headerCrud("Find");
	string accountNumber;
	sClient client;
	vector<sClient> clients;

	clients = LoadFromFileToVector(FileName);
	accountNumber = ReadAccountNumber();
	if (!findClientAccountNumber(clients, accountNumber)) {
		cout << "\nClient with[" << accountNumber << "] Not Found!\n";
		pressAnyKeyToReturn();
		return;
	}

	client = getClientByAccountNumber(clients, accountNumber);
	ShowClientINLines(client);
	pressAnyKeyToReturn();
}
int Bank_choice() {
	Bank_menu();
	int choice = -1;
	while (choice == -1) {
		cout << "Choose what do you want to do [1:6]? ";
		cin >> choice;

		if (!(1 <= choice && choice <= 6)) {
			cout << "Sorry, You Entered Wrong Number Please choose from [1:6]? ";
			choice = -1;
		}
	}
	return choice;
}
void Bank_system() {

		
	while (true) {
		system("cls");
		int choice = Bank_choice();
		if (choice == 1)
		{
			system("cls");
			showClients();
		}
		else if (choice == 2) {
			system("cls");
			AddNewClient();
		}
		else if (choice == 3) {
			system("cls");
			DeleteClient();
		}
		else if (choice == 4) {
			system("cls");
			UpdateClient();
		}
		else if (choice == 5) {
			system("cls");
			FindClient();
		}
		else
			break;
	}
}
int main() {

	Bank_system();

	system("pause>0");
}

