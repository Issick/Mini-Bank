#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";

enum enUserOptions {
	ShowClientList = 1, AddingNewClient = 2, DeleteClient = 3,
	UpdateClientInfo = 4, FindClient = 5, Exit = 6
};

struct sClient
{
	string AcountNum = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AcountBalance = 0;
	bool MarkToDelete = false;
};

vector <string> SplitString(string S1)
{
	vector <string> vWords;
	string delim = "#//#";
	string sWord;
	short pos = 0;
	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
			vWords.push_back(sWord);
		S1.erase(0, pos + delim.length());
	}
	if (S1 != "")
		vWords.push_back(S1);
	return vWords;
}

sClient ConvertLineToRecord(string S)
{
	vector <string> vClient = SplitString(S);
	sClient Client;
	Client.AcountNum = vClient[0];
	Client.PinCode = vClient[1];
	Client.Name = vClient[2];
	Client.Phone = vClient[3];
	Client.AcountBalance = stod(vClient[4]);
	return Client;
}

vector <sClient> LoadsClientsDataFromFile(string FileName)
{
	vector <sClient> vFileContent;

	fstream MyFile;
	MyFile.open(FileName, ios::in);//Read Mode
	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			sClient Client = ConvertLineToRecord(Line);
			vFileContent.push_back(Client);
		}
		MyFile.close();
	}

	return vFileContent;
}

string PrintLine(short Lenght)
{
	string Line = "";
	for (short i = 0; i < Lenght; i++)
		Line += "-";

	return Line;
}

void PrintClientRecord(sClient Client)
{
	cout << setw(2) << "| " << setw(15) << left << Client.AcountNum;
	cout << setw(2) << "| " << setw(10) << left << Client.PinCode;
	cout << setw(2) << "| " << setw(30) << left << Client.Name;
	cout << setw(2) << "| " << setw(12) << left << Client.Phone;
	cout << setw(2) << "| " << setw(10) << left << Client.AcountBalance;
}

void PrintAllClientsData()
{
	system("cls");
	vector <sClient> vClients = LoadsClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\tClients List (" << vClients.size() << ") Client(s)" << endl;
	cout << PrintLine(90) << endl;
	cout << setw(2) << "| " << setw(15) << left << "Account Number";
	cout << setw(2) << "| " << setw(10) << left << "Pin Code";
	cout << setw(2) << "| " << setw(30) << left << "Client Name";
	cout << setw(2) << "| " << setw(12) << left << "Phone";
	cout << setw(2) << "| " << setw(10) << left << "Balance" << endl;
	cout << PrintLine(90) << endl;

	for (sClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}

	cout << PrintLine(90) << endl;
}

void PrintMainMinu()
{
	cout << " ==========================================================\n";
	cout << " \t\t\tMain Minu Screen\n";
	cout << " ==========================================================\n";
	cout << " \t[1] Show Client List.\n";
	cout << " \t[2] Add New Client.\n";
	cout << " \t[3] Delete Client.\n";
	cout << " \t[4] Update Client Info.\n";
	cout << " \t[5] Find Client.\n";
	cout << " \t[6] Exit.\n";
	cout << " ===========================================================\n";

}

enUserOptions ShowMainMinuOnScreen()
{
	system("cls");
	PrintMainMinu();
	short Choice = 0;
	cout << "Choose what do you want to do? [1 to 6]? ";
	cin >> Choice;

	return enUserOptions(Choice);
}

bool FindClientByAccountNumber(string AccountNumber, sClient& Client)
{
	vector <sClient> vClients = LoadsClientsDataFromFile(ClientsFileName);

	for (sClient C : vClients)
	{
		if (C.AcountNum == AccountNumber)
		{
			Client = C;
			return true;
		}
	}

	return false;
}

sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number? ";
	// Usage of std::ws will extract all the whitespace characters
	getline(cin >> ws, Client.AcountNum);
	while (FindClientByAccountNumber(Client.AcountNum, Client))
	{
		cout << "\nAccount Number (" << Client.AcountNum << ") is already exist! \n";
		cout << "Try another account number please :\n\n";
		cout << "Enter Account Number? ";
		getline(cin, Client.AcountNum);

	}
	cout << "Enter Pin Code? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone Number? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance? ";
	cin >> Client.AcountBalance;

	return Client;
}

string ConvertRecordToLine(sClient Client, string Separator = "#//#")
{
	string StgClientRecord = "";

	StgClientRecord += Client.AcountNum + Separator;
	StgClientRecord += Client.PinCode + Separator;
	StgClientRecord += Client.Name + Separator;
	StgClientRecord += Client.Phone + Separator;
	StgClientRecord += to_string(Client.AcountBalance);
	StgClientRecord += to_string(Client.MarkToDelete);

	return StgClientRecord;
}

void AddDataLineToFile(string FileName, string Line)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);//Append Mode
	if (MyFile.is_open() && Line.length() != 20)
	{
		MyFile << Line << endl;

		MyFile.close();
	}
}

