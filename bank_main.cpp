// Project1 - Bank Extension:

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowMainMenue();
void ShowTransactionsMenue();


struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

enum enMainMenueOptions
{
	eListClient = 1, eAddClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eShowTransactionsMenue = 6,
	eExit = 7
};

enum enTransactionsMenueOptions
{
	eDeposit = 1, eWithdraw = 2,
	eShowTotalBalances = 3, eShowMainMenue = 4
};

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

short ReadTransactionMenueOption() {

	short Option = 0;

	do
	{
		cout << "Choose what do you want to do? [1 to 4] ";
		cin >> Option;

	} while (Option < 1 || Option > 4 );

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
		cout << "Choose what do you want to do? [1 To 7]?  ";
		cin >> Option;

	} while (Option < 1 || Option > 7);

	return Option;
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

void ShowExitScreen() {
	cout << "\n-------------------------------------\n";
	cout << "\tProgram Ends :-) ";
	cout << "\n-------------------------------------\n";

	system("pause > 0");
}

bool DepositBalanceToClientByAccountNumber(const string& AccountNumber,const double& Amount,vector <sClient>& vClients) {

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
		ShowTransactionsMenue();
		break;
	case enMainMenueOptions::eExit:
		system("cls");
		ShowExitScreen();
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
	cout << "\n\t[7] Exit.";
	cout << "\n================================================\n";
	PerformMainMenueOptions((enMainMenueOptions)ReadMainMenueOption());
}

int main() {

	ShowMainMenue();

	return 0;
}
