// Assign01AccountActions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <string>

using namespace std;

string fileName = "AccountActions.txt";



char getActionCode();
void displayBalance();
void recordAction(char);
double getActionAmount(char);
void writeAction(char, double);
void listActions();
string getActionLabel(char);

int main()
{
	
	char actionCode;

	cout << fixed << setprecision(2);

	actionCode = getActionCode();

	while (actionCode != 'Q')
	{
		switch (actionCode)
		{
		case 'B':
			displayBalance();
			break;
		case 'C':
			recordAction('C');
			break;
		case 'D':
			recordAction('D');
			break;
		case 'W':
			recordAction('W');
			break;
		case 'L':
			listActions();
			break;
		}
		actionCode = getActionCode();
	}

	cout << endl;
	system("pause");
	return 0;
}

char getActionCode()
{
	char code;

	cout << endl
		<< " Enter B  show Balance ..." << endl
		<< "       C  record Check ..." << endl
		<< "       D  make Deposit ..." << endl
		<< "       W  Withdrawal   ..." << endl
		<< "       L  List actions ..." << endl
		<< "       Q  Quit program:  ";
	cin >> code;
	code = toupper(code);
	
	while (code != 'B' && code != 'C' && code != 'D' && code != 'W' && code != 'L' && code != 'Q')
	{
		cout << endl
			<< "Enter B  show Balance ..." << endl
			<< "      C  record Check ..." << endl
			<< "      D  make Deposit ..." << endl
			<< "      W  Withdrawal   ..." << endl
			<< "      L  List actions ..." << endl
			<< "      Q  Quit program:  ";
		cin >> code;
		code = toupper(code);
	}
	return code;
}

void displayBalance()
{
	double balance = 0.0;
	char transCode;
	double amt;
	ifstream accountFile;

	accountFile.open(fileName);

	if (!accountFile)
	{
		cout << endl << " No records to display. Make initial deposit." << endl << endl;
		return;
	}

	accountFile >> transCode;

	while (!accountFile.eof())
	{
		accountFile >> amt;

		if (transCode == 'C' || transCode == 'W')
		{
			balance -= amt;
		}
		else if (transCode = 'D')
		{
			balance += amt;
		}
		accountFile >> transCode;
	}

	accountFile.close();

	cout << endl << " BALANCE of account   $" << fixed << setw(10) << setprecision(2) << balance << endl;

	return;
}

void recordAction(char a)
{
	char trans = a;
	double transAmt = 0.0;
	
	transAmt = getActionAmount(trans);

	writeAction(trans, transAmt);

	return;
}

double getActionAmount(char trans)
{
	double amount;

	if (trans == 'C')
	{
		cout << endl << " Amount of" << getActionLabel(trans) << ":  $ ";
	}
	else if (trans == 'D')
	{
		cout << endl << " Amount of" << getActionLabel(trans) << ":  $ ";
	}

	else if (trans == 'W')
	{
		cout << endl << " Amount of" << getActionLabel(trans) << ":  $ ";
	}
	cin >> amount;
	return amount;
}

void writeAction(char a, double b)
{
	ofstream accountFile;

	accountFile.open(fileName, ios::app);

	accountFile << a << right << fixed << setw(10) << setprecision(2) << b << endl;

	accountFile.close();
	return;
}


void listActions()
{
	char transCode;
	char transSymbol;
	double transAmt;

	ifstream actionFile;

	actionFile.open(fileName);

	if (!actionFile)
	{
		cout << endl << " No records to display. Make initial deposit." << endl << endl;
		return;
	}
	actionFile >> transCode;

	while (!actionFile.eof())
	{
		actionFile >> transAmt;
		transSymbol = '-';

		if (transCode == 'D')
			transSymbol = '+';

		cout << endl;
		cout << getActionLabel(transCode) << "           " << transSymbol << fixed << right << setw(10) << setprecision(2) << transAmt << endl;

		actionFile >> transCode;
	}
	displayBalance();
	return;
}

string getActionLabel(char code)
{
	
	string label;

	if (code == 'C')
		label = " check     ";
	else if (code == 'D')
		label = " deposit   ";
	else if (code == 'W')
		label = " withdrawal";

	return label;
}