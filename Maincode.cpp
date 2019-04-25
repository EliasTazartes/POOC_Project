#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <limits>
#include <cstdlib>

using namespace std;

double negative_Value(double number) {
	while (number < 0)
	{
		cout << "You seem to have entered a negative number" << endl;
		cout << "Please enter the correct number.  " << endl;
		cin >> number;
	}
	return number;
}

int check_Frequency_Value(double number) {
	while (number !=1 && number !=2 && number !=4 && number !=12)
	{
		cout << "You seem to have entered an inappropriate value" << endl;
		cout << "Please enter the correct number.  " << endl;
		cin >> number;
	}
	return number;
}

double verifiy_Double_Value () {
	double value;
	cin.clear();
	while (1) {
			if (cin >> value) {
			break;
			} 
			else {
				cout << "Invalid Input! Please input a proper value." << endl;
				cin.clear();
				while (cin.get() != '\n') ; 
			}
		}
	value = negative_Value(value);	
	return value;
}

double verifiy_Int_Value () {
	int value;
	cin.clear();
	while (1) {
			if (cin >> value) {
			break;
			} 
			else {
				cout << "Invalid Input! Please input a proper value." << endl;
				cin.clear();
				while (cin.get() != '\n') ; 
			}
		}
	value = negative_Value(value);
	return value;
}

double presentValue(double instalment, double rate, double period) {
	double netPV;
	netPV = instalment / (rate * (1 + (1 / (pow(1 + rate, period) - 1))));
	return netPV;
}

double rate_input() {
	double APR;
	cout << "Please enter the fixed rate as Annual Percentage Rate (APR) in %" << endl;
	APR = verifiy_Double_Value()/100;
	return APR;
}

int duration_input() {
	int loanDuration;
	cout << "Please enter the duration of the loan (in years) ";
	loanDuration = verifiy_Int_Value();
	return loanDuration;
}

int frequency_input() {
	int frequency;
	cout << "Please enter the frequency of payment for the loan" << endl;
	cout << "1 for annually, 2 for semi-annually, 4 for quarterly, and 12 for monthly  ";
	frequency = verifiy_Int_Value();
	frequency = check_Frequency_Value(frequency);
	return frequency;
}

double periodic_rate(double rate, int frequency) {
	double periodicRate;
	periodicRate = rate / frequency;
	return periodicRate;
}

double loan_value_input() {
	double loanPV;
	cout << "Enter the value of your loan (in USD) " << endl;
	loanPV = verifiy_Double_Value();
	return loanPV;
}

double instal_value_input() {
	double value;
	cout << "Enter the value of your instalment (in USD) " << endl;
	value = verifiy_Double_Value();
	return value;
}

double period_number(double net_PV, double instalment, double rate, double frequency) {
	double periodNb;
	double tampn;
	double period_rate;
	period_rate = rate / frequency;
	tampn = log(pow(instalment / (period_rate * net_PV) - 1, -1) + 1) / log(1 + period_rate);
	periodNb = floor(tampn + 0.5);
	cout << periodNb << endl;
	return periodNb;
}

double dichotomy(double net_PV, double instalment, double periodNb) {
	double rate = 0.5;
	double parameter = 1;
	double test_value;
	double val_sup = 1, val_min = 0;


	while (abs(parameter) > 0.00001) {
		test_value = net_PV * rate * (1 + (1 / (pow(1 + rate, periodNb) - 1)));
		parameter = instalment - test_value;

		if (parameter > 0 && abs(parameter) > 0.00001) {
			val_min = rate;
			rate = (rate + val_sup) / 2;
		}
		if (parameter < 0 && abs(parameter) > 0.00001) {
			val_sup = rate;
			rate = (val_min + rate) / 2;
		}
	}
	return rate;
}

void fixedPrincipal(double loanPV, double principal, double rate, int period) {

	vector<vector<double> > table;
	table.resize(7);
	for (int i = 0; i < 7; i++) {
		table[i].resize(period);
	}

	table[1][0] = loanPV;

	for (int j = 1; j < period; j++) {
		table[1][j] = table[1][j - 1] - principal;
	}

	for (int j = 0; j < period; j++) {
		table[0][j] = j + 1;
		table[2][j] = principal;
		table[3][j] = rate * 100;
		table[4][j] = table[1][j] * rate;
		table[5][j] = table[2][j] + table[4][j];
		table[6][j] = table[1][j] - table[2][j];
	}
	std::ofstream myfile;
	myfile.open("amortization_table1.csv");
	myfile << "# ; Opening Balance ; Principal ; Interest Rate ; Interest ; Instalment ; Closing Balance\n";
	myfile << "i ; PV (i-1) ; P i ; R i ; Int i ; PMT i ; PV i \n";
	for (int j = 0; j < period; j++) {
		for (int i = 0; i < 7; i++) {
			myfile << table[i][j];
			myfile << ";";
		}
		myfile << "\n";
	}
	myfile.close();
	cout << endl << "Thank you for your time, the .csv file has been successfully created." << endl;
}

