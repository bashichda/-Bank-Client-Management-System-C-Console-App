//   Project 1 Bank Extension 2 (Requirements)

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

void ShowMainMenue();
void ShowTransactionsMenue();
void Login();
void ShowManageUserMenue();
void ShowAccessDeniedMessage();

struct sUser
{
	string UserName;
	string Password;
	int Permissions = 0;
	bool MarkForDelete = false;
};

sUser CurrentUser;

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

enum enMainMenuePermissions
{
	pAll = -1, pListClient = 1,
	pAddClient = 2, pDeleteClient = 4,
	pUpdateClient = 8, pFindClient = 16,
	pTransaction = 32, pManageUsers = 64
};

enum enMainMenueOptions
{
	eListClient = 1, eAddClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eShowTransactionsMenue = 6,
	eManageUsers = 7, eExit = 8
};

enum enManageUsersMenueOptions
{
	eListUser = 1, eAddUser = 2,
	eDeleteUser = 3, eUpdateUser = 4,
	eFindUser = 5, eMainMenue = 6
};

enum enTransactionsMenueOptions
{
	eDeposit = 1, eWithdraw = 2,
	eShowTotalBalances = 3, eShowMainMenue = 4
};

bool CheckPermission(enMainMenuePermissions Permission) {

	if (CurrentUser.Permissions == enMainMenuePermissions::pAll)
		return true;

	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;
	else
		return false;
}

void PrintClientCard(const sClient& Client) {

	cout << "\nThe following are the client details:";
	cout << "\n--------------------------------------";
	cout << "\nAccount Number  : " << Client.AccountNumber;
	cout << "\nPinCode         : " << Client.PinCode;
	cout << "\nName            : " << Client.Name;
	cout << "\nPhone           : " << Client.Phone;
	cout << "\nAccount Balance : " << Client.AccountBalance;
	cout << "\n--------------------------------------\n";

}

vector <string>SplitString(string S1, const string& delim) {

	vector <string> vString;

	int pos = 0;
	string sWord;

	while ((pos = S1.find(delim)) != std::string::npos) {

		sWord = S1.substr(0, pos);
		if (sWord != "") {
			vString.push_back(sWord);
		}

		S1.erase(0, pos + delim.length());
	}

	if (S1 != "") {
		vString.push_back(S1);
	}

	return vString;
}

string ConvertRecordToLine(const sClient& Client, const string Separator = "#//#") {

	string stDataLine = "";

	stDataLine += Client.AccountNumber + Separator;
	stDataLine += Client.PinCode + Separator;
	stDataLine += Client.Name + Separator;
	stDataLine += Client.Phone + Separator;
	stDataLine += to_string(Client.AccountBalance);

	return stDataLine;
}

sClient ConvertLineToRecord(const string& Line, const string Separator = "#//#") {

	sClient Client;
	vector <string> vClientData;
	vClientData = SplitString(Line, Separator);

	if (vClientData.size() == 5) {

		Client.AccountNumber = vClientData[0];
		Client.PinCode = vClientData[1];
		Client.Name = vClientData[2];
		Client.Phone = vClientData[3];
		Client.AccountBalance = stod(vClientData[4]);
	}

	return Client;
}

string ConvertUserRecordToLine(const sUser& User, string Separator = "#//#") {

	string stLine = "";

	stLine += User.UserName + Separator;
	stLine += User.Password + Separator;
	stLine += to_string(User.Permissions);

	return stLine;
}

sUser ConvertUserLineToRecord(const string& Line, string Separator = "#//#") {

	sUser User;
	vector <string> vUserDataLine = SplitString(Line, Separator);

	if (vUserDataLine.size() == 3) {
		User.UserName = vUserDataLine[0];
		User.Password = vUserDataLine[1];
		User.Permissions = stoi(vUserDataLine[2]);
	}

	return User;
}

bool ClientExistsByAccountNumber(const string& AccountNumber, const string& FileName) {

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		sClient Client;

		while (getline(MyFile, Line)) {

			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber) {
				MyFile.close();
				return true;
			}
		}

		MyFile.close();
	}

	return false;
}

