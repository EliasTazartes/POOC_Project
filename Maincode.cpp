#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int main()
{
	string firstName, lastName;
	double frequency;
	int loanDuration;
	double loanPV;
	double APR;
	double periodicRate;
	double principal, interestPayment, instalment;
	double balance;


	cout << "Welcome to Sorbank, a bank for and by Sorbonne students !" << endl;
	cout << "This app is designed to generate with your help your loan payment schedule !" << endl;
	cout << "Please enter the fixed rate as Annual Percentage Rate (APR) in %" << endl;
	cin >> APR;
	while (APR < 0)
	{
		cout << "You seem to have entered a negative rate, although this is possible in terms of real interest rates, Sorbank only proposes positive nominal rates." << endl;
		cout << "Please enter the correct rate.  " << endl;
		cin >> APR;
	}
	APR = APR / 100;
	cout << "Please enter the duration of the loan (in years) ";
	cin >> loanDuration;
	while (loanDuration < 0)
	{
		cout << "You seem to have entered a negative duration, please enter the correct number of years.";
		cin >> loanDuration;
	}

	cout << "Please enter the frequency of payment for the loan" << endl;
	cout << "1 for annually, 2 for semi-annually, 4 for quarterly, and 12 for monthly  ";
	cin >> frequency;
	while (frequency != 1 && frequency != 2 && frequency != 4 && frequency != 12)
	{
		cout << "You have entered an incorrect frequency, please enter a correct one.  ";
		cin >> frequency;
	}
	const int periodNb = frequency * loanDuration;
	cout << "Okay ! Your loan will be rembursed over " << periodNb << " periods" << endl;

	periodicRate = APR / frequency;

	cout << "Enter the value of your loan (in USD) " << endl;
	cin >> loanPV;
	while (loanPV < 0)
	{
		cout << "You have entered a negative loan value, please enter a correct one.  " << endl;
		cin >> loanPV;
	}

	cout << "Right ! So you have borrowed " << loanPV << " $, which you will repay over " << periodNb << " periods." << endl;
	principal = loanPV / periodNb;


	// Defining the table

	vector<vector<double>> table;
	table.resize(6);
	for (int i = 0; i < 6; i++) {
		table[i].resize(periodNb);
	}

	// Generating the table;

	// Opening Balance
	table[0][0] = loanPV;
	for (int j = 1; j < periodNb; j++)
	{
		table[0][j] = table[0][j - 1] - principal;
	}

	// Principal

	for (int j = 0; j < periodNb; j++)
	{
		table[1][j] = principal;
	}

	// Periodic interest rate

	for (int j = 0; j < periodNb; j++)
	{
		table[2][j] = periodicRate;
	}

	// Interest

	for (int j = 0; j < periodNb; j++)
	{
		table[3][j] = table[0][j] * periodicRate;
	}

	// Instalment
	for (int j = 0; j < periodNb; j++)
	{
		table[4][j] = table[1][j] + table[3][j];
	}

	// Closing Balance

	for (int j = 0; j < periodNb; j++)
	{
		table[5][j] = table[0][j] - table[1][j];
	}


	for (int i = 0; i < 6; i++)
	{
		cout << " " << endl;
		for (int j = 0; j < periodNb; j++)
		{
			cout << "  " << table[i][j] << "  ";
		}
	}
	return 0;
}