int amortization_table_fixed_instal(double loanPV, double rate, int period, double instalment) {
	vector<vector<double> > table;
	table.resize(8);
	for (int i = 0; i < 8; i++) {
		table[i].resize(period);
	}
	table[1][0] = loanPV;

	if (instalment == 0) {
		instalment = loanPV * rate * (1 + (1 / (pow(1 + rate, period) - 1)));
	}


	for (int j = 1; j < period; j++) {
		table[1][j] = table[1][j - 1] - instalment + rate * table[1][j - 1];
	}

	for (int j = 0; j < period; j++) {
		table[0][j] = j + 1;
		table[3][j] = rate * 100;
		table[2][j] = instalment - table[1][j] * rate;
		table[4][j] = table[1][j] * rate;
		table[5][j] = instalment;
		table[6][j] = table[1][j] - instalment + table[4][j];
		table[7][j] = table[1][j - 1] - instalment + rate * table[1][j - 1];
	}

	std::ofstream myfile;
	myfile.open("amortization_table3.csv");
	myfile << "# ; opening balance ; principal ; interest rate ; interest ; instalment ; closing balance\n";
	myfile << "i ; PV (i-1) ; P i ; R i ; Int i ; PMT i ; PV i \n";
	for (int j = 0; j < period; j++) {
		for (int i = 0; i < 7; i++) {
			myfile << table[i][j];
			myfile << ";";
		}
		myfile << "\n";
	}
	myfile.close();
	cout << endl << "Thank you for your time, the .csv file has been successfully created." << endl;
	return 0;
}

double gaussianNoise(double mu, double sigma) {

	static const double epsilon = std::numeric_limits<double>::min();
	static const double two_pi = 2.0 * 3.14159265358979323846;
	double z1;
	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon && u2 <= epsilon);

	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
	return (z1 * sigma + mu);
}

double floatmargin_input() {
	double margin;
	cout << "Please first enter the floating rate's  fixed margin M expressed in Annual Percentage Rate (APR) in %." << endl;
	cin >> margin;
	margin = negative_Value(margin);
	margin = margin / 100;
	return margin;
}

double getmean() {
	double mu;
	cout << "Please enter the mean of the floating part expressed as a APR in %" << endl;
	cin >> mu;
	return mu;
}

double getstd() {
	double sigma;
	cout << "Please enter the standard deviation of the floating part expressed in terms of a rate's standard deviation (%)" << endl;
	cin >> sigma;
	return sigma;
}

void floatRateFixedPrincipal(double loanPV, double principal, double rate, int period, int frequency, double mu, double sigma) {
	double noise;
	srand(time(NULL));
	vector<vector<double> > table;
	table.resize(8);

	for (int i = 0; i < 8; i++) {
		table[i].resize(period);
	}

	table[1][0] = loanPV;

	for (int j = 1; j < period; j++) {
		table[1][j] = table[1][j - 1] - principal;
	}

	for (int j = 0; j < period; j++) {

		noise = gaussianNoise(mu, sigma) / 100;
		table[0][j] = j + 1;
		table[2][j] = principal;
		table[3][j] = noise * 100;
		table[4][j] = ((noise + rate) / frequency) * 100;
		table[5][j] = table[1][j] * ((rate + noise) / frequency);
		table[6][j] = table[2][j] + table[4][j];
		table[7][j] = table[1][j] - table[2][j];
	}
	std::ofstream myfile;
	myfile.open("amortization_table2.csv");
	myfile << "input: ; PV ;" << loanPV << "\n";
	myfile << " ; frequency (#payments per year); " << frequency << "\n";
	myfile << " ; # of periods ; " << period << "\n";
	myfile << " ; margin (%) ; " << rate * 100 << "\n";
	myfile << " ; floating rate mean (%) ; " << mu << "\n";
	myfile << " ; floating rate std ; " << sigma << "\n" << "\n" << "\n";

	myfile << "# ; Opening Balance ; Principal ; Floating noise (%) ; Total periodic rate (%) ; Interest ; Instalment ; Closing Balance\n";
	for (int j = 0; j < period; j++) {
		for (int i = 0; i < 8; i++) {
			myfile << table[i][j];
			myfile << ";";
		}
		myfile << "\n";
	}
	myfile.close();
	cout << endl << "Thank you for your time, the .csv file has been successfully created." << endl;
}