bool UserExistsByUserName(const string& Username, const string& FileName) {

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		sUser User;

		while (getline(MyFile, Line)) {
			User = ConvertUserLineToRecord(Line);
			if (User.UserName == Username) {
				MyFile.close();
				return true;
			}
		}

		MyFile.close();
	}

	return false;
}

short ReadTransactionMenueOption() {

	short Option = 0;

	do
	{
		cout << "Choose what do you want to do? [1 to 4] ";
		cin >> Option;

	} while (Option < 1 || Option > 4);

	return Option;
}

sClient ReadNewClient() {

	sClient Client;

	cout << "\nEnter Account Number : ";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName)) {
		cout << "\nClient with Account Number [" << Client.AccountNumber <<
			"] Already exists, Enter another Account Number : ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode : ";
	getline(cin, Client.PinCode);

	cout << "Enter Name : ";
	getline(cin, Client.Name);

	cout << "Enter Phone : ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance : ";
	cin >> Client.AccountBalance;

	return Client;
}

sUser ReadNewUser() {

	sUser  User;
	char Answer = 'n';

	cout << "\nEnter Username : ";
	getline(cin >> ws, User.UserName);

	while (UserExistsByUserName(User.UserName, UsersFileName)) {
		cout << "\nUser with Username [" << User.UserName <<
			"] Already exists, Enter another Username : ";
		getline(cin >> ws, User.UserName);
	}

	cout << "Enter Password : ";
	getline(cin, User.Password);

	cout << "\nDo you want to give full Access? y/n ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y') {
		User.Permissions = enMainMenuePermissions::pAll;
	}
	else if (Answer == 'n' || Answer == 'N') {

		cout << "\nDo you want to give access to :";
		
		cout << "\nShow Client List? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pListClient;
		}


		cout << "\nAdd New Client? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pAddClient;
		}

		cout << "\nDelete Client? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pUpdateClient;
		}
		

		cout << "\nFind Client? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pFindClient;
		}

		cout << "\nTransactions? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pTransaction;
		}

		cout << "\nManage Users? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pManageUsers;
		}
	}

	return User;
}

string ReadClientAccountNumber() {

	string AccountNumber = "";

	cout << "\nPlease Enter Account Number : ";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}

short ReadMainMenueOption() {

	short Option = 0;

	do
	{
		cout << "Choose what do you want to do? [1 To 8]?  ";
		cin >> Option;

	} while (Option < 1 || Option > 8);

	return Option;
}

vector <sUser> LoadUsersDataFromFile(const string& FileName) {

	vector <sUser> vUsers;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sUser User;

		while (getline(MyFile, Line)) {
			
			User = ConvertUserLineToRecord(Line);
			vUsers.push_back(User);
		}

		MyFile.close();
	}

	return vUsers;
}

vector <sClient> LoadClientsDataFromFile(const string& FileName) {

	vector <sClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		sClient Client;

		while (getline(MyFile, Line)) {

			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}

void SaveDataClientsInFile(const string& FileName, const vector <sClient>& vClients) {

	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {

		string Line = "";

		for (const sClient& C : vClients) {

			if (C.MarkForDelete == false) {

				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;
			}
		}

		MyFile.close();
	}
}

bool FindClientByAccountNumber(const vector <sClient>& vClients, const string& AccountNumber, sClient& Client) {

	for (const sClient& C : vClients) {

		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	}

	return false;
}

void PrintClientRecord(const sClient& Client) {

	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;

}

void ShowClientListScreen() {

	if (!CheckPermission(enMainMenuePermissions::pListClient)) {

		ShowAccessDeniedMessage();
		return;
	}

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n----------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "AccountNumber";
	cout << "| " << left << setw(10) << "PinCode";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n----------------------------------------------------------------------------------------------\n";

	if (vClients.empty()) {

		cout << "\n\t\t\t\t\t No Client Available in System." << endl;
	}
	else {

		for (const sClient& C : vClients) {

			PrintClientRecord(C);
			cout << endl;
		}
	}
	cout << "----------------------------------------------------------------------------------------------\n\n";
}

void GoBackToMainMenue() {

	cout << "\nPress any key to back to Main Menue...";
	system("pause > 0");
	ShowMainMenue();
}

void AddDataClientToFile(const string& FileName, const string& Line) {

	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << Line << endl;

		MyFile.close();
	}

}

