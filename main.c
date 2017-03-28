#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include "companyAndEmployees.h"

COMPANY company[16];

//Yes no menu options
char yesNoOptions[][32] = {"Yes", "No"};

//Option 1
void purchase()
{
	//int choice;
	char opts[][32]={"87 gasoline","90 gasoline", "Diesel"};
	int chosen=	displayArrowMenu("Select Gas Type:", opts,3 );
	//choice = displayArrowMenu
	switch (chosen)
	{
		case 1:
			puts("Hey!!\n");
			system ("pause");
			break;
		case 2:
			break;
		case 3:
			break;
	}
}

void clearScreen()
{
	system("cls");
}

//Used to get information about the comapny and store in temporary variables to be validated (eg. Company Name)
void getInfo(char * message, char * target)
{
	puts(message);
	gets(target);
	clearScreen();
}

//Stores information for a company just created
void storeCompanyInfo(char companyInfo[][32])
{
	strcpy(company[numberOfCompanies].companyName, companyInfo[0]);
	strcpy(company[numberOfCompanies].companyContactName, companyInfo[1]);
	strcpy(company[numberOfCompanies].companyContactPersonEmail,companyInfo[2]);
	strcpy(company[numberOfCompanies].companyContactTelephoneNumber, companyInfo[3]);
}

//Incraments number of companies registered
void incramentNumberOfCompanies()
{
	numberOfCompanies++;
}

int checkInfo(char infoType[][32], char info[][32], int s)
{
	char stringArray[1000] = "";
	int x;
	for(x = 0; x < s; x++)
	{
		strcat(stringArray, ("%s:", infoType[x]));
		strcat(stringArray, info[x]);
		strcat(stringArray, "\n\n");
	}
	strcat(stringArray, "\nIs this okay?");
	return displayArrowMenu(stringArray, yesNoOptions, sizeof(yesNoOptions) / sizeof(yesNoOptions[0]));
}

int reEnterData()
{
	return displayArrowMenu("Re-enter data?", yesNoOptions, sizeof(yesNoOptions) / sizeof(yesNoOptions[0]));
}

bool authenticateID(char ID)
{
	return ID == 'D' || ID =='N' || ID == 'P';
}

char getIDType()
{
	puts("Enter type of ID\nD - Driver's License\tN - National ID\tP - Passport\t");
	char id = toupper(_getch());
	while(!authenticateID(id))
	{
		clearScreen();
		puts("Please Enter a valid ID type\nD - Driver's License\tN - National ID\tP - Passport\t");
		id = toupper(_getch());
	}
	return id;
}

bool checkCustomerInfo(char * name, char iDType, int IDNumber)
{
	char message[1000] = "";
	sprintf(message, "Name\t :\t%s\n\nID Type\t :\t%c\n\nID Number:\t%d\n\n", name, iDType, IDNumber);
	return displayArrowMenu(message, yesNoOptions, sizeof(yesNoOptions) / sizeof(yesNoOptions[0])) == 1;
}

void storeCustomerInfo(int companyNumber, int customerNumber, char name[32], char iDType, int iDNumber)
{
	strcpy(company[companyNumber].employees[customerNumber].customerName, name);
	company[companyNumber].employees[customerNumber].iDType = iDType;
	company[companyNumber].employees[customerNumber].companyCode = (companyNumber + 1) * 1000;
	company[companyNumber].employees[customerNumber].customerIDNumber = company[companyNumber].employees[customerNumber].companyCode + (customerNumber + 1) * 10;
	company[companyNumber].numberOfCustomers++;
}

void displayAllCustomerInfo(int companyCode)
{
	int x;
	printf("\nID Type\t\tID Number\tName\n\n");
	for (x = 0; x < company[companyCode].numberOfCustomers; x++) {
		printf("%c\t\t%i\t\t%s\n", company[companyCode].employees[x].iDType, company[companyCode].employees[x].customerIDNumber, company[companyCode].employees[x].customerName);
	}
}

void displayRegisteredCustomers(int companyCode)
{
	companyCode = (companyCode / 1000) - 1;
	clearScreen();
	printf("The Following Employees have been registeed for %s\n", company[companyCode].companyName);
	displayAllCustomerInfo(companyCode);
	system("pause");
}

void printCustomerData(int customerNumber)
{
	int companyNumber = (customerNumber / 1000) - 1;
	customerNumber = ((customerNumber - ((companyNumber + 1) * 1000)) / 10) - 1;
	printf("%s\n", company[companyNumber].employees[customerNumber].customerName);
}

bool continueEnteringClients()
{
	char * message = "Continue entering clients?";
	return displayArrowMenu(message, yesNoOptions, sizeof(yesNoOptions) / sizeof(yesNoOptions[0])) == 1;
}

void addEmployees()
{
	bool keepEntering = true;
	company[numberOfCompanies].numberOfCustomers = 0;
	int * numEmployees = &company[numberOfCompanies].numberOfCustomers;
	while (keepEntering && company[numberOfCompanies].numberOfCustomers < 32)
	{
		clearScreen();
		char tempCustomerName[32], tempID;
		getInfo("Enter Customer Name", tempCustomerName);
		tempID = getIDType();
		int tempIDNumber = (numberOfCompanies + 1) * 1000 + (*numEmployees + 1) * 10;

		checkCustomerInfo(tempCustomerName, tempID, tempIDNumber) ? storeCustomerInfo(numberOfCompanies, *numEmployees, tempCustomerName, tempID, tempIDNumber) : false;
		keepEntering = continueEnteringClients();
	}
}

