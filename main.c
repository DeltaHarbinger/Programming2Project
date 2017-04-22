#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include "companyAndEmployees.h"


COMPANY company[16];

EAGLEEMPLOYEE eagleEmployees[32];
int activeAccount;

//Yes no menu options
char yesNoOptions[][32] = {"Yes", "No"};


//Option 1
void purchase()
{
	char opts[][32] = {"87","90", "Diesel"};
	//Used sizeof instead of constant '3'
	int chosen =	displayArrowMenu("Select Gas Type:", opts, sizeof(opts) / sizeof(opts[0]));


}


void clearScreen()
{
	system("cls");
}



//Used to get information about the comapny and store in temporary variables to be validated (eg. Company Name)
void getInfo(char * message, char * target)
{
	clearScreen();
	puts(message);
	gets(target);
	while(strcmp(target, "") == 0)
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
	char stringArray[576] = "";
	int x;
	for(x = 0; x < s; x++)
		//Construct array using a certain format. In this case, the format includes three strings ALL STORED in the variable stringArray
		sprintf(stringArray, "%s%s%s\n\n", stringArray, infoType[x], info[x]);
	//Appends "Is this okay?" to the message
	strcat(stringArray, "\n\nIs this okay?");
	//Returns 1 or 2 from "Yes" or "No" menu
	return displayArrowMenu(stringArray, yesNoOptions, sizeof(yesNoOptions) / sizeof(yesNoOptions[0]));
}



int reEnterData()
{
	//In the case of incorrectly entered data, this menu may be used
	return displayArrowMenu("Re-enter data?", yesNoOptions, sizeof(yesNoOptions) / sizeof(yesNoOptions[0]));
}



bool authenticateID(char ID)
{
	//Authenticates the ID Type of a customer. This ID should be represented as 'D', 'N' or 'P'
	return ID == 'D' || ID =='N' || ID == 'P';
}



char getIDType()
{
	//Tells user to enter the type of ID the customer is to use
	puts("Enter type of ID\nD - Driver's License\tN - National ID\tP - Passport\t");
	char id = toupper(_getch());
	//Ensures ID is 'D', 'N', or 'P'
	while(!authenticateID(id))
	{
		clearScreen();
		puts("Please Enter a valid ID type\nD - Driver's License\tN - National ID\tP - Passport\t");
		id = toupper(_getch());
	}
	//Returns valid ID
	return id;
}



bool checkCustomerInfo(EMPLOYEE source)
{
	char message[1000] = "";
	sprintf(message, "Name\t :\t%s\n\nID Type\t :\t%c\n\nID Number:\t%d\n\n", source.customerName, source.iDType, source.customerIDNumber);
	return displayArrowMenu(message, yesNoOptions, sizeof(yesNoOptions) / sizeof(yesNoOptions[0])) == 1;
}



void storeCustomerInfo(EMPLOYEE * dest, EMPLOYEE source)
{
	*dest = source;
	company[numberOfCompanies].numberOfCustomers++;
}

void displayAllCustomerInfo(int companyCode)
{
	int x;
	printf("\nID Type\t\tID Number\tName\n\n");
	for (x = 0; x < company[companyCode].numberOfCustomers; x++)	printf("%c\t\t%i\t\t%s\n", company[companyCode].employees[x].iDType, company[companyCode].employees[x].customerIDNumber, company[companyCode].employees[x].customerName);
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
	int customerPositionNumber = ((customerNumber - ((companyNumber + 1) * 1000)) / 10) - 1;
	(companyNumber >= 0 && (companyNumber + 1) * 1000 + (customerPositionNumber + 1) * 10 == customerNumber && companyNumber < numberOfCompanies && customerPositionNumber < company[companyNumber].numberOfCustomers) ? printf("Company Name\n%s\n\nCompany Code\n%i\n\nCustomer Name\n%s\n\nCustomer ID Number\n%i\n", company[companyNumber].companyName, eagleEmployees[activeAccount].jobType == PUMP_ATTENDANT ? 0 : company[companyNumber].companyCode, company[companyNumber].employees[customerPositionNumber].customerName, company[companyNumber].employees[customerPositionNumber].customerIDNumber) : printf("Invalid Customer Number\n" );
}