void AddNewClient() {

	sClient Client;
	Client = ReadNewClient();

	AddDataClientToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients() {

	cout << "Adding New Client:\n\n";

	char AddMore = 'N';
	do
	{
		AddNewClient();

		cout << "\nClient Added Successfully, do you want to add more clients ? y/n  ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

void ShowAddClientScreen() {

	if (!CheckPermission(enMainMenuePermissions::pAddClient)) {

		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-------------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-------------------------------------\n";

	AddNewClients();
}

bool MarkClientForDelete(vector <sClient>& vClients, const string& AccountNumber) {

	for (sClient& C : vClients) {

		if (C.AccountNumber == AccountNumber) {
			C.MarkForDelete = true;
			return true;
		}
	}

	return false;
}

bool DeleteClientByAccountNumber(vector <sClient>& vClients, const string& AccountNumber) {

	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(vClients, AccountNumber, Client)) {

		PrintClientCard(Client);

		cout << "\nAre you sure you want delete this client ? y/n ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {

			MarkClientForDelete(vClients, AccountNumber);
			SaveDataClientsInFile(ClientsFileName, vClients);

			cout << "\nClient Deleted Successfully." << endl;

			//Refrech Client;
			vClients = LoadClientsDataFromFile(ClientsFileName);
			return true;
		}
	}
	else {

		cout << "\nClient with Account Number [" << AccountNumber << "] is Not Found!." << endl;
		return false;
	}
}

void ShowDeleteClientScreen() {

	if (!CheckPermission(enMainMenuePermissions::pDeleteClient)) {

		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-------------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-------------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(vClients, AccountNumber);
}

sClient ChangeClientRecord(const string& AccountNumber) {

	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode : ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name : ";
	getline(cin, Client.Name);

	cout << "Enter Phone : ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance : ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientByAccontNumber(vector <sClient>& vClinets, const string& AccountNumber) {

	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(vClinets, AccountNumber, Client)) {

		PrintClientCard(Client);

		cout << "\nAre you sure you want update this client? y/n ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			for (sClient& C : vClinets) {

				if (C.AccountNumber == AccountNumber) {

					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveDataClientsInFile(ClientsFileName, vClinets);
			return true;
		}
	}
	else {
		cout << "\nClient with Account Number [" << AccountNumber << "] is Not Found!." << endl;
		return false;
	}
}

void ShowUpdateClientScreen() {

	if (!CheckPermission(enMainMenuePermissions::pUpdateClient)) {

		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-------------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-------------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByAccontNumber(vClients, AccountNumber);
}

void GoBackToTransactionMenue() {

	cout << "\n\nPress any key to back to Transactions Menue...";
	system("pause>0");
	ShowTransactionsMenue();
}

void ShowFindClinetScreen() {

	if (!CheckPermission(enMainMenuePermissions::pFindClient)) {

		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-------------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-------------------------------------\n";

	sClient Client;
	vector <sClient> vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccounNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(vClient, AccounNumber, Client)) {

		PrintClientCard(Client);
	}
	else {
		cout << "\nClient with Account Number [" << AccounNumber << "] is Not Found!." << endl;
	}

}

short ReadManageUsersMenueOption() {
	short Option = 0;

	do
	{
		cout << "Choos what do you want to do ? [1 to 6] ?  ";
		cin >> Option;
	} while (Option < 1 || Option > 6);

	return Option;
}

bool DepositBalanceToClientByAccountNumber(const string& AccountNumber, const double& Amount, vector <sClient>& vClients) {

	char Answer = 'N';


	cout << "\nAre you sure you want perform this trasaction? y/n ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		for (sClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += Amount;
				SaveDataClientsInFile(ClientsFileName, vClients);
				cout << "\nDone Successfully, New Balnce is : " << C.AccountBalance << endl;
				return true;
			}
		}
	}


	return false;
}

