
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
const string UserFileName = "Users.txt";

void Bank_menu();
void transaction_menu();
void Login();
void MangeUser_menu();
struct sClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkDelete = false;
};
struct sUser
{
	string userName = "";
	string password = "";
	int permission = -1;
	bool MarkDelete = false;
};
// this is login user 
sUser CurrentLoginUser;
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
sUser ConverLineToUserRecord(string line, string delimeter = "#//#") {
	sUser user;
	vector<string> res = Split(line, delimeter);
	user.userName = res[0];
	user.password = res[1];
	user.permission = stoi(res[2]);

	return user;
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
string ConvertUserRecordToLine(sUser user, string delimeter = "#//#") {
	string res = "";
	res += user.userName + delimeter;
	res += user.password + delimeter;
	res += to_string(user.permission) ;

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
bool UserExistsByUserName(string UserName, string file,sUser &user) {
	vector<sUser> vusers;
	fstream myFile;

	myFile.open(file, ios::in); // Read mode
	if (myFile.is_open()) {

		string line;
		while (getline(myFile, line)) {
			user = ConverLineToUserRecord(line);
			if (user.userName == UserName) {
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
int ReadSetPermission() {
	string adding = "00000000";
	char choice;
	cout << " List users (y/n): ";
	cin >> choice;
	if (tolower(choice) == 'y')
		adding[7] = '1';

	cout << "add new users (y/n): ";
	cin >> choice;
	if (tolower(choice) == 'y')
		adding[6] = '1';

	cout << "Update users (y/n): ";
	cin >> choice;
	if (tolower(choice) == 'y')
		adding[5] = '1';

	cout << "Delete users (y/n): ";
	cin >> choice;
	if (tolower(choice) == 'y')
		adding[4] = '1';

	cout << "Find users (y/n): ";
	cin >> choice;
	if (tolower(choice) == 'y')
		adding[3] = '1';

	cout << "transaction users (y/n): ";
	cin >> choice;
	if (tolower(choice) == 'y')
		adding[2] = '1';

	cout << "Manage users (y/n): ";
	cin >> choice;
	if (tolower(choice) == 'y')
		adding[1] = '1';

	int sum = 0;
	for (int i = 0; i < adding.size(); i++) {
		if (adding[adding.size() - i - 1] == '1')
			sum += pow(2, i);
	}
	return sum;

}
sUser ReadNewUser() {
	sUser user;
	sUser tempUser;
	cout << "Enter UserName? ";
	getline(cin >> ws, user.userName);

	while (UserExistsByUserName(user.userName, UserFileName, tempUser)) {
		cout << "\User with [" << user.userName << "] already exists, Enter another userName ? ";
		getline(cin >> ws, user.userName);
	}


	cout << "\nEnter Password? ";
	getline(cin, user.password);

	char fullAccess;
	cout << "\nDo You want to give full access? (y/n): ";
	cin >> fullAccess;

	if (tolower(fullAccess) == 'n') {
		cout << "\nDo you want to give access to : \n";
		user.permission = ReadSetPermission();
	}

	return user;
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
vector<sUser> LoadFromFileToVectorUsers(string file) {
	vector <sUser> vUsers;
	fstream myFile;

	myFile.open(file, ios::in); // read mode
	if (myFile.is_open()) {
		string line;
		sUser user;
		while (getline(myFile, line)) {
			user = ConverLineToUserRecord(line);
			vUsers.push_back(user);
		}
		myFile.close();
	}
	return vUsers;
}
void ShowClient(sClient Client) {
	cout << "|" << setw(18) << left << Client.AccountNumber;
	cout << "|" << setw(12) << left << Client.PinCode;
	cout << "|" << setw(30) << left << Client.Name;
	cout << "|" << setw(20) << left << Client.Phone;
	cout << "|" << setw(15) << left << Client.AccountBalance << "\n";

}
void ShowUser(sUser user) {
	cout << "| " << setw(20) << left << user.userName;
	cout << "| " << setw(15) << left << user.password;
	cout << "| " << setw(10) << left <<user.permission << "\n";
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
void ShowUserINLines(sUser user) {
	cout << "\nThe Following are the User details:\n";
	cout << "-------------------------------------------------------------\n";
	cout << "UserName  : " << user.userName << "\n";
	cout << "Password  : " << user.password << "\n";
	cout << "Permission: " << user.permission<< "\n";

	cout << "----------------------------------------------------------------\n";
}
bool findUserByUserName(vector<sUser>& users, string UserName, sUser& user) {

	for (auto& us : users) {
		if (us.userName == UserName) {
			user = us;
			return true;
			break;
		}
	}
	return false;
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
sUser ReadUser(string userName) {
	sUser user;

	user.userName = userName;

	cout << "\nEnter Password? ";
	getline(cin >> ws, user.password);


	char fullAccess;
	cout << "\nDo You want to give full access? (y/n): ";
	cin >> fullAccess;

	if (tolower(fullAccess) == 'n') {
		cout << "\nDo you want to give access to : \n";
		user.permission = ReadSetPermission();
	}

	return user;
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
bool DeleteCurrentUser(vector<sUser>& users, string UserName) {
	for (auto& user : users) {
		if (user.userName == UserName)
		{
			user.MarkDelete = true;
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
void saveDataToFileUser(vector<sUser>& users, string fileName) {
	fstream myFile;
	//vector<string> res = 
	myFile.open(fileName, ios::out); // write mode
	if (myFile.is_open())
	{
		string line;
		for (auto& user : users) {
			if (user.MarkDelete == false) {
				line = ConvertUserRecordToLine(user);
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
void AddUser() {
	sUser user;
	user = ReadNewUser();
	addDataLineToFile(UserFileName, ConvertUserRecordToLine(user));
}
void AddNewUsers() {
	char AddMore = 'Y';
	do {
		cout << "Adding New User:\n\n";
		AddUser();
		cout << "\nUser Added Successfully, do you want to add more users? Y/N? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
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
bool DeleteUserByUserName(string UserName, vector<sUser>& users) {
	sUser user;
	char answer;

	
	if (findUserByUserName(users, UserName, user)) {
		ShowUserINLines(user);

		cout << "\n\nAre you sure you want delete this user? y/n ? ";
		cin >> answer;



		if (tolower(answer) == 'y') {
			DeleteCurrentUser(users, UserName);
			saveDataToFileUser(users, UserFileName);

			users = LoadFromFileToVectorUsers(UserFileName);
			cout << "\n\User Deleted Successfully.\n";
			return true;
		}
	}
	return false;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& clients) {
	sClient client;
	char answer;
	if (findClientAccountNumber(clients, AccountNumber, client)) {
		ShowClientINLines(client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> answer;



		if (tolower(answer) == 'y') {
			DeleteCurrentClient(clients, AccountNumber);
			saveDataToFile(clients, FileName);

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

			for (sClient& C : clients) {
				if (C.AccountNumber == AccountNumber)
				{
					C = ReadClient(AccountNumber);
					break;
				}
			}
			saveDataToFile(clients, FileName);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}


}
bool UpdateUserByUserName(string UserName, vector<sUser>& users) {
	sUser user;
	char answer = 'n';

	if (findUserByUserName(users, UserName, user)) {
		ShowUserINLines(user);

		cout << "\n\nAre you sure you want to Update this user? y/n ? ";
		cin >> answer;

		if (tolower(answer) == 'y') {

			for (sUser& U : users) {
				if (U.userName == UserName)
				{
					U = ReadUser(UserName);
					break;
				}
			}
			saveDataToFileUser(users, UserFileName);
			cout << "\n\nUser Updated Successfully.";
			return true;
		}
	}
	else {
		cout << "\nUser with UserName (" << UserName << ") is Not Found!";
		return false;
	}


}
string ReadAccountNumber() {
	string accountNumber;
	cout << "\nEnter Account Number? ";
	cin >> accountNumber;
	return accountNumber;
}
string ReadUserName() {
	string userName;
	cout << "\nEnter UserName? ";
	cin >> userName;
	return userName;
}
void ShowDeleteUserScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n-----------------------------------\n";

	vector<sUser> users = LoadFromFileToVectorUsers(UserFileName);
	string UserName = ReadUserName();
	if (UserName == "Admin") {
		cout << "\nYou cann't delete this user\n";
		return;
	}

	if (!DeleteUserByUserName(UserName, users))
		cout << "\nUser with UserName[" << UserName << "] is not found!";

}
void ShowDeleteClientScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> clients = LoadFromFileToVector(FileName);
	string AccountNumber = ReadAccountNumber();

	if (!DeleteClientByAccountNumber(AccountNumber, clients))
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}
void ShowUpdateUserScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tUpdat User Screen";
	cout << "\n-----------------------------------\n";

	vector<sUser> users = LoadFromFileToVectorUsers(UserFileName);
	string UserName = ReadUserName();
	if (UserName == "Admin") {
		cout << "\nYou cann't Update this user\n";
		return;
	}
	UpdateUserByUserName(UserName, users);
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
void ShowFindUserScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n-----------------------------------\n";

	vector<sUser> users = LoadFromFileToVectorUsers(UserFileName);
	sUser User;
	string UserName = ReadUserName();
	if (findUserByUserName(users, UserName, User)) {
		ShowUserINLines(User);
	}
	else {
		cout << "\nUser with UserName[" << UserName << "] is not found!";
	}
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
void LoginScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tLogin Screen";
	cout << "\n-----------------------------------\n";
}
void ShowEndScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}
enum enMainMenueOptions {
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransaction = 6,
	eManageUsers=7,	eLogOut = 8
};
enum enTranscationMenueOptions {
	eDepoiste = 1, eWithDraw = 2,
	eTotalBalance = 3, eMainMenu = 4,
};
enum enManageUserOptions {
	eListUser = 1, eAddNewUser = 2,
	eDeleteUser = 3, eUpdateUser = 4,
	eFindUser = 5 ,eMainMenuManger = 6
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
void GoBackToMangerUserMenue() {
	cout << "\nPress any key to go back MangerUser menu...\n";
	system("pause>nul");
	MangeUser_menu();
}
short ReadMainMenueOption() {
	cout << "Choose what do you want to do? [1 to 7]? ";
	short Choice = 0;
	cin >> Choice; return Choice;
}
short ReadMangeUsersMenueOption() {
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
short ReadTransactionMenueOption() {
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double amount, vector<sClient> vClients) {
	char ans;
	cout << "\nAre you sure you want to perform thi transaction (y/n)? ";
	cin >> ans;
	if (ans == 'y' || ans == 'Y') {
		for (auto& C : vClients) {
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += amount;
				saveDataToFile(vClients, FileName);
				cout << "\nDone Successfully,New Balance is: " << C.AccountBalance << "\n";
				return true;
			}
		}

		return false;
	}
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

	DepositBalanceToClientByAccountNumber(AccountNumber, amount, vClients);

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


	while (amount > client.AccountBalance) {
		cout << "\nAmount Exceeds the balance, you can withDraw up to " << client.AccountBalance << "\n";
		cout << "Please enter another amount? ";
		cin >> amount;
	}
	DepositBalanceToClientByAccountNumber(AccountNumber, -amount, vClients);
	//GoBackToTransMenue();

}
void showClientTransaction(sClient Client) {
	cout << "| " << setw(20) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(20) << left << Client.AccountBalance << "\n";
}
void ShowTotalBalances() {
	vector<sClient> vClients = LoadFromFileToVector(FileName);

	cout << "\n\t\t\t\t Balance List (" << vClients.size() << ") Client(s).\n";
	cout << "____________________________________________________________________________________________________________________\n\n";
	cout << "| " << setw(20) << left << "AccountNumber";
	cout << "| " << setw(40) << left << "Clietn Name";
	cout << "| " << setw(20) << left << "Balance";
	cout << "\n____________________________________________________________________________________________________________________\n\n";
	double totalBalance = 0;
	if (vClients.size() < 0)
		cout << "\t\t\t No Clients availble in the system\n";
	else
		for (auto& emp : vClients) {
			showClientTransaction(emp);
			totalBalance += emp.AccountBalance;
		}

	cout << "\n____________________________________________________________________________________________________________________\n\n";

	cout << "\t\t\t\t\t Total Balance = " << totalBalance << endl;

}
void ShowTotalBalancesScreen() {
	ShowTotalBalances();
}
void ShowUserList() {
	vector<sUser> users = LoadFromFileToVectorUsers(UserFileName);
	
	cout << "\n\t\tUser List " << users.size() << ") User(s)";
	cout << "\n_____________________________________________________________________________________________________________\n";

	cout << "| "<<setw(20) << left<<"UserName";
	cout << "| "<<setw(15) << left << "Password";
	cout << "| " << setw(10) << left << "Permission";
	cout << "\n_____________________________________________________________________________________________________________\n";

	for (auto& user : users)
		ShowUser(user);
}
string convertToBinartyString(int num){
	int i = 0, r;
	string res = "";
	while (num != 0)
	{
		r = num % 2;
		res =to_string(r) + res;
		num /= 2;
	}
	return res;
}
string getBinaryString() {
	string res = convertToBinartyString(CurrentLoginUser.permission);
	string binaryPermission = "00000000";
	int pos = 8 - res.size();
	  binaryPermission.replace(pos, res.size(), res);
	//reverse(binaryPermission.begin(), binaryPermission.end());
		 return binaryPermission;
}
void accesDenied() {
	cout << "\n-------------------------------------------------------------\n";
	cout << "Acess isDenied,\n you don't have permission to do this,\n";
	cout << "Please contact your Admin\n";
	cout << "\n-------------------------------------------------------------\n";
}
void PerfromMangeUserMenueOption(enManageUserOptions useroptions) {
	string binaryPermission = getBinaryString();
	switch (useroptions)
	{
	case enManageUserOptions::eListUser: {
		system("cls");
		if (binaryPermission[7] == '1' || CurrentLoginUser.permission == -1)
			ShowUserList();
		else
			accesDenied();

		GoBackToMangerUserMenue();
		break;
	}
	case enManageUserOptions::eAddNewUser: {
		system("cls");
		if (binaryPermission[6] == '1' || CurrentLoginUser.permission == -1)
			AddNewUsers();
		else
			accesDenied();
		
		GoBackToMangerUserMenue();
		break;
	}
	case enManageUserOptions::eDeleteUser: {
		system("cls");
		if (binaryPermission[5] == '1' || CurrentLoginUser.permission == -1)
			ShowDeleteUserScreen();
		else
			accesDenied();
		GoBackToMangerUserMenue();
		break;
	}
		case enManageUserOptions::eUpdateUser: {
			system("cls");
			if (binaryPermission[4] == '1' || CurrentLoginUser.permission == -1)
				ShowUpdateUserScreen();
			else
				accesDenied();
			GoBackToMangerUserMenue();
		break;
	}
		case enManageUserOptions::eFindUser: {
			system("cls");
			if (binaryPermission[3] == '1' || CurrentLoginUser.permission == -1)
				ShowFindUserScreen();
			else
				accesDenied();
			GoBackToMangerUserMenue();
			break;
		}
		case enManageUserOptions::eMainMenuManger: {
			Bank_menu();
			break;
		}
	}
}
void PerfromTranscationMenueOption(enTranscationMenueOptions transcationMenu) {
	switch (transcationMenu)
	{
	case enTranscationMenueOptions::eDepoiste: {
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
		ShowTotalBalancesScreen();
		GoBackToTransMenue();
		break;
	}
	case enTranscationMenueOptions::eMainMenu: {
		Bank_menu();
		break;
	}
	}
}
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption) {
	string binaryPermission = getBinaryString();
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients: {
		system("cls");
		if (binaryPermission[7] == '1' || CurrentLoginUser.permission == -1)
				showClients();
		else
			accesDenied();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eAddNewClient: {
		system("cls");
		if (binaryPermission[6] == '1' || CurrentLoginUser.permission == -1)
			ShowAddNewClientsScreen();
		else
			accesDenied();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eDeleteClient: {
		system("cls");
		if (binaryPermission[5] == '1' || CurrentLoginUser.permission == -1)
		ShowDeleteClientScreen();
		else
			accesDenied();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eUpdateClient: {
		system("cls");
		if (binaryPermission[4] == '1' || CurrentLoginUser.permission == -1)
		ShowUpdateClientScreen();
		else
			accesDenied();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eFindClient: {
		system("cls");
		if (binaryPermission[3] == '1' || CurrentLoginUser.permission == -1)
		ShowFindClientScreen();
		else
			accesDenied();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eTransaction: {
		system("cls");
		if (binaryPermission[2] == '1' || CurrentLoginUser.permission == -1)
			transaction_menu();
		else
			accesDenied();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eManageUsers: {
		system("cls");
		if (binaryPermission[1] == '1' || CurrentLoginUser.permission == -1)
		MangeUser_menu();
		else
			accesDenied();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eLogOut: {
		system("cls");
		Login();
		break;
	}
	}
}
void MangeUser_menu() {
	system("cls");
	cout << "==================================================\n";
	cout << "\t\tMangeUser Menu Screen";
	cout << "\n==================================================\n";
	cout << "\t [1] List Users.\n";
	cout << "\t [2] Add New Users.\n";
	cout << "\t [3] Delete Users.\n";
	cout << "\t [4] Update Users.\n";
	cout << "\t [5] Find Users.\n";
	cout << "\t [6] Main Menu.\n";
	cout << "\n==================================================\n";
	PerfromMangeUserMenueOption((enManageUserOptions)ReadMangeUsersMenueOption());
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
	cout << "\t [7] Manage Users.\n";
	cout << "\t [8] LogOut.\n";
	cout << "***********************************************\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
void Login() {
	LoginScreen();
	while (true)
	{
		string userName,password;
		cout << "\nEnter UserName: ";
		getline(cin >> ws, userName);

		cout << "Enter passowrod: ";
		cin >> password;


		if (!UserExistsByUserName(userName, UserFileName, CurrentLoginUser)) {
			cout << "\nInvalid userName/password\n";
			continue;
		}
		
		if (CurrentLoginUser.password != password) {
			cout << "\nInvalid userName/password\n";
			continue;
		}
		// reach here username and password are correct

		break;
	}
	// show me the system
	Bank_menu();
}
int main() {
	Login();
	
	system("pause>0");
}

