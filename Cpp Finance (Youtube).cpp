# include <iostream>
# include <cmath>
# include <iomanip>

# include "multiplier.h"
# include "divisor.h"
# include "globals.h"

using namespace std;

enum AmortizeProgram {
	AP_LOAN_PRINCIPAL = 1,
	AP_INTEREST_RATE = 2,
	AP_YEARS_OF_LOAN = 3
};

string AmortHeader[] = {
		"Yr",
		"Mn",
		"CumMn",
		"Payment",
		"Interest",
		"Principal",
		"Balance"
};

enum AmortEnum{
	YR_OUT = 2,
	MN_OUT = 2,
	CUM_MN_OUT = 5,
	PAYMENT_OUT = 12,
	INTEREST_OUT = 12,
	PRINCIPAL_OUT = 12,
	BALANCE_OUT = 16
};

void printAmortHeader() {
	cout <<
			endl <<
			setw(YR_OUT) << AmortHeader[0] << " " <<
			setw(MN_OUT) << AmortHeader[1] << " " <<
			setw(CUM_MN_OUT) << AmortHeader[2] << " " <<
			setw(PAYMENT_OUT) << AmortHeader[3] << " " <<
			setw(INTEREST_OUT) << AmortHeader[4] << " " <<
			setw(PRINCIPAL_OUT) << AmortHeader[5] << " " <<
			setw(BALANCE_OUT) << AmortHeader[6] << " " <<
			endl << endl;
}

int main(int argc, char*argv[]) {

	cout << "argc: " << argc << endl;
	cout << "argv[0]: " << argv[0] << endl; // gives the full name of the program.

	for(int i = 0; i < argc; i = i + 1) {
		cout << "argv[" << i << "]:" << argv[i] << endl;
	}                                                       // this part is useful for editing the "scheme"


	double principal = 0.00;
	double inputInterest = 0.00;
	int yearsOfLoan = 0.00;

	if(argc == 1){
		cout << "Principal amount? " << flush;
		cin >> principal;

		cout << "Interest amount? " << flush;
		cin >> inputInterest;

		cout << "Years of the loan? " << flush;
		cin >> yearsOfLoan;
	} else {
		principal = atof(argv[AP_LOAN_PRINCIPAL]);    // atof - a string to a float - turns into a decimal point number
		inputInterest = atof(argv[AP_INTEREST_RATE]); // Check the enum at the top of the document for parameter values
		yearsOfLoan = atoi(argv[AP_YEARS_OF_LOAN]);  // atoi - a string to int
	}

	cout << "Loan Principal: " << principal << endl;
	cout << "Interest Rate: " << inputInterest << "%" << endl;
	cout << "Time Period: " << yearsOfLoan << "year(s) " << endl;


	double interest = simpleDivisor(inputInterest, glbPercentDenominator);
	double monthInterest = simpleDivisor(interest, glbMonthsInYear);
	long monthsOfLoan = simpleMultiplier(yearsOfLoan, glbMonthsInYear);

	double monthlyPayment = 0.00;

	monthlyPayment = principal *
			(monthInterest /
					(1 - (pow((double)1 + monthInterest,
							(double)-monthsOfLoan))));

	cout << "Monthly Payments: " << setiosflags(ios::fixed) << setprecision(2) << monthlyPayment << endl;

	cout << principal << " " << interest << " " << yearsOfLoan <<
			" " << monthInterest << " " << monthsOfLoan << endl;

	double currentInterestPayment = 0.00;
	double currentPrincipalPayment = 0.00;
	double currentBalance= 0.00;

	currentBalance = principal;

	long currentLoanMonth = 1;

	int year = 1;
	int switchYear = 0;
	int yearMonth = 1;

	while(currentLoanMonth <= monthsOfLoan){
		//cout << "Current Loan Month: " << currentLoanMonth << endl;

		if(switchYear != year){
			switchYear = year;

			printAmortHeader();
		}


		glbAmortizeMonth amortMonth;

		currentInterestPayment = currentBalance * monthInterest;
		currentPrincipalPayment = monthlyPayment - currentInterestPayment;
		currentBalance = abs(currentBalance - currentPrincipalPayment);

		amortMonth.year = year;
		amortMonth.yearMonth = yearMonth;
		amortMonth.loanMonth = currentLoanMonth;
		amortMonth.payment = monthlyPayment;
		amortMonth.pureInterest = currentInterestPayment;
		amortMonth.paidDownPrincipal = currentPrincipalPayment;
		amortMonth.principalBalance = currentBalance;


		cout <<
				setw(YR_OUT) << amortMonth.year << " " <<                 //setw here because we previously used
				setw(MN_OUT) << amortMonth.yearMonth << " " <<            // setprecision(2) to configure decimal places
				setw(CUM_MN_OUT) << amortMonth.loanMonth << " " <<
				setw(PAYMENT_OUT) << amortMonth.payment << " " <<
				setw(INTEREST_OUT) << amortMonth.pureInterest << " " <<
				setw(PRINCIPAL_OUT) << amortMonth.paidDownPrincipal << " " <<
				setw(BALANCE_OUT) << amortMonth.principalBalance <<
				endl;

		yearMonth = yearMonth + 1;
		if(yearMonth < glbMonthsInYear){     // this part forces the months back to 1 when it passes 12 months
			yearMonth = 1;                   // and also adds an additional year - i.e. start at Jan of year x.
			year = year + 1;
		}

		currentLoanMonth = currentLoanMonth + 1;
	}

	cout << endl <<  "Loan Repayments Complete" << endl << endl;

	return 0;
}