void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddClients()
{
	char NewClient = 'y';
	do
	{
		system("cls");
		cout << "Adding new Client\n\n";
		AddNewClient();
		cout << "\nClient added succesfully, Do you want to add a new Client y/n?";
		cin >> NewClient;

	} while (tolower(NewClient) == 'y');
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "Please enter account number?";
	cin >> AccountNumber;

	return AccountNumber;
}

void PrintClientCard(sClient Client)
{
	cout << "\nClient Data in the structure are :\n";
	cout << "\n Account Number : " << Client.AcountNum;
	cout << "\n Pine Code : " << Client.PinCode;
	cout << "\n Name : " << Client.Name;
	cout << "\n Phone Number : " << Client.Phone;
	cout << "\n Account Balance : " << Client.AcountBalance;
}

string LoadsClientsDataFromFileToString(string FileName, string AccountNumber)
{
	string stFileContent;

	fstream MyFile;
	MyFile.open(FileName, ios::in);//Read Mode
	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			sClient Client = ConvertLineToRecord(Line);
			if (Client.AcountNum == AccountNumber)
				return Line;
		}
		MyFile.close();
	}
	return "";
}

void LoadDataFromFileToVector(string Path, vector <string>& vFileContent)
{
	fstream MyFile;
	MyFile.open(Path, ios::in);//Read Mode
	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			vFileContent.push_back(Line);
		}
		MyFile.close();
	}
}

void SaveVectorToFile(string Path, vector <string> vFileContent)
{
	fstream MyFile;
	MyFile.open(Path, ios::out);//Write Mode
	if (MyFile.is_open())
	{
		for (string& Line : vFileContent)
		{
			if (Line != "")
				MyFile << Line << endl;
		}
		MyFile.close();
	}
}

void DeleteRecordFromFile(string Path, string Record)
{
	vector <string> vFileContent;
	LoadDataFromFileToVector(Path, vFileContent);
	for (string& Line : vFileContent)
	{
		if (Line == Record)
			Line = "";
	}
	SaveVectorToFile(Path, vFileContent);
}

void DeleteRecordFromFileByAccountNumber(string FileName, string AccountNumber)
{
	char DeleteForSure = 'y';
	cout << "\n\nAre you sure you want to delete this Record ? (y/n)?";
	cin >> DeleteForSure;

	if (tolower(DeleteForSure) == 'y')
	{
		string LineToDelete = LoadsClientsDataFromFileToString(ClientsFileName, AccountNumber);
		DeleteRecordFromFile(ClientsFileName, LineToDelete);
		cout << "\n\nClient Deleted Successfully\n";
	}
}

void DeleteAClient()
{
	system("cls");
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();

	if (FindClientByAccountNumber(AccountNumber, Client))
	{
		PrintClientCard(Client);
		DeleteRecordFromFileByAccountNumber(ClientsFileName, AccountNumber);

	}
	else
	{
		cout << "\nClient with account number (" << AccountNumber << ") not found\n\n";
	}

}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client) {
	for (sClient C : vClients)
	{
		if (C.AcountNum == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

sClient UpdateClient(string AccountNumber)
{
	sClient Client;

	Client.AcountNum = AccountNumber;
	cout << "Enter Pin Code? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone Number? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance? ";
	cin >> Client.AcountBalance;

	return Client;
}


bool UpdateClient(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients) {
		if (C.AcountNum == AccountNumber) {
			C = UpdateClient(AccountNumber);
			return true;
		}
	}
	return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open()) {
		for (sClient C : vClients) {
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

vector <sClient> LoadCleintsDataFromFile(string FileName) {
	vector <sClient> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open()) {
		string Line;
		sClient Client;
		while (getline(MyFile, Line)) {
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}


bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			UpdateClient(AccountNumber, vClients);

			SaveCleintsDataToFile(ClientsFileName, vClients);
			//Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}


void UpdateAClientInfo()
{
	vector <sClient> vClients = LoadsClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
	system("pause>0");

}

void FindClientByAccountNumber()
{
	system("cls");
	string AccountNum = ReadClientAccountNumber();
	sClient Client;
	if (FindClientByAccountNumber(AccountNum, Client))
		PrintClientCard(Client);
	else
		cout << "\nClient is not exist!\n\n";

}

void CheckUserOption(enUserOptions Choice)
{
	bool ExitState = false;
	switch (Choice)
	{
	case ShowClientList:
		PrintAllClientsData();
		break;
	case enUserOptions::AddingNewClient:
		AddClients();
		break;
	case enUserOptions::DeleteClient:
		DeleteAClient();
		break;
	case enUserOptions::UpdateClientInfo:
		UpdateAClientInfo();
		break;
	case enUserOptions::FindClient:
		FindClientByAccountNumber();
		break;
	case enUserOptions::Exit:
		ExitState = true;
		break;
	default:
		break;
	}
	if (!ExitState)
	{
		cout << "\nPress any key to return to Main Minu :";
		system("pause>0");
	}
}


int main()
{
	//vector <sClient> vClients = LoadsClientsDataFromFile(ClientsFileName);
	enUserOptions Choice;

	do
	{
		Choice = ShowMainMinuOnScreen();
		CheckUserOption(Choice);
	} while (Choice != enUserOptions::Exit);

	return 0;
}