void addCompany()
{
	int x, isCorrect = 2, reEnter = 1;
	char tempCompanyInfo[4][32];
	char companyInfoName[][32] = {"Company Name\n", "Company Contact Name\n", "Company Contact Email\n", "Company Contact Number\n"};
	//Creates a 2D array to show later as a menu
	while (isCorrect == 2 && reEnter == 1)
	{
		//Gets company info
		for(x = 0; x < 4; x++) getInfo(companyInfoName[x], tempCompanyInfo[x]);
		isCorrect = checkInfo(companyInfoName, tempCompanyInfo, sizeof(companyInfoName) / sizeof(companyInfoName[x]));
		if(isCorrect == 2)
		{
			reEnter = reEnterData();
		}
		else {
			storeCompanyInfo(tempCompanyInfo);
			company[numberOfCompanies].companyCode = (numberOfCompanies + 1) * 1000;
			clearScreen();
		}

	}
	/////ADD EMPLOYEES
	if(isCorrect == 1)
	{
		addEmployees();
		if(company[numberOfCompanies].numberOfCustomers > 0)
		{
			displayRegisteredCustomers(company[numberOfCompanies].companyCode);
			incramentNumberOfCompanies();
		}
		else
			false;
	}
}

/*
//Option 3
void addCompany() {
	char isCorrect = 'n', reEnter = 'y';
	while (isCorrect == 'n' && reEnter == 'y') {
		char companyInfo[3][30] = { "Company Name\n", "Company Contact Name\n", "Company Contact Email\n" };
		int x;
		for (x = 0; x < 3; x++)
			getInfo(companyInfo[x]);
		for (x = 0; x < 3; x++)
			puts(companyInfo[x]);
		puts("Is this correct?");
		isCorrect = _getch();
		while (isCorrect != 'y' && isCorrect != 'n') {
			printf("\nPlease enter y or n");
			isCorrect = _getch();
		}
		if (isCorrect == 'n') {
			printf("\nWould you like to enter the data again?\n");
			reEnter = _getch();
			while (reEnter != 'y' && reEnter != 'n') {
				printf("\nPlease enter y or n\n");
				reEnter = _getch();
			}
		}
		else {
			storeCompanyInfo(companyInfo);
			companyCode[numberOfCompanies] = (numberOfCompanies + 1) * 1000;
			incramentNumberOfCompanies();
			char continueEnteringClients = 'y';
			x = 0;
			while (continueEnteringClients == 'y' && x < 10) {
				clearScreen();
				char tempcustomerName[30];
				char iDType;
				printf("Enter the Customer's Name\n");
				scanf(" %s", tempcustomerName);
				printf("\nEnter the type of ID the customer will use (P - Passport, N - National ID, D - Driver's License)\n");
				iDType = _getch();
				iDType = toupper(iDType);
				printf("\n%s\n%c\nIs this correct? (y/n)\n", tempcustomerName, iDType);
				char correct =_getch();
				while (correct != 'y' && correct != 'n') {
					printf("\nPlease enter a valid option\n\n%s\n%c\nIs this correct? (y/n)\n", tempcustomerName, iDType);
					correct =_getch();
				}
				if (correct == 'y') {
					strcpy(customerName[numberOfCompanies - 1][x], tempcustomerName);
					customerIDNumber[numberOfCompanies - 1][x] = companyCode[numberOfCompanies - 1] + ((x + 1) * 60);
					customerTypeOfID[numberOfCompanies - 1][x] = iDType;
					x++;
					printf("%s\n", customerName[numberOfCompanies - 1][x - 1]);
					printf("Would you like to continue entering clients? (y/n)");
					continueEnteringClients =_getch();
					while (continueEnteringClients != 'y' && continueEnteringClients != 'n') {
						printf("Would you like to continue entering clients? (y/n)");
						continueEnteringClients =_getch();
					}
				}
				else {
					printf("Would you like to re-enter the information? (y/n)\n");
					reEnter =_getch();
					while (reEnter != 'y' && reEnter != 'n') {
						printf("Please enter a valid option\nWould you like to re-enter the information?(y/n)\n");
						reEnter =_getch();
					}
					if (reEnter != 'y') {
						printf("\nContinue entering clients?\n");
						continueEnteringClients =_getch();
						while (continueEnteringClients != 'y' && continueEnteringClients != 'n') {
							printf("Please enter a valid response.\nStop entering clients?\n");
							continueEnteringClients =_getch();
						}
					}
				}
			}
			int z;
			clearScreen();
			for (z = 0; z < x; z++)
				printf("\n%s\t%c", customerName[numberOfCompanies - 1][z], customerTypeOfID[numberOfCompanies - 1][z]);
			printf("\nThese employees have been registered\n");
			system("pause");
		}
	}
	clearScreen();
}
*/

void menuFunctions(int menuOption) {
	switch (menuOption)
	{
		case 1:
			purchase(menuOption);
			break;
		case 2:
			break;
		case 3:
			addCompany();
			break;
		case 4:
			break;
	}
}

//Display Menu and get option
int displayArrowMenu(char * message, char menu[][32], int s)
{
	int position = 0, x, test = 0;
	while (test != 8 && test != 13)
	{
		clearScreen();
		puts(message);
		for (x = 0; x < s; x++) printf("%s%s%s\n", position == x ? "-->" : "  ", menu[x], position == x ? "<--" : "");
		test = ((test = _getch())== -32) ? _getch() : test;
		(test == 72 && position != 0) ? position-- : false;
		(test == 80 && position != s - 1) ? position++ : false;
	}
	return  position + 1;
}



void main()
{
	int menuOption = 1;
	char * message = "Enter an option";
	while (menuOption != 4) {
		char options[][32] = { "Pump Gas", "Employee Login", "Register Company", "Exit"};
		menuOption = displayArrowMenu(message, options, sizeof(options) / sizeof(options[0]));
		clearScreen();
		menuFunctions(menuOption);
	}
}