void printCompanyData(int companyNumber)
{
	companyNumber = (((companyNumber / 1000) - 1) + 1) * 1000 == companyNumber ? (companyNumber / 1000) - 1 : -1;
	companyNumber >= 0 && companyNumber < numberOfCompanies ? printf("Company Name\n%s\n\nContact Number\n%s\n\nContact Name\n%s\n\nContact Email\n%s\n\nCompany Code\n%i\n\nNumber of Customers\n%i\n\n", company[companyNumber].companyName, company[companyNumber].companyContactTelephoneNumber, company[companyNumber].companyContactName, company[companyNumber].companyContactPersonEmail, eagleEmployees[activeAccount].jobType == PUMP_ATTENDANT ? 0 : company[companyNumber].companyCode, company[companyNumber].numberOfCustomers) : printf("Invalid Company Code\n");
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
		EMPLOYEE tempEmployee;

		getInfo("Enter Customer Name", tempEmployee.customerName);
		tempEmployee.iDType = getIDType();
		tempEmployee.customerIDNumber = (numberOfCompanies + 1) * 1000 + (*numEmployees + 1) * 10;

		checkCustomerInfo(tempEmployee) ? storeCustomerInfo(&company[numberOfCompanies].employees[*numEmployees], tempEmployee) : false;
		keepEntering = continueEnteringClients();
	}
}


//Option 3
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
			reEnter = reEnterData();
		else
		{
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
	}
}

//Option 4 (during exit)
void fileWrite()
{
	FILE * fp;
	fp = fopen("companyData.dat", "wb");
	int x;
	for(x = 0; x < numberOfCompanies; x++)
	{
		int y;
		fwrite(&company[x], sizeof(COMPANY), 1, fp);
	}
	fclose(fp);
}

//Reads all data from file
void fileRead()
{

	int x = 0;
	if(fopen("companyData.dat", "rb")){
		FILE * fp;
		fp = fopen("companyData.dat", "rb");
		while(!feof(fp)){
			fread(&company[numberOfCompanies], sizeof(COMPANY), 1, fp);
			numberOfCompanies++;
		}
		numberOfCompanies--;
		fclose(fp);
	}

}

bool confirmEagleAccount(EAGLEEMPLOYEE employee)
{
	char message[256];
	char jobType[16];
	if(employee.jobType == 1)
	{
		strcpy(jobType, "Manager");
	}
	else
	{
		if(employee.jobType == 2)
		{
			strcpy(jobType, "Cashier");
		}
		else
		{
			strcpy(jobType, "Pump Attendant");
		}
	}

	sprintf(message, "Name:\t%s\n\nUserName:\t%s\n\nJob Type:\t%s\n\nIs this okay?", employee.eagleEmployeeName, employee.eagleUserName, jobType);
	return displayArrowMenu(message, yesNoOptions, sizeof(yesNoOptions) / sizeof(yesNoOptions[0])) == 1;
}

bool authenticatePassword(char * a, char * b)
{
	return strcmp(a, b) == 0;
}

void createEagleAccount(int jobType)
{
	EAGLEEMPLOYEE temp;
	temp.jobType = jobType;
	getInfo("Enter Employee Name (Max 31 Characters)", temp.eagleEmployeeName);
	getInfo("Enter Employee Username (Max 31 Characters)", temp.eagleUserName);
	getInfo("Enter Employee Password (Max 31 Characters)", temp.eaglePassword);
	char tempPassword[32];
	getInfo("Re-enter Employee Password", tempPassword);
	if(strcmp(tempPassword, temp.eaglePassword) == 0)
	{
		if(confirmEagleAccount(temp))
		{
			eagleEmployees[numberOfEagleEmployees] = temp;
			numberOfEagleEmployees++;
		}
	}
}



void searchInfo()
{
	char options[2][32] = {"Customer ID Number", "Company Code"};
	char * message = "Choose the field to search";
	int searchOption = displayArrowMenu(message, options, sizeof(options) / sizeof(options[0]));
	int searchQuerry;
	printf("Enter %s\n", options[searchOption - 1]);
	fflush(stdin);
	scanf(" %i", &searchQuerry);
	clearScreen();
	switch (searchOption) {
		case 1:
			printCustomerData(searchQuerry);
			system("pause");
			break;
		case 2:
			printCompanyData(searchQuerry);
			system("pause");
			break;
	}
}

bool AccountExists()
{
	return fopen("eagleEmployees.dat", "rb");
}

void writeEagleEmployeeData()
{
	FILE * fp;
	fp = fopen("eagleEmployees.dat", "wb");
	int x;
	for(x = 0; x < numberOfEagleEmployees; x++)
		fwrite(&eagleEmployees[x], sizeof(EAGLEEMPLOYEE), 1, fp);
}