void ShowDepositScreen() {

	cout << "\n-------------------------------------\n";
	cout << "\tDeposit Screen.";
	cout << "\n-------------------------------------\n";

	sClient Client;
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(vClients, AccountNumber, Client)) {
		cout << "\nCliet with [" << AccountNumber << "] does not exist." << endl;
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithdrawScreen() {

	cout << "\n-------------------------------------\n";
	cout << "\tDeposit Screen.";
	cout << "\n-------------------------------------\n";

	sClient Client;
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(vClients, AccountNumber, Client)) {
		cout << "\nClient with [" << AccountNumber << "] does not exist." << endl;
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter withdraw amount? ";
	cin >> Amount;

	while (Amount > Client.AccountBalance) {
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "\nPlease enter another amount : ";
		cin >> Amount;
	}

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void PrintClientRecordBalances(const sClient& Client) {

	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.AccountBalance;
	cout << endl;
}

void ShowTotalBalancesScreen() {

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n----------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n----------------------------------------------------------------------------------------------\n";

	double TotalBalnces = 0;

	if (vClients.empty()) {

		cout << "\t\tNo Client Available in System." << endl;
	}
	else
	{
		for (const sClient& C : vClients) {

			PrintClientRecordBalances(C);
			TotalBalnces += C.AccountBalance;
		}
	}
	cout << "----------------------------------------------------------------------------------------------\n";
	cout << "\n\t\t\t\t\tTotal Balances = " << TotalBalnces;


}

void PerformTransactionsMenueOptions(enTransactionsMenueOptions TransactionMenueOption) {

	switch (TransactionMenueOption) {

	case enTransactionsMenueOptions::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionMenue();
		break;
	case enTransactionsMenueOptions::eWithdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionMenue();
		break;
	case enTransactionsMenueOptions::eShowTotalBalances:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionMenue();
		break;
	case enTransactionsMenueOptions::eShowMainMenue:
		ShowMainMenue();
		break;
	}
}

void ShowTransactionsMenue() {

	if (!CheckPermission(enMainMenuePermissions::pTransaction)) {

		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	cout << "\n================================================\n";
	cout << "\t\tTransactions Menue Screen";
	cout << "\n================================================";
	cout << "\n\t[1] Deposit.";
	cout << "\n\t[2] Withdraw.";
	cout << "\n\t[3] Total Balances.";
	cout << "\n\t[4] Main Menue.";
	cout << "\n================================================\n";
	PerformTransactionsMenueOptions((enTransactionsMenueOptions)ReadTransactionMenueOption());
}

void GoBackToManagerUserMenue() {
	cout << "\n\nPress any key to go back to Manage User Menue...";
	system("pause > 0");
	ShowManageUserMenue();
}

void PrintUserRecord(const sUser& User) {

	cout << "| " << left << setw(15) << User.UserName;
	cout << "| " << left << setw(10) << User.Password;
	cout << "| " << left << setw(15) << User.Permissions;

}

void ShowListUserScreen() {

	vector <sUser> vUsers = LoadUsersDataFromFile(UsersFileName);

	cout << "\n\t\t\t\t\tUsers List(" << vUsers.size() << ") User(s).";
	cout << "\n----------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(15) << "Permision";
	cout << "\n----------------------------------------------------------------------------------------------\n";

	if (vUsers.empty()) {
		cout << "\n\t\t\t No Users Data Available In System.";
	}
	else {

		for (const sUser& U : vUsers) {
			PrintUserRecord(U);
			cout << endl;
		}
	}
	cout << "----------------------------------------------------------------------------------------------\n";

}

void AddNewUserToFile(const string& FileName, const string& stDataLine) {

	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;

		MyFile.close();
	}
}

void AddNewUser() {

	sUser User = ReadNewUser();
	AddNewUserToFile(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewUsers() {

	cout << "Adding New User:\n\n";

	char AddMore = 'N';
	do
	{
		AddNewUser();

		cout << "\nUser Added Successfully, do you want to add more users ? y/n  ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

void ShowAddclientsScreen() {

	cout << "\n-------------------------------------\n";
	cout << "\tAdd New User Screen.";
	cout << "\n-------------------------------------\n";
	AddNewUsers();
}

string ReadUserName() {

	string UserName = "";

	cout << "Please enter username : ";
	getline(cin >> ws, UserName);

	return UserName;
}

bool MarkUserForDelete(vector <sUser>& vUsers, const string& UserName) {

	for (sUser& U : vUsers) {

		if (U.UserName == UserName) {
			U.MarkForDelete = true;
			return true;
		}
	}

	return false;
}

void SaveDataUsersInFile(const string& FileName,const vector <sUser>& vUsers) {
	
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {

		string Line = "";

		for (const sUser& U : vUsers) {

			if (U.MarkForDelete == false) {

				Line = ConvertUserRecordToLine(U);
				MyFile << Line << endl;
			}
		}

		MyFile.close();
	}
}

bool FindUserByUserName(const vector <sUser>& vUsers, const string& UserName, sUser& User) {

	for (const sUser& U : vUsers) {

		if (U.UserName == UserName) {
			User = U;
			return true;
		}
	}

	return false;
}

void PrintUserCard(const sUser& User) {

	cout << "\nthe following are the User Details : ";
	cout << "\n---------------------------------------";
	cout << "\nUser Name   : " << User.UserName;
	cout << "\nPassword    : " << User.Password;
	cout << "\nPermissions : " << User.Permissions;
	cout << "\n---------------------------------------\n";
}

bool DeleteUserByUserName(vector <sUser>& vUsers, const string& UserName) {

	sUser User;
	char Answer = 'n';

	if (FindUserByUserName(vUsers, UserName, User)) {

		PrintUserCard(User);

		cout << "\nAre you sure you want delete this User ? y/n ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {

			MarkUserForDelete(vUsers, UserName);
			SaveDataUsersInFile(UsersFileName, vUsers);

			cout << "\nUser Deleted Successfully." << endl;

			//Refrech Users;
			vUsers = LoadUsersDataFromFile(UsersFileName);
			return true;
		}
	}
	else {

		cout << "\nUser with UserName [" << UserName << "] is Not Found!." << endl;
		return false;
	}
}

void ShowDeleteUserScreen() {

	cout << "\n-------------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n-------------------------------------\n";

	vector <sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();
	DeleteUserByUserName(vUsers, UserName);

}

sUser ChangeUserRecord(const string& UserName) {
	
	sUser User;
	char Answer = 'n';

	User.UserName = UserName;

	cout << "Enter Passworr : ";
	getline(cin >> ws, User.Password);

	cout << "\nDo you want to give full Access? y/n ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y') {
		User.Permissions = enMainMenuePermissions::pAll;
	}
	else if (Answer == 'n' || Answer == 'N') {

		cout << "\nDo you want to give access to :";

		cout << "\nShow Client List? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pListClient;
		}


		cout << "\nAdd New Client? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pAddClient;
		}

		cout << "\nDelete Client? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pUpdateClient;
		}


		cout << "\nFind Client? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pFindClient;
		}

		cout << "\nTransactions? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pTransaction;
		}

		cout << "\nManage Users? y/n  ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			User.Permissions += enMainMenuePermissions::pManageUsers;
		}
	}

	return User;

}

