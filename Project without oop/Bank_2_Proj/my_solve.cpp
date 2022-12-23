
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
void Bank_menu();
void transaction_menu();
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
bool ClientExistsByAccountNumber(string AccountNumber, string file) {
	vector<sClient> vclients;
	fstream myFile;

	myFile.open(file, ios::in); // Read mode
	if (myFile.is_open()) {

		string line;
		sClient client;
		while (getline(myFile, line)) {
			client = ConverLineToRecord(line);
			if (client.AccountNumber == AccountNumber) {
				myFile.close();
				return true;
			}

		}
	}
	return false;
}
sClient ReadNewClient() {
	sClient client;

	cout << "Enter Account Number? ";
	getline(cin >> ws, client.AccountNumber);

	while (ClientExistsByAccountNumber(client.AccountNumber, FileName)) {
		cout << "\nClient with [" << client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, client.AccountNumber);
	}


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
	cout << "|" << setw(18) << left << Client.AccountNumber;
	cout << "|" << setw(12) << left << Client.PinCode;
	cout << "|" << setw(30) << left << Client.Name;
	cout << "|" << setw(20) << left << Client.Phone;
	cout << "|" << setw(15) << left << Client.AccountBalance << "\n";
	
}
void showClients() {
	vector<sClient> vClients = LoadFromFileToVector(FileName);;

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

	if (vClients.size() == 0) {
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else {

		// show acount data
		for (auto& acc : vClients) {
			ShowClient(acc);
		}
	}
	cout << "_____________________________________________________________________________________________________________________\n\n\n";
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
bool findClientAccountNumber(vector<sClient>& clients, string AccountNumber, sClient& client) {

	for (auto& emp : clients) {
		if (emp.AccountNumber == AccountNumber) {
			client = emp;
			return true;
			break;
		}
	}
	return false;
}
sClient ReadClient(string accountNumber) {
	sClient client;

	 client.AccountNumber = accountNumber;

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
bool DeleteCurrentClient(vector<sClient>& clients, string AccountNumber) {
	for (auto& emp : clients) {
		if (emp.AccountNumber == AccountNumber)
		{
			emp.MarkDelete = true;
			return true;
		}
	}

	return false;
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
void addDataLineToFile(string file, string addstr) {
	fstream myFile;

	myFile.open(file, ios::out | ios::app);
	if (myFile.is_open()) {

		myFile << addstr << endl;

		myFile.close();
	}
}
void AddClient() {
	sClient client;
	client = ReadNewClient();
	addDataLineToFile(FileName, ConvertRecordToLine(client));
}
void AddNewClients() {
	char AddMore = 'Y';
	do {
		cout << "Adding New Client:\n\n";
		AddClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& clients){
	sClient client;
	char answer;
	if(findClientAccountNumber(clients, AccountNumber, client)){
		ShowClientINLines(client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> answer;

		

		if (tolower(answer) == 'y') {
			DeleteCurrentClient(clients, AccountNumber);
			saveDataToFile(clients,FileName);

			clients = LoadFromFileToVector(FileName);
			cout << "\n\nClient Deleted Successfully.\n";
			return true;
		}
	}
	return false;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& clients) {
	sClient client;
	char answer = 'n';

	if (findClientAccountNumber(clients, AccountNumber, client)) {
		ShowClientINLines(client);

		cout << "\n\nAre you sure you want to Update this client? y/n ? ";
		cin >> answer;

		if (tolower(answer) == 'y') {

			for (sClient & C : clients) {
				if (C.AccountNumber == AccountNumber)
				{
					C = ReadClient(AccountNumber);
					break; 
				} 
			}
			saveDataToFile(clients,FileName);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else { 
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false; 
	}


}
string ReadAccountNumber() {
	string accountNumber;
	cout << "\nEnter Account Number? ";
	cin >> accountNumber;
	return accountNumber;
}
void ShowDeleteClientScreen() {
	cout << "\n-----------------------------------\n"; 
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> clients = LoadFromFileToVector(FileName);
	string AccountNumber = ReadAccountNumber();

	if(!DeleteClientByAccountNumber(AccountNumber, clients))
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}
void ShowUpdateClientScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tUpdat Client Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> clients = LoadFromFileToVector(FileName);
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, clients);
}
void ShowAddNewClientsScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Client Screen";
	cout << "\n-----------------------------------\n";
		
	AddNewClients();
}
void ShowFindClientScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> clients = LoadFromFileToVector(FileName);
	sClient Client;
	string AccountNumber = ReadAccountNumber();
	if (findClientAccountNumber(clients, AccountNumber, Client)) {
		ShowClientINLines(Client);
	}
	else {
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
	}
}
void ShowEndScreen() { 
	cout << "\n-----------------------------------\n"; 
	cout << "\tProgram Ends :-)";   
	cout << "\n-----------------------------------\n";
}
enum enMainMenueOptions {
	eListClients = 1 , eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5,  eTransaction = 6,
	eExit = 7
};
enum enTranscationMenueOptions {
	eDepoiste = 1, eWithDraw = 2,
	eTotalBalance = 3, eMainMenu = 4,
};
void GoBackToMainMenue() {
	cout << "\nPress any key to go back main menu...\n";
	system("pause>nul");
	Bank_menu();
}
void GoBackToTransMenue() {
	cout << "\nPress any key to go back Transaction menu...\n";
	system("pause>nul");
	transaction_menu();
}
short ReadMainMenueOption() {
	cout << "Choose what do you want to do? [1 to 7]? ";
	short Choice = 0;
	cin >> Choice; return Choice; 
}
short ReadTransactionMenueOption() {
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice; return Choice;
}
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption) {


	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:{
		system("cls");
		showClients();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eAddNewClient:{
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eDeleteClient: {
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eUpdateClient: {
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;
	}								
	case enMainMenueOptions::eFindClient: {
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eTransaction: {
		system("cls");
		transaction_menu();
		break;
	}
	case enMainMenueOptions::eExit: {
		system("cls");
		ShowEndScreen();
		break;
	}
	}
}
bool Can_WithDraw(sClient& client,double amount) {
	if (client.AccountBalance < amount)
		return false;
	client.AccountBalance -= amount;
	return true;
}
void showDepoisteScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\t\tDeposite Screen";
	cout << "\n-----------------------------------\n";
	vector<sClient> vClients = LoadFromFileToVector(FileName);
	sClient client;
	string AccountNumber = ReadAccountNumber();

	while (!findClientAccountNumber(vClients, AccountNumber, client)) {
		cout << "\nClient with [" << AccountNumber << "] doesn't exsits\n";
		AccountNumber = ReadAccountNumber();
	}

	ShowClientINLines(client);
	cout << "\nPlease Enter Depoiste Amount? ";
	double amount;
	cin >> amount;
	char ans;
	cout << "\nAre you sure you want to perform thi transaction (y/n)? ";
	cin >> ans;
	if (ans == 'y' || ans == 'Y') {
		for (auto& C : vClients) {
			if(C.AccountNumber == client.AccountNumber)
				C.AccountBalance += amount, client = C;
		}

		cout << "\nNew Balance is: " << client.AccountBalance << "\n";
		saveDataToFile(vClients, FileName);
		//GoBackToTransMenue();
	}
}
void showWithDrawScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\t\WithDraw Screen";
	cout << "\n-----------------------------------\n";
	vector<sClient> vClients = LoadFromFileToVector(FileName);
	sClient client;
	string AccountNumber = ReadAccountNumber();

	while (!findClientAccountNumber(vClients, AccountNumber, client)) {
		cout << "\nClient with [" << AccountNumber << "] doesn't exsits\n";
		AccountNumber = ReadAccountNumber();
	}

	ShowClientINLines(client);
	cout << "\nPlease Enter withDraw Amount? ";
	double amount;
	cin >> amount;
	
	
	while (!Can_WithDraw(client, amount)) {
		cout << "\nAmount Exceeds the balance, you can withDraw up to " << client.AccountBalance << "\n";
		cout << "Please enter another amount? ";
		cin >> amount;
	}
	char ans;
	cout << "\nAre you sure you want to perform thi transaction (y/n)? ";
	cin >> ans;
	if (ans == 'y' || ans == 'Y') {
		for (auto& C : vClients) {
			if (C.AccountNumber == AccountNumber)
				C.AccountBalance = client.AccountBalance;
		}
		cout << "\nDone Successfully, New Balance is: " << client.AccountBalance << "\n";
		saveDataToFile(vClients, FileName);
	}
	
		
		//GoBackToTransMenue();
	
}
void showClientTransaction(sClient Client) {
	cout << "| " << setw(20) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(20) << left << Client.AccountBalance << "\n";
} 
void ShowTotalBalances(){
	vector<sClient> vClients = LoadFromFileToVector(FileName);

	cout << "\n\t\t\t\t Balance List (" << vClients.size() << ") Client(s).\n";
	cout << "____________________________________________________________________________________________________________________\n\n";
	cout << "| " << setw(20) << left << "AccountNumber";
	cout << "| " << setw(40) << left << "Clietn Name";
	cout << "| " << setw(20) << left << "Balance";
	cout << "\n____________________________________________________________________________________________________________________\n\n";
	double totalBalance = 0;
	for (auto& emp : vClients) {
		showClientTransaction(emp);
		totalBalance += emp.AccountBalance;
	}

	cout << "\n____________________________________________________________________________________________________________________\n\n";

	cout << "\t\t\t\t\t Total Balance = " << totalBalance << endl;
}
void PerfromTranscationMenueOption(enTranscationMenueOptions transcationMenu) {


	switch (transcationMenu)
	{
	case enTranscationMenueOptions::eDepoiste:{
		system("cls");
		showDepoisteScreen();
		GoBackToTransMenue();
		break;
	}
	case enTranscationMenueOptions::eWithDraw: {
		system("cls");
		showWithDrawScreen();
		GoBackToTransMenue();
		break;
	}
	case enTranscationMenueOptions::eTotalBalance: {
		system("cls");
		ShowTotalBalances();
		GoBackToTransMenue();
		break;
	}
	case enTranscationMenueOptions::eMainMenu: {
		system("cls");
		Bank_menu();
		break;
	}
	}
}
void transaction_menu() {
	system("cls");
	cout << "==================================================\n";
	cout << "\t\tTranscation Menu Screen";
	cout << "\n==================================================\n";
	cout << "\t [1] Deposite.\n";
	cout << "\t [2] WithDraw.\n";
	cout << "\t [3] Total Balance.\n";
	cout << "\t [4] Main Menu.\n";
	cout << "\n==================================================\n";
	PerfromTranscationMenueOption((enTranscationMenueOptions)ReadTransactionMenueOption());
}
void Bank_menu() {

	system("cls");
	cout << "***********************************************\n";
	cout << " \t\tMain Menu Screen\n";
	cout << "***********************************************\n";
	cout << "\t [1] Show Client List.\n";
	cout << "\t [2] Add New Client.\n";
	cout << "\t [3] Delete Client.\n";
	cout << "\t [4] Update Client.\n";
	cout << "\t [5] Find Client.\n";
	cout << "\t [6] Transaction.\n";
	cout << "\t [7] Exit.\n";
	cout << "***********************************************\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
int main() {
	Bank_menu();
	
	system("pause>0");
}

