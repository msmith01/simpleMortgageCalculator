/*
 * globals.h
 *
 *  Created on: 6 mar. 2020
 *      Author: Matt
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_


	const int glbMonthsInYear = 12;
	const int glbPercentDenominator = 100;

	struct glbAmortizeMonth {
		int year;
		int yearMonth;
		long loanMonth;
		double payment;
		double pureInterest;
		double paidDownPrincipal;
		double principalBalance;
	};


#endif /* GLOBALS_H_ */