bool UpdateUserByUserName(vector <sUser> & vUsers,const string& UserName) {
	
	sUser User;
	char Answer = 'n';

	if (FindUserByUserName(vUsers,UserName, User)) {

		PrintUserCard(User);

		cout << "\nAre you sure you want update this User? y/n ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			for (sUser& U : vUsers) {

				if (U.UserName == UserName) {

					U = ChangeUserRecord(UserName);
					break;
				}
			}

			SaveDataUsersInFile(UsersFileName, vUsers);
			return true;
		}
	}
	else {
		cout << "\nUser with UserName [" << UserName << "] is Not Found!." << endl;
		return false;
	}
}

void ShowUpdateUserScreen() {

	cout << "\n-------------------------------------\n";
	cout << "\tUpdate User Info Screen";
	cout << "\n-------------------------------------\n";

	vector <sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();

	UpdateUserByUserName(vUsers, UserName);

}

void ShowFindUserScreen() {

	cout << "\n-------------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n-------------------------------------\n";

	sUser User;
	vector <sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();

	if (FindUserByUserName(vUsers, UserName, User)) {

		PrintUserCard(User);
	}
	else {
		cout << "\nUser with UserName [" << UserName << "] is Not Found!." << endl;
	}

}

void PerformManageUsersMenueOptions(enManageUsersMenueOptions ManageUsersMenueOption) {

	switch (ManageUsersMenueOption) {

	case enManageUsersMenueOptions::eListUser:
		system("cls");
		ShowListUserScreen();
		GoBackToManagerUserMenue();
		break;
	case enManageUsersMenueOptions::eAddUser:
		system("cls");
		ShowAddclientsScreen();
		GoBackToManagerUserMenue();
		break;
	case enManageUsersMenueOptions::eDeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManagerUserMenue();
		break;
	case enManageUsersMenueOptions::eUpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManagerUserMenue();
		break;
	case enManageUsersMenueOptions::eFindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackToManagerUserMenue();
		break;
	case enManageUsersMenueOptions::eMainMenue:
		ShowMainMenue();
	}
}