void getEagleEmployeeData()
{
	if(!AccountExists())
	{
		printf("No employee data has been created.\nAn administrator account will have to be created before the system is used.");
		Sleep(5000);
		while(numberOfEagleEmployees < 1)
			createEagleAccount(MANAGER);
		writeEagleEmployeeData();
		system("cls");
	}
	else
	{
		FILE * fp;
		fp = fopen("eagleEmployees.dat", "rb");
		while(!feof(fp))
		{
			fread(&eagleEmployees[numberOfEagleEmployees], sizeof(EAGLEEMPLOYEE), 1, fp);
			numberOfEagleEmployees++;
		}
		fclose(fp);
	}

}

//Debugging option 5
void printAllData()
{
	int x, y;
	for(x = 0; x < numberOfCompanies; x++)
	{
		displayRegisteredCustomers(company[x].companyCode);
	}
}

//Option 6, Creating New Account
void createNewEagleAccount()
{
	char accountTypes[3][32] = { "Manager", "Cashier", "Pump Attendant"};
	char * message = "Choose the account type";
	createEagleAccount(displayArrowMenu(message, accountTypes, sizeof(accountTypes) / sizeof(accountTypes[0])));
}
void fullMenuFunctions(int menuOption)
{
	switch (menuOption)
	{
		case 1:
			purchase();
			break;
		case 2:
			fileWrite();
			writeEagleEmployeeData();
			break;
		case 3:
			searchInfo();
			break;
		case 4:
			addCompany();
			break;
		case 5:
			printAllData();
			break;
		case 6:
			createNewEagleAccount();
			break;
	}
}

//Display Menu and get option
int displayArrowMenu(char * message, char menu[][32], int s)
{
	int position = 0, x, test = 0;
	while (test != 13)
	{
		clearScreen();
		puts(message);
		for (x = 0; x < s; x++)	printf("%s%s%s\n", position == x ? "-->" : "  ", menu[x], position == x ? "<--" : "");
		test = (test = _getch()) == 224 ? _getch() : test;
		(test == 72 && position != 0) ? position-- : (test == 80 && position != s - 1) ? position++ : false;
	}
	return  position + 1;
}

int searchAccount(char accountInfo[2][32])
{
	int x = 0;
	bool found = false;
	while( x < numberOfEagleEmployees && found == false)
		(strcmp(accountInfo[0], eagleEmployees[x].eagleUserName) == 0 && strcmp(accountInfo[1], eagleEmployees[x].eaglePassword) == 0) ? found = true : x++;
	return found ? x : -1;
}

bool login()
{
	char credentials[2][32];
	printf("Enter Your UserName:");
	gets(credentials[0]);
	printf("Enter Your Password:");
	gets(credentials[1]);
	int workingAccount = searchAccount(credentials);
	system("cls");
	if(workingAccount != -1){
		activeAccount = workingAccount;
		return true;
	}
	return false;
}

void displayManagerMenu()
{
	int menuOption = 1;
	char * message = "Enter an option";
	while (menuOption != 2)
	{
		char options[][32] = { "Pump Gas", "Save and Exit", "Search Information", "Register Company", "Print All Data", "Create New Eagle Employee"};
		menuOption = displayArrowMenu(message, options, sizeof(options) / sizeof(options[0]));
		clearScreen();
		fullMenuFunctions(menuOption);
	}
}

void displayCashierMenu()
{
	int menuOption = 1;
	char * message = "Enter an option";
	while (menuOption != 2)
	{
		char options[][32] = { "Pump Gas", "Save and Exit", "Search Information"};
		menuOption = displayArrowMenu(message, options, sizeof(options) / sizeof(options[0]));
		clearScreen();
		fullMenuFunctions(menuOption);
	}
}

void displayPumpAttendantMenu()
{
	int menuOption = 1;
	char * message = "Enter an option";
	while (menuOption != 2)
	{
		char options[][32] = { "Pump Gas", "Save and Exit", "Search Information"};
		menuOption = displayArrowMenu(message, options, sizeof(options) / sizeof(options[0]));
		clearScreen();
		fullMenuFunctions(menuOption);
	}
}

void displayEmployeeMenu()
{
	switch(eagleEmployees[activeAccount].jobType)
	{
		case MANAGER:
			displayManagerMenu();
			break;
		case CASHIER:
			displayCashierMenu();
			break;
		case PUMP_ATTENDANT:
			displayPumpAttendantMenu();
			break;
		default:
			printf("WTF happened?\n");
	}
}

void main()
{
	//Reads all data from file at startup
	getEagleEmployeeData();
	fileRead();
	if(login())
	{
		displayEmployeeMenu();
	} else {
		puts("This Account does not exist");
	}
}