int verifiy_Option_Loan () {
	int option;
	while (1) {
			if (cin >> option && (option==1 or option ==2)) {
			break;
			} 
			else {
				cout << "Invalid Input! Please input a proper value." << endl;
				cin.clear();
				while (cin.get() != '\n') ; 
			}
		}
	return option;
}

int verifiy_Option_Fixed_Instal () {
	int option;
	while (1) {
			if (cin >> option && (option==1 or option ==2 or option ==3 or option ==4)) {
			break;
			} 
			else {
				cout << "Invalid Input! Please input a proper value." << endl;
				cin.clear();
				while (cin.get() != '\n') ; 
			}
		}
	return option;
}


int main()
{
	double loanPV, APR, periodicRate, principal, instalment, duration, mu, sigma, noise, margin;
	int frequency, periodNb, optionLoan, optionRate, option_Fixed_Instal;

	cout << "Welcome to Sorbank, a bank for and by Sorbonne students !" << endl;
	cout << "This app is designed to generate with your help your loan payment schedule !" << endl;
	cout << "Please select the type of loan you want to have" << endl;
	cout << "For fixed principal type : 1" << endl;
	cout << "For fixed instalments type : 2" << endl;
	optionLoan=verifiy_Option_Loan();

	if (optionLoan == 1) {
		cout << "You selected a fixed principal loan." << endl;
		cout << "If you want fixed interest rate, type 1" << endl;
		cout << "If you want floating rates, type 2" << endl;
		optionRate =verifiy_Option_Loan();

		if (optionRate == 1) {
			loanPV = loan_value_input();
			duration = duration_input();
			frequency = frequency_input();
			periodicRate = periodic_rate(rate_input(), frequency);
			periodNb = frequency * duration;
			principal = loanPV / periodNb;
			fixedPrincipal(loanPV, principal, periodicRate, periodNb);
		}
		if (optionRate == 2) {
			loanPV = loan_value_input();
			duration = duration_input();
			frequency = frequency_input();
			periodNb = frequency * duration;
			principal = loanPV / periodNb;
			margin = floatmargin_input();
			mu = getmean();
			sigma = getstd();
			floatRateFixedPrincipal(loanPV, principal, margin, periodNb, frequency, mu, sigma);

		}
	}

	if (optionLoan == 2) {
		cout << "You selected a fixed instalments loan." << endl;
		cout << "What informations do you have ? Type the according number (1,2,3 or 4) " << endl;
		cout << "1. Presevent Value, fixed rate, number of years" << endl;
		cout << "2. Instalments, fixed rate, number of years" << endl;
		cout << "3. Presevent Value, Instalments, fixed rate" << endl;
		cout << "4. Presevent Value, Instalments, number of years" << endl;
		option_Fixed_Instal = verifiy_Option_Fixed_Instal() ;

		if (option_Fixed_Instal == 1) {
			loanPV = loan_value_input();
			duration = duration_input();
			frequency = frequency_input();
			periodicRate = periodic_rate(rate_input(), frequency);
			instalment = 0;
			periodNb = frequency * duration;
			amortization_table_fixed_instal(loanPV, periodicRate, periodNb, instalment);
		}

		if (option_Fixed_Instal == 2) {
			instalment = instal_value_input();
			duration = duration_input();
			frequency = frequency_input();
			periodNb = frequency * duration;
			periodicRate = periodic_rate(rate_input(), frequency);
			loanPV = presentValue(instalment, periodicRate, periodNb);
			amortization_table_fixed_instal(loanPV, periodicRate, periodNb, instalment);
		}

		if (option_Fixed_Instal == 3) {
			double rateTpn;
			loanPV = loan_value_input();
			instalment = instal_value_input();
			rateTpn = rate_input();
			frequency = frequency_input();
			periodNb = period_number(loanPV, instalment, rateTpn, frequency);
			periodicRate = periodic_rate(rateTpn, frequency);
			amortization_table_fixed_instal(loanPV, periodicRate, periodNb, instalment);
		}

		if (option_Fixed_Instal == 4) {
			loanPV = loan_value_input();
			instalment = instal_value_input();
			duration = duration_input();
			frequency = frequency_input();
			periodNb = frequency * duration;
			periodicRate = dichotomy(loanPV, instalment, periodNb);
			amortization_table_fixed_instal(loanPV, periodicRate, periodNb, instalment);
		}
	}
	return 0;
}