void ShowAccessDeniedMessage() {

	cout << "-----------------------------------------";
	cout << "\nAccess Denied,";
	cout << "\nYou don't have Permission to Do this,";
	cout << "\nPlease Contact Your Admin.";
	cout << "\n-----------------------------------------";
}

void ShowManageUserMenue() {

	if (!CheckPermission(enMainMenuePermissions::pManageUsers)) {

		ShowAccessDeniedMessage();
		return;
	}

	system("cls");
	cout << "\n================================================\n";
	cout << "\t\tManage Users Menue Screen";
	cout << "\n================================================";
	cout << "\n\t[1] List Users.";
	cout << "\n\t[2] Add New User.";
	cout << "\n\t[3] Delete User.";
	cout << "\n\t[4] Update User.";
	cout << "\n\t[5] Find User.";
	cout << "\n\t[6] Main Menue.";
	cout << "\n================================================\n";
	PerformManageUsersMenueOptions((enManageUsersMenueOptions)ReadManageUsersMenueOption());
}

void PerformMainMenueOptions(enMainMenueOptions MainMenueOption) {

	switch (MainMenueOption) {

	case enMainMenueOptions::eListClient:
		system("cls");
		ShowClientListScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eAddClient:
		system("cls");
		ShowAddClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClinetScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eShowTransactionsMenue:
		system("cls");
		ShowTransactionsMenue();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eManageUsers:
		system("cls");
		ShowManageUserMenue();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eExit:
		system("cls");
		Login();
		break;
	}
}

void ShowMainMenue() {

	system("cls");
	cout << "\n================================================\n";
	cout << "\t\tMain Menue Screen";
	cout << "\n================================================";
	cout << "\n\t[1] Show Client List.";
	cout << "\n\t[2] Add New Client.";
	cout << "\n\t[3] Delete Client.";
	cout << "\n\t[4] Update Client Info.";
	cout << "\n\t[5] Find Client.";
	cout << "\n\t[6] Transactions.";
	cout << "\n\t[7] Manage Users.";
	cout << "\n\t[8] Logout.";
	cout << "\n================================================\n";
	PerformMainMenueOptions((enMainMenueOptions)ReadMainMenueOption());
}

bool FindUserByUserNameAndPassword(string UserName, string Password, sUser& CurrentUser) {

	vector <sUser> vUsers = LoadUsersDataFromFile(UsersFileName);

	for (const sUser& U : vUsers) {

		if (U.UserName == UserName && U.Password == Password) {
			CurrentUser = U;
			return true;
		}
	}

	return false;
}

bool LoadUserInfo(string UserName, string Password) {

	if (FindUserByUserNameAndPassword(UserName, Password, CurrentUser))
		return true;
	else
		return false;
}

void Login() {


	bool LoginFaild = false;
	string UserName, Password;
	do
	{
		system("cls");
		cout << "\n-------------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n-------------------------------------\n";
		
		if (LoginFaild) {
			cout << "Invalid UserName/Password!\n";
		}

		cout << "Enter UserName : ";
		getline(cin >> ws, UserName);
		cout << "Enter Password : ";
		cin >> Password;

		LoginFaild = !LoadUserInfo(UserName, Password);
		
	} while (LoginFaild);

	ShowMainMenue();
}

int main() {

	Login();

	return 0;
}
