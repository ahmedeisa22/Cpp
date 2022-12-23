
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include<fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
const string FileName = "Clients.txt";

void ATM_menu();
void  Login();
void QuickWithDrawMenuOption();
void ShowNormalWithDraw();


enum enMainMenueOptions{
	eQuickWithDraw = 1 , eNormalWithDarw = 2,
	eDeposite = 3 , eCheckBalance = 4, eLogout = 5
};

struct sClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkDelete = false;
};
// this is login user 
sClient CurrentLogin;

vector<string>Split(string str, string delimeter = "#//#") {
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
sClient ConverLineToRecord(string line, string delimeter = "#//#") {
	sClient clinet;
	vector<string> res = Split(line, delimeter);
	clinet.AccountNumber = res[0];
	clinet.PinCode = res[1];
	clinet.Name = res[2];
	clinet.Phone = res[3];
	clinet.AccountBalance = stod(res[4]);

	return clinet;
}
string ConvertRecordToLine(sClient client, string delimeter = "#//#") {
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
bool ClientExistsByAccountNumberAndPinCode(string AccountNumber,string pinCode, sClient& client) {
	vector<sClient> vclients = LoadFromFileToVector(FileName);
	for (auto& c : vclients) {
		if (c.PinCode == pinCode && c.AccountNumber == AccountNumber) {
			client = c;
			return true;
		}
	}
	
	return false;
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>&vClients)
{ 
char Answer = 'n';  
cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
cin >> Answer; 
if (Answer == 'y' || Answer == 'Y')
{ 
	for (sClient& C : vClients)
	{ if (C.AccountNumber == AccountNumber)
	{ 
		C.AccountBalance += Amount;
	saveDataToFile( vClients, FileName);
	cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance; 
	return true; 
	} 
} 
	return false; 
} 
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
	cout << "Account Number : " << Client.AccountNumber << "\n";
	cout << "Code Pin       : " << Client.PinCode << "\n";
	cout << "Name           : " << Client.Name << "\n";
	cout << "Phone Number   : " << Client.Phone << "\n";
	cout << "AccountBalance : " << Client.AccountBalance << "\n";
	cout << "----------------------------------------------------------------\n";
}
string ReadAccountNumber() {
	string accountNumber;
	cout << "\nEnter Account Number? ";
	cin >> accountNumber;
	return accountNumber;
}
short ReadMainMenueOption() {
	cout << "Choose what do you want to do? [1 to 5]? ";
	short Choice = 0;
	cin >> Choice; 
	return Choice;
}
short ReadWithdrawMainMenueOption() {
	cout << "Choose what do you want to do? [1 to 9]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
void GoBackToMainMenue() {
	cout << "\nPress any key to go back main menu...\n";
	system("pause>nul");
	ATM_menu();
}
void ShowCheckBalance() {
	cout << "=============================================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "=============================================================\n";
	cout << "Your Balance is: " << CurrentLogin.AccountBalance << endl;
}
short getQuickWithDrawAmount(short QuickWithDrawOption)
{ 
	switch (QuickWithDrawOption) 
{ 
	case 1: return  20;
case 2: return 50;
case 3: return 100;
case 4: return 200;
case 5: return 400;
case 6: return 600; 
case 7: return 800; 
case 8: return 1000;
default: 
	return 0;
	} 
}
short ReadQuickWithdrawOption()
{ 
	short Choice = 0;
	while (Choice < 1 || Choice>9)
	{ 
		cout << "\nChoose what to do from [1] to [9] ? "; 
		cin >> Choice; 
	} 
	return Choice;
}
void PerfromQuickWithdrawMenueOption(short withdrawOptions) {
	
	if (withdrawOptions == 9)
		return;

	short WithDrawBalance = getQuickWithDrawAmount(withdrawOptions);

	if (WithDrawBalance > CurrentLogin.AccountBalance) {
		cout << "\nThe amount exceeds yuor balance, make another choice\n";
		system("pause");
		QuickWithDrawMenuOption();
		return;
	}
	vector<sClient>clients = LoadFromFileToVector(FileName);
	DepositBalanceToClientByAccountNumber(CurrentLogin.AccountNumber, -WithDrawBalance, clients);
	CurrentLogin.AccountBalance -= WithDrawBalance;
}
void QuickWithDrawMenuOption() {
	system("cls");
	cout << "***********************************************\n";
	cout << " \t\tATM Main Menu Screen\n";
	cout << "***********************************************\n";
	cout << "\t [1] 20\t\t[2] 50.\n";
	cout << "\t [3] 100\t[4] 200.\n";
	cout << "\t [5] 400\t[6] 600.\n";
	cout << "\t [7] 800\t[8] 1000.\n";
	cout << "\t [9] Exit\n";
	cout << "***********************************************\n";
	cout << "Your Balance is: " << CurrentLogin.AccountBalance << endl;
	PerfromQuickWithdrawMenueOption(ReadQuickWithdrawOption());
}
void ShowQuickWithDraw() {
	cout << "=============================================================\n";
	cout << "\t\tQuick Withdraw Screen\n";
	cout << "=============================================================\n";
	QuickWithDrawMenuOption();
}
int ReadWithDrawAmont() {
	int Amount;  
	cout << "\nEnter an amount multiple of 5's ? ";  
	cin >> Amount;
while (Amount % 5 != 0)
{ cout << "\nEnter an amount multiple of 5's ? "; 
cin >> Amount; 
}
return Amount; 
}
void PerfotmNormalWithDraw(){
	int withdrawBalance = ReadWithDrawAmont();
	if (withdrawBalance > CurrentLogin.AccountBalance) {
		cout << "\nThe amount exceeds yuor balance, make another choice\n";
		system("pause");
		ShowNormalWithDraw();
		return;
	}
	vector<sClient>clients = LoadFromFileToVector(FileName);
	DepositBalanceToClientByAccountNumber(CurrentLogin.AccountNumber, -withdrawBalance, clients);
	CurrentLogin.AccountBalance -= withdrawBalance;
}
void ShowNormalWithDraw() {
	cout << "=============================================================\n";
	cout << "\t\tNormal Withdraw Screen\n";
	cout << "=============================================================\n";
	PerfotmNormalWithDraw();
}
double ReadDepositAmount()
{ 
	double Amount;
	cout << "\nEnter a positive Deposit Amount? "; 
	cin >> Amount; 
	while (Amount <= 0) { 
		cout << "\nEnter a positive Deposit Amount? ";   
		cin >> Amount; 
	} 
	return Amount; 
}
void PerformDeposite(){
	double deposite = ReadDepositAmount();
	vector<sClient>clients = LoadFromFileToVector(FileName);
	DepositBalanceToClientByAccountNumber(CurrentLogin.AccountNumber, -deposite, clients);
	CurrentLogin.AccountBalance -= deposite;
}
void ShowDeposite() {
	cout << "=============================================================\n";
	cout << "\t\tDeposite Screen\n";
	cout << "=============================================================\n";
	PerformDeposite();
}
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption) {
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eQuickWithDraw: {
		system("cls");
		ShowQuickWithDraw();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eNormalWithDarw: {
		system("cls");
		ShowNormalWithDraw();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eDeposite: {
		system("cls");
		ShowDeposite();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eCheckBalance: {
		system("cls");
		ShowCheckBalance();
		GoBackToMainMenue();
		break;
	}
	
	case enMainMenueOptions::eLogout: {
		system("cls");
		Login();
		break;
	}
	}
}
string ReadPinCode() {
	string pinCode;
	cout << "\nEnter PinCode ? ";
	cin >> pinCode;
	return pinCode;
}
void ATM_menu() {

	system("cls");
	cout << "***********************************************\n";
	cout << " \t\tATM Main Menu Screen\n";
	cout << "***********************************************\n";
	cout << "\t [1] Quick Withdraw.\n";
	cout << "\t [2] Normal Withdraw.\n";
	cout << "\t [3] Deposite.\n";
	cout << "\t [4] Check Balance.\n";
	cout << "\t [5] LogOut.\n";
	cout << "***********************************************\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
bool LoadClientInfo(string AccountNumber, string PinCode) {
	if (ClientExistsByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentLogin))
		return true;
	return false;
}
void Login() {
	bool FalidToLogIn = false;
	string AccountNumber, PinCode;
	do {
		
		system("cls");
		cout << "\n-----------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n-----------------------------------\n";

		if (FalidToLogIn) {
			cout << "\nInvalid userName/password\n";
		}

		AccountNumber = ReadAccountNumber();
		PinCode = ReadPinCode();

		FalidToLogIn = !LoadClientInfo(AccountNumber, PinCode);


	} while (FalidToLogIn);
	ATM_menu();
}
int main() {
	Login();
	system("pause>0");
}

