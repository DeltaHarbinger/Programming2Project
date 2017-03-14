#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

int companyCode[10], companyContactTelephoneNumber[10], customerIDNumber[10][10];
int customerCompanyIDNumber[10], customerPersonalIDNumber[10][10];
int closeProgram = 0, numberOfCompanies = 0;
char companyName[10][30], companyContactName[10][30], companyContactPersonEmail[10][30], customerTypeOfID[10][10];
char customerName[10][10][30];


//Used to get information about the comapny and store in temporary variables to be validated (eg. Company Name)
void getCompanyInfo(char * message) {
	char companyInfo[30];
	printf("%s", message);
	gets(message);
	system("cls");
}


//Stores information for a company just created
void storeCompanyInfo(char companyInfo[][30]) {
	strcpy(companyName[numberOfCompanies], companyInfo[0]);
	strcpy(companyContactName[numberOfCompanies], companyInfo[1]);
	strcpy(companyContactPersonEmail[numberOfCompanies],companyInfo[2]);
}

//Incraments number of companies registered
void incramentNumberOfCompanies() {
	numberOfCompanies++;
}

//Option 3
void AddCompany() {
	char isCorrect = 'n', reEnter = 'y';
	while (isCorrect == 'n' && reEnter == 'y') {
		char companyInfo[3][30] = { "Company Name\n", "Company Contact Name\n", "Company Contact Email\n" };
		int x;
		for (x = 0; x < 3; x++)
			getCompanyInfo(companyInfo[x]);

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
				system("cls");
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
			system("cls");
			for (z = 0; z < x; z++)
				printf("\n%s\t%c", customerName[numberOfCompanies - 1][z], customerTypeOfID[numberOfCompanies - 1][z]);
			printf("\nThese employees have been registered\n");
			system("pause");
		}
	}
	system("cls");

}

void menuFunctions(int menuOption) {
	switch (menuOption) {
	case 1:

		break;
	case 2:
		break;
	case 3:
		AddCompany();
		break;
	case 4:
		break;
	default:
		printf("Enter a valid option\n");
	}
}

//Display Menu and get option
int getMenuOption(char menu[][30], int s) {
	int position = 0, x, test = 0;
	while (test != 8 && test != 13)
	{
		system("cls");
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
	while (menuOption != 4) {
		char options[][30] = { "Pump Gas", "Employee Login", "Register Company", "Exit"};
		menuOption = getMenuOption(options, sizeof(options) / sizeof(options[0]));
		system("cls");
		menuFunctions(menuOption);
	}
}
