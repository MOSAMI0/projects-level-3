#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";

void ShowMainMenue();
void ShowTransactionsMenue();

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

vector<string> SplitString(string Name, string Delim)
{
	vector<string>Vstring;

	short pos = 0;
	string sWord; // define a string variable 

	// use find() function to get the position of the delimiters  
	while ((pos = Name.find(Delim)) != std::string::npos)
	{
		sWord = Name.substr(0, pos); // store the word   
		if (sWord != "")
		{
			Vstring.push_back(sWord);
		}

		Name.erase(0, pos + Delim.length()); /* erase() until
		 positon and move to next word. */
	}

	if (Name != "")
	{
		Vstring.push_back(Name);
	}

	return Vstring;
}

stClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	stClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]); //cast string to double

	return Client;
}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector<stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in); //overwritr

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return false;
}

stClient ReadNewClient()
{
	stClient Client;

	cout << "Enter Account Number: ";
	//Usage of std::ws will extract allthe whitespace character
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber
			<< "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);

	}

	cout << "\nEnter PinCode: ";
	getline(cin, Client.PinCode);
	cout << "\nEnter Name: ";
	getline(cin, Client.Name);
	cout << "\nEnter Phone: ";
	getline(cin, Client.Phone);
	cout << "\nEnter Account Balance: ";
	cin >> Client.AccountBalance;

	return Client;
}

vector<stClient> LoadCleintsDataFromFile(string FileName)
{
	vector<stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in); // read mode

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}

void PrintClientRecord(stClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}

void PrintClientRecordBalanceLine(stClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
	vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (stClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}

void ShowTotalBalances()
{
	vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalances = 0;
	if (vClients.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else

		for (stClient Client : vClients)
		{
			PrintClientRecordBalanceLine(Client);
			TotalBalances += Client.AccountBalance;

			cout << endl;
		}
	
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}

void PrintClientCard(stClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number  : " << Client.AccountNumber;
	cout << "\nPin Code       : " << Client.PinCode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;

}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}

	}

	return false;
}

stClient ChangeClientRecord(string AccountNumber)
{
	stClient Client;

	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;

		}

	}

	return false;
}

vector<stClient> SaveCleintsDataToFile(string FileName, vector<stClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out); //overwritr
	string DataLine;
	if (MyFile.is_open())
	{
		for (stClient& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}

	return vClients;
}

void AddDataLineToFile(string FileName, string sDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << sDataLine << endl;

		MyFile.close();
	}

}

void AddNewClient()
{
	stClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "Add Client: \n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			// Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";

			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}

}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
	stClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveCleintsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number ("
			<< AccountNumber << ") is Not Found!";
		return false;
	}
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<stClient> vClients)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		for (stClient& C : vClients )
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);

				cout << "\n\nDone Successfully. New balance is: " 
					<< C.AccountBalance;
				return  true;
			}
		}

		return false;
	}
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "Please enter Account Number? ";
	cin >> AccountNumber;
	return AccountNumber;
}

void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";

	vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientsScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	AddNewClients();
}

void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	stClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with Account Number["
			<< AccountNumber << "] is not found!";
	}
}

void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}

void ShowDepositScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen"; 
	cout << "\n----------------------------------- \n";

	stClient Client;
	vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);
	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tWithDraw Screen";
	cout << "\n----------------------------------- \n";

	stClient Client;
	vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);
	double Amount = 0;
	cout << "\nPlease enter withdraw amount? ";
	cin >> Amount;

	//Validate that the amount does not exceeds the balance
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : "
			<< Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1 , vClients);

}

void ShowTotalBalancesScreen()
{
	ShowTotalBalances();
}

enum enTransactionsMenueOptions
{
	eDeposit = 1, eWithdraw = 2,
	eShowTotalBalance = 3, eShowMainMenue = 4
};

enum enMainMenueOptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eShowTransactionsMenue = 6 , 
	eExit = 7
};

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

void GoBackToTransactionsMenue()
{
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransactionsMenue();
}

short ReadTransactionsMenueOption()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0; 
	cin >> Choice;
	return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOptions)
{
	switch (TransactionsMenueOptions)
	{
	case enTransactionsMenueOptions::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMenueOptions::eWithdraw:
		system("cls");
		ShowWithDrawScreen();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMenueOptions::eShowTotalBalance:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenue();
		break;
	case enTransactionsMenueOptions::eShowMainMenue:
	{
		ShowMainMenue();
	}

	}
}

void ShowTransactionsMenue()
{
	system("cls");
	cout << "===========================================\n"; 
	cout << "\t\tTransactions Menue Screen\n"; 
	cout << "===========================================\n"; 
	cout << "\t[1] Deposit.\n";  
	cout << "\t[2] Withdraw.\n"; 
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";   
	cout << "===========================================\n";

	PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 7]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClients:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
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
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::eShowTransactionsMenue:
		system("cls");
		ShowTransactionsMenue();
		break;
	case enMainMenueOptions::eExit:
		system("cls");
		ShowEndScreen();
		break;

	}
}

void ShowMainMenue()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "===========================================\n";

	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{
	ShowMainMenue();
	system("pause>0");
	return 0;
}