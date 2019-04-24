#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

double negative_Value (double number) {
   while (number < 0)
	{
		cout << "You seem to have entered a negative number" << endl;
		cout << "Please enter the correct number.  " << endl;
		cin >> number;
	}
    return number;
}

void fixedPrincipal (double loanPV, double principal, double rate, int period) {
    
    vector<vector<double> > table;
	table.resize(6);
	for (int i = 0; i < 6; i++) {
		table[i].resize(period);
	}

	table[0][0] = loanPV;
	for (int j = 1; j < period; j++)
	{table[0][j] = table[0][j - 1] - principal;}

    for (int j = 0; j < period; j++)
	{table[1][j] = principal;}

	for (int j = 0; j < period; j++)
	{table[2][j] = rate;}

	for (int j = 0; j < period; j++)
	{table[3][j] = table[0][j] * rate;}

	for (int j = 0; j < period; j++)
	{table[4][j] = table[1][j] + table[3][j];}

	for (int j = 0; j < period; j++)
	{table[5][j] = table[0][j] - table[1][j];}

	for (int i = 0; i < 6; i++)
	{cout << " " << endl;
		for (int j = 0; j < period; j++)
		{cout << "  " << table[i][j] << "  ";}
	}
}

void fixedInstalment (double loanPV, double rate, int period, double instalment) {
    vector<vector<double> > table;
	table.resize(6);
	for (int i = 0; i < 6; i++) {
		table[i].resize(period);
	}

	table[0][0] = loanPV;

    if (instalment == 0) {
        instalment = loanPV * rate * (1 + (1/(pow(1+rate,period)-1))) ;
    }
    
	for (int j = 1; j < period; j++)
	{table[0][j] = table[0][j - 1] - instalment + rate*table[0][j-1];}

	for (int j = 0; j < period; j++)
	{table[2][j] = rate;}

    for (int j = 0; j < period; j++)
	{table[1][j] = instalment - table[0][j]*rate ;}

	for (int j = 0; j < period; j++)
	{table[3][j] = table[0][j] * rate;}

	for (int j = 0; j < period; j++)
	{table[4][j] = instalment ;}

	for (int j = 0; j < period; j++)
	{table[5][j] = table[0][j] - instalment + table[3][j];}

	for (int i = 0; i < 6; i++)
	{cout << " " << endl;
		for (int j = 0; j < period; j++)
		{cout << "  " << table[i][j] << "  ";}
	}
}

double presentValue (double instalment, double rate, double period) {
    double netPV ;
    netPV = instalment/(rate*(1+(1/(pow(1+rate, period)-1))));
    return netPV;
}

double rate_input () {
    double APR;
    cout << "Please enter the fixed rate as Annual Percentage Rate (APR) in %" << endl;
	cin >> APR;
	APR = negative_Value (APR);
	APR = APR / 100;
    return APR; 
}

int duration_input () {
    int loanDuration;
    cout << "Please enter the duration of the loan (in years) ";
	cin >> loanDuration;
	loanDuration = negative_Value(loanDuration);
    return loanDuration ; 
}

int frequency_input (int loanDuration) {
    int frequency ; 
    cout << "Please enter the frequency of payment for the loan" << endl;
	cout << "1 for annually, 2 for semi-annually, 4 for quarterly, and 12 for monthly  ";
	cin >> frequency;
	frequency = negative_Value(frequency); 
	const int periodNb = frequency * loanDuration;
    return periodNb ;
}

double periodic_rate (double rate, int frequency) {
    double periodicRate; 
    periodicRate = rate / frequency;
    return periodicRate ; 
}

double loan_value_input () {
    double loanPV; 
    cout << "Enter the value of your loan (in USD) " << endl;
	cin >> loanPV;
	loanPV = negative_Value(loanPV);
    return loanPV;
}

double instal_value_input () {
    double loanPV; 
    cout << "Enter the value of your instalment (in USD) " << endl;
	cin >> loanPV;
	loanPV = negative_Value(loanPV);
    return loanPV;
}

double period_number (double net_PV, double instalment, double rate) {
    double periodNb; 
    double frequency ; 
    double tampn ; 
    double period_rate ;
    cout << "Please enter the frequency of payment for the loan" << endl;
	cout << "1 for annually, 2 for semi-annually, 4 for quarterly, and 12 for monthly  ";
	cin >> frequency;
    frequency = negative_Value(frequency); 
    period_rate = rate/frequency ;
    tampn = log(pow(instalment/(period_rate*net_PV), -1)+1)/log(1+period_rate); 
    periodNb = floor(tampn+0.5) ;
    return periodNb ; 
}

int main()
{
	string firstName, lastName;
	int frequency;
	int loanDuration;
	double loanPV;
	double APR;
	double periodicRate;
	double principal, interestPayment, instalment;
    int periodNb; 
	double balance;
    int optionLoan; 
    int optionRate ;
    int option_Fixed_Instal ; 


	cout << "Welcome to Sorbank, a bank for and by Sorbonne students !" << endl;
	cout << "This app is designed to generate with your help your loan payment schedule !" << endl;

    cout << "Please select the type of loan you want to have" << endl;
    cout << "For fixed principal type : 1" << endl;
    cout << "For fixed instalments type : 2" << endl;
	cin >> optionLoan;

    if (optionLoan ==1 ){
        cout << "You selected a fixed principal loan." << endl;
        cout << "If you want fixed interest rate, type 1" << endl;
        cout << "If you want floating rates, type 2" << endl;
        cin >> optionRate;

        if (optionRate == 1) {
            loanPV = loan_value_input();
            periodNb = frequency_input(duration_input());
            periodicRate = periodic_rate(rate_input(), periodNb);
            principal = loanPV / periodNb;
            fixedPrincipal(loanPV, principal, periodicRate, periodNb);
        }
        if (optionRate==2) {
        }   
    }

    if (optionLoan == 2) {
         cout << "You selected a fixed instalments loan." << endl;
         cout << "What informations do you have ? Type the according number (1,2,3 or 4) "<< endl;
         cout << "1. Presevent Value, fixed rate, number of years" << endl; 
         cout << "2. Instalments, fixed rate, number of years" << endl; 
         cout << "3. Presevent Value, Instalments, fixed rate" << endl; 
         cout << "4. Presevent Value, Instalments, number of years" << endl; 
         cin >> option_Fixed_Instal ;

         if (option_Fixed_Instal == 1) {
            loanPV = loan_value_input();
            periodNb = frequency_input(duration_input());
            periodicRate = periodic_rate(rate_input(), periodNb);
            instalment = 0; 
            fixedInstalment(loanPV, periodicRate, periodNb, instalment);
         }

         if (option_Fixed_Instal == 2) {
            instalment = instal_value_input();
            periodNb = frequency_input(duration_input());
            periodicRate = periodic_rate(rate_input(), periodNb);
            loanPV = presentValue(instalment, periodicRate, periodNb);
            fixedInstalment(loanPV, periodicRate, periodNb, instalment);
         }

         if (option_Fixed_Instal == 3) {
             double rateTpn ;
             loanPV = loan_value_input();
             instalment = instal_value_input();
             rateTpn = rate_input();
             periodNb = period_number(loanPV, instalment, rateTpn);
             periodicRate = periodic_rate(rateTpn,periodNb);
             fixedInstalment(loanPV, periodicRate, periodNb, instalment);
         }

         if (option_Fixed_Instal == 4) {
             loanPV = loan_value_input();
             instalment = instal_value_input();
             periodNb = frequency_input(duration_input());
             periodicRate = 0 ;
         }
    }

	return 0;
}
