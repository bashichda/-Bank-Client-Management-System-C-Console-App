// Project Bank 1:

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowMainMenue();

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
	eFindClient = 5, eExit = 6
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

string ConvertRecordToLine(const sClient& Client,const string Separator = "#//#") {

	string stDataLine = "";

	stDataLine += Client.AccountNumber + Separator;
	stDataLine += Client.PinCode+ Separator;
	stDataLine += Client.Name+ Separator;
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

short ReadChoice() {

	short Choice = 0;

	do
	{
		cout << "Choose what do you want to do? [1 To 6]?  ";
		cin >> Choice;

	} while (Choice < 1 || Choice > 6);

	return Choice;
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

void SaveDataClientsInFile(const string& FileName,const vector <sClient>& vClients) {

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

void AddDataClientToFile(const string& FileName,const string& Line) {

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
	DeleteClientByAccountNumber(vClients,AccountNumber);
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
	cout << "\n\t[6] Exit.";
	cout << "\n================================================\n";
	PerformMainMenueOptions((enMainMenueOptions)ReadChoice());
}

int main() {

	ShowMainMenue();

	return 0;
}
