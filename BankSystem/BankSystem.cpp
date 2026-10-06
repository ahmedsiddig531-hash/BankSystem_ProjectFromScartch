#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;


void ReadClientInfo(clsBankClient& Client)
{
	cout << "\nEnter First Name: ";
	Client.FirstName = clsInputValidate::ReadString();

	cout << "Enter Last Name: ";
	Client.LastName = clsInputValidate::ReadString();

	cout << "Enter Email: ";
	Client.Email = clsInputValidate::ReadString();

	cout << "Enter Phone: ";
	Client.Phone = clsInputValidate::ReadString();

	cout << "Enter Pin Code: ";
	Client.PinCode = clsInputValidate::ReadString();

	cout << "Enter Account Balance: ";
	Client.AccountBalance = clsInputValidate::ReadDblNumber();
}


void UpdateClient()
{
	string AccountNumber = "";

	cout << "\nEnter Client Account Number: ";
	AccountNumber = clsInputValidate::ReadString();

	while (!clsBankClient::IsClientExist(AccountNumber))
	{
		cout << "\nClient Not Found, Enter another Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient Client = clsBankClient::Find(AccountNumber);

	Client.Print();

	cout << "\nUpdate Client Info:\n";
	cout << "---------------------\n";

	ReadClientInfo(Client);

	Client.Save();

	cout << "\nClient Updated Successfully.\n";

	cout << "\nClient Updated Info:\n";
	Client.Print();
}


void AddNewClient()
{
	string AccountNumber = "";

	cout << "\nEnter Client Account Number: ";
	AccountNumber = clsInputValidate::ReadString();

	while (clsBankClient::IsClientExist(AccountNumber))
	{
		cout << "\nAccount Number already exists, Enter another Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient NewClient =
		clsBankClient::GetAddNewClient(AccountNumber);

	ReadClientInfo(NewClient);

	clsBankClient::enSaveResults SaveResult = NewClient.Save();

	switch (SaveResult)
	{
	case clsBankClient::enSaveResults::svSucceeded:

		cout << "\nClient Added Successfully.\n";
		NewClient.Print();

		break;


	case clsBankClient::enSaveResults::svFaildEmptyObject:

		cout << "\nFailed to add client. Empty object.\n";

		break;


	case clsBankClient::enSaveResults::svFaildAccountNumberExists:

		cout << "\nError account was not saved because account number is used!\n";

		break;
	}
}


void DeleteClient()
{
	string AccountNumber = "";

	cout << "\nEnter Client Account Number: ";
	AccountNumber = clsInputValidate::ReadString();

	while (!clsBankClient::IsClientExist(AccountNumber))
	{
		cout << "\nClient Not Found, Enter another Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient Client = clsBankClient::Find(AccountNumber);

	Client.Print();

	cout << "\nAre you sure you want to delete this client? (Y/N): ";

	char Confirm = 'N';
	cin >> Confirm;

	if (Confirm == 'Y' || Confirm == 'y')
	{
		if (Client.Delete())
		{
			cout << "\nClient Deleted Successfully.\n";
			Client.Print();
		}
		else
		{
			cout << "\nFailed to delete client.\n";
		}
	}
	else
	{
		cout << "\nClient Deletion Cancelled.\n";
	}
}


void PrintClientRecordLine(clsBankClient Client)
{
	cout << "| " << setw(15) << left
		<< Client.AccountNumber();

	cout << "| " << setw(20) << left
		<< Client.FullName();

	cout << "| " << setw(12) << left
		<< Client.Phone;

	cout << "| " << setw(20) << left
		<< Client.Email;

	cout << "| " << setw(10) << left
		<< Client.PinCode;

	cout << "| " << setw(12) << left
		<< Client.AccountBalance;
}


void ShowAllClients()
{
	vector <clsBankClient> vClients =
		clsBankClient::GetClientsList();

	cout << "\n\t\t\t\t\tClient List ("
		<< vClients.size()
		<< ") Client(s).";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;


	cout << "| " << left << setw(15)
		<< "Account Number";

	cout << "| " << left << setw(20)
		<< "Client Name";

	cout << "| " << left << setw(12)
		<< "Phone";

	cout << "| " << left << setw(20)
		<< "Email";

	cout << "| " << left << setw(10)
		<< "Pin Code";

	cout << "| " << left << setw(12)
		<< "Balance";


	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;


	if (vClients.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else
	{
		for (clsBankClient Client : vClients)
		{
			PrintClientRecordLine(Client);
			cout << endl;
		}
	}


	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}


void PrintTotalBalanceRecordLine(clsBankClient Client)
{
	cout << "| " << setw(15) << left
		<< Client.AccountNumber();

	cout << "| " << setw(40) << left
		<< Client.FullName();

	cout << "| " << setw(12) << left
		<< Client.AccountBalance;
}


void ShowTotalBalances()
{
	vector <clsBankClient> vClients =
		clsBankClient::GetClientsList();

	double TotalBalances = clsBankClient::TotalBalances();

	cout << "\n\t\t\t\t\tClient List ("
		<< vClients.size()
		<< ") Client(s).";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;


	cout << "| " << left << setw(15)
		<< "Account Number";

	cout << "| " << left << setw(40)
		<< "Client Name";

	cout << "| " << left << setw(12)
		<< "Balance";


	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;


	if (vClients.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else
	{
		for (clsBankClient Client : vClients)
		{
			PrintTotalBalanceRecordLine(Client);
			cout << endl;
		}
	}


	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;


	cout << "\n\nTotal Balances = "
		<< TotalBalances << " (" << clsUtil::NumberToText((int)TotalBalances) << ")\n" << endl;
}


int main()
{
	ShowTotalBalances();

	system("pause>0");

	return 0;
}