#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include "companyAndEmployees.h"
#include <time.h>
#include <math.h>

COMPANY company[16];

EAGLEEMPLOYEE eagleEmployees[32];
int activeAccount;

//Yes no menu options
char yesNoOptions[][32] = {"Yes", "No"};

void clearScreen()
{
	system("cls");
}

void receipt(PURCHASE * temp)
{
  int i;
  char types[3][32] = { "87", "90", "Diesel" };
  char gas;
  COMPANY tab;
  clearScreen();
	printf("Sale ID: %i\t\tBranch: %i\t\tPump: %i\t\tEmployee Number: %i\n\nDate: %i\n\n", (*temp).saleIDNumber, (*temp).stationNumber, (*temp).pumpNumber, (*temp).employeeID, (*temp).eightDigitSaleDate);
  printf("\n\t\t\t\tEAGLE ENERGY LTD\n");
  printf("\n\t\tCompany ID\t  Litres\t  Cost($)\t  Gas Type\n\n\n");
  printf("\n\t\t%d\t\t%.2f\t\t%.2f\t\t%s", (*temp).companyCode, (*temp).litresOfPetrol , (*temp).costOfSale, types[(*temp).gasType - 1]);
  printf("\n\n\n\t\t\t\tThank you!");
  printf("\n\t\t\t\tHave a Nice day\n");
  getch();
}

//Option 1
float gasMessage(PURCHASE * temp)
{
  float amt;
  bool confirm = false;
  do
  {
    clearScreen();
    puts("How much dollars worth:\n");
    scanf("%f", &amt);
		char message[30];
		sprintf(message, "Is this correct?\n %f", amt);
    confirm = displayArrowMenu(message, yesNoOptions, sizeof(yesNoOptions) / sizeof(yesNoOptions[0])) == 1;
  } while(confirm == false);
  return amt;
}

int getSaleIDNumber()
{
	PURCHASE temp;
	int saleID = 1;
	if(fopen("purchaseData.dat", "rb"))
	{
		FILE * fp;
		fp = fopen("purchaseData.dat", "rb");
		while(!feof(fp))
		{
			fread(&temp, sizeof(PURCHASE), 1, fp);
			saleID++;
		}
		saleID--;
		fclose(fp);
	}
	return saleID;
}

bool dateValid(int day)
{
	FILE * fp;
	fp = fopen("date.txt", "r");
	int month, year;
	fscanf(fp, "%i\n%i\n", &month, &year);
	fclose(fp);
	if(day > 0)
	{
		if(month == 2)
		{
			if(year % 4 == 0 && year % 100 != 0)
				return day < 30;
			else
				return day < 29;
		}
		else
		{
			if(month == 4 || month ==  6 || month == 9 || month == 11)
				return day < 31;
			else
				return day < 32;
		}
	}
	else
		return false;

}

void ppLitre(int line, PURCHASE * temp)
{
  FILE *ptr;
  float value,amount,litres;
  int i;
  (*temp).costOfSale = gasMessage(temp);
  //printf("%.2f",am);
  ptr=fopen("Priceperlitre.txt", "r");
  //fread()
  value = 0.0;
  for(i=0;i<line;i++)
  {
      fscanf(ptr, "%f\n", &(*temp).costPerLitre);
  }
  (*temp).litresOfPetrol= (*temp).costOfSale / (*temp).costPerLitre;
  printf("Amount of litres is : %.2f\n", (*temp).litresOfPetrol);
  system("pause");
  fclose(ptr);
	(*temp).saleIDNumber = getSaleIDNumber();
	int date;
	do {
		printf("Enter the day (1 - 31)");
		scanf("%i", &date);
	} while(!(dateValid(date)));
	(*temp).eightDigitSaleDate = date * 1000000 + getDate();
	receipt(temp);
}

//Option 1
void purchase(PURCHASE * temp)
{

    char opts[][32] = {"  87","  90", "  Diesel"};
    //Used sizeof instead of constant '3'
    clearScreen();
		do
		{
			printf("Enter the pump number (Any numer above zero)\n");
			scanf(" %i", &(*temp).pumpNumber);
			clearScreen();
		} while((*temp).pumpNumber < 1);
		(*temp).stationNumber = eagleEmployees[activeAccount].branchNumber;
		(*temp).employeeID = eagleEmployees[activeAccount].eagleEmployeeNumber;
    ppLitre((*temp).gasType = displayArrowMenu("Select Gas Type:", opts, sizeof(opts) / sizeof(opts[0])), temp);
}

void storePurchase(PURCHASE purchaseToStore)
{
	FILE * fp;
  if(!fopen("purchaseData.dat", "rb"))
  	fp = fopen("purchaseData.dat", "wb");
	else
		fp = fopen("purchaseData.dat", "ab");
	fwrite(&purchaseToStore, sizeof(PURCHASE), 1, fp);
	fclose(fp);
}

//ID Number:\t%d\n\n"
void pumpGas()
{
  PURCHASE temp;
  int code,pID,x;
  clearScreen();
  puts("Enter Company Code:\n"); scanf(" %d", &temp.companyCode);
  puts("Enter Personal IDNumber:"); scanf(" %d", &temp.customerIDNumber);
  code = (temp.companyCode / 1000) - 1;
	bool pumped = false;
	if((code + 1) * 1000 == temp.companyCode)
	  for (x = 0; x < company[code].numberOfCustomers; x++)
		{
			if (temp.customerIDNumber == company[code].employees[x].personalIDNumber)
			{
				purchase(&temp);
				pumped = true;
				storePurchase(temp);
				company[code].employees[x].numberOfPurchases++;
			}
			else
				if (!pumped && x == company[code].numberOfCustomers - 1 && temp.customerIDNumber != company[code].employees[x].personalIDNumber)
				{
					system("cls");
					puts("\n\n\n\n\n\t\t\t\tID Number not found!\n");
					system("pause");
				}
		}
	else
	{
		printf("Inalid Company Code\n");
		system("pause");
	}
  clearScreen();
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
	printf("%c\n", id);
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

bool idTaken(int iD)
{
	int x;
	bool taken = false;
	while(!taken && x < company[numberOfCompanies].numberOfCustomers)
		iD == company[numberOfCompanies].employees[x].personalIDNumber ? taken = true : x++;
	return taken;
}

int getPersonalIDNumber(int companyCode)
{
	int personalID;
	do
		personalID = (companyCode + 1) * 10000 + rand() % 1000;
	while(idTaken(personalID));
	return personalID;
}

void storeCustomerInfo(EMPLOYEE * dest, EMPLOYEE source, int companyNumber)
{

	*dest = source;
	company[companyNumber].numberOfCustomers++;
}

void displayAllCustomerInfo(int companyCode)
{
	int x;
	printf("\nID Type\t\tID Number\tPersonal ID\tName\n\n");
	for (x = 0; x < company[companyCode].numberOfCustomers; x++)	printf("%c\t\t%i\t\t%i\t%s\n", company[companyCode].employees[x].iDType, company[companyCode].employees[x].customerIDNumber, company[companyCode].employees[x].personalIDNumber, company[companyCode].employees[x].customerName);
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
	(companyNumber >= 0 && (companyNumber + 1) * 1000 + (customerPositionNumber + 1) * 10 == customerNumber && companyNumber < numberOfCompanies && customerPositionNumber < company[companyNumber].numberOfCustomers) ? printf("Company Name\n%s\n\nCompany Code\n%i\n\nCustomer Name\n%s\n\nCustomer ID Number\n%i\n", company[companyNumber].companyName, eagleEmployees[activeAccount].jobType == PUMP_ATTENDANT ? 0 : company[companyNumber].companyCode , company[companyNumber].employees[customerPositionNumber].customerName, company[companyNumber].employees[customerPositionNumber].customerIDNumber) : printf("Invalid Customer Number\n" );
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
		tempEmployee.personalIDNumber = getPersonalIDNumber(numberOfCompanies);
		tempEmployee.numberOfPurchases = 0;
		checkCustomerInfo(tempEmployee) ? storeCustomerInfo(&company[numberOfCompanies].employees[*numEmployees], tempEmployee, numberOfCompanies) : false;
		keepEntering = continueEnteringClients();
	}
}

void appendEmployees(int companyCode)
{
	bool keepEntering = true;
	int * numEmployees = &company[companyCode / 1000 - 1].numberOfCustomers;
	while (keepEntering && company[companyCode / 1000 - 1].numberOfCustomers < 32)
	{
		clearScreen();
		EMPLOYEE tempEmployee;

		getInfo("Enter Customer Name", tempEmployee.customerName);
		tempEmployee.iDType = getIDType();
		tempEmployee.customerIDNumber = (companyCode / 1000 - 1 + 1) * 1000 + (*numEmployees + 1) * 10;
		tempEmployee.personalIDNumber = getPersonalIDNumber(companyCode / 1000 - 1);
		tempEmployee.numberOfPurchases = 0;
		checkCustomerInfo(tempEmployee) ? storeCustomerInfo(&company[companyCode / 1000 - 1].employees[*numEmployees], tempEmployee, companyCode / 1000 - 1) : false;
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
	if(numberOfCompanies != 16)
	{
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
	else
		printf("Maximim number of companies reached");
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
	if(fopen("companyData.dat", "rb"))
	{
		FILE * fp;
		fp = fopen("companyData.dat", "rb");
		while(!feof(fp))
		{
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

	sprintf(message, "Name:\t%s\n\nUserName:\t%s\n\nJob Type:\t%s\n\nBranch Number:\t%i\n\nIs this okay?", employee.eagleEmployeeName, employee.eagleUserName, jobType, employee.branchNumber);
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
	printf("Enter Branch Number\n");
	scanf("%i", &temp.branchNumber);
	temp.eagleEmployeeNumber = numberOfEagleEmployees + 1;
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
	fclose(fp);
}

void updatePricePerLitre()
{
	FILE *uPtr;
	float price;
	int i;

	uPtr=fopen("Priceperlitre.txt","w");
	puts("Enter price for 87, 90, diesel:\n");
	for(i=0;i<3;i++)
	{
		scanf("%f", &price);
		fprintf(uPtr, "%f\n",price);
	}
	fclose(uPtr);
}

bool dateExists()
{
	return fopen("date.txt", "r");
}

void getInitialDate()
{
	int year, month;
	do {
		printf("Enter the current year\n");
		scanf(" %i", &year);
	} while(year < 1);
	do {
		printf("Enter the month ( 1 - 12 )\n");
		scanf("%i", &month);
	} while(month > 12 || month < 1);
	FILE * fp;
	fp = fopen("date.txt", "w");
	fprintf(fp, "%i\n%i\n", month, year);
	fclose(fp);
}

int getDate()
{
	if(!dateExists())
	{
		getInitialDate();
	}
	FILE * fp;
	fp = fopen("date.txt", "r");
	int month, year;
	fscanf(fp, "%i\n%i\n", &month, &year);
	return (month * 10000) + year;
	fclose(fp);
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
    clearScreen();
    updatePricePerLitre();
    clearScreen();
		getInitialDate();
		clearScreen();
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

void updateCompanyInfo(int companyCode)
{
	companyCode = (companyCode / 1000) - 1;
	char options[][32] = {"New Company Name", "New Contact Name", "New Contact Number", "New Contact Email"};
	int toUpdate = displayArrowMenu("Choose the appropriate option", options, sizeof(options) / sizeof(options[0]));
	switch (toUpdate)
	{
		case 1:
			getInfo(options[toUpdate - 1], company[companyCode].companyName);
			break;
		case 2:
			getInfo(options[toUpdate - 1], company[companyCode].companyContactName);
			break;
		case 3:
			getInfo(options[toUpdate - 1], company[companyCode].companyContactTelephoneNumber);
			break;
		case 4:
			getInfo(options[toUpdate - 1], company[companyCode].companyContactPersonEmail);
			break;
	}
}

void updateCustomerInfoType(int companyCode, int customerIDNumber)
{
	char options[][32] = {"New Customer Name", "New Customer ID"};
	int toUpdate = displayArrowMenu("Chose the appropriate option", options, sizeof(options) / sizeof(options[0]));
	switch (toUpdate) {
		case 1:
			getInfo(options[toUpdate - 1], company[companyCode].employees[customerIDNumber].customerName);
			break;
		case 2:
			company[companyCode].employees[customerIDNumber].iDType = getIDType();
			break;
	}
}

void updateCustomerInfo(int companyCode)
{
	int x;
	companyCode = (companyCode / 1000) - 1;
	char options[company[companyCode].numberOfCustomers][32];
	for (x = 0; x < company[companyCode].numberOfCustomers; x++)	sprintf(options[x], "%i\t%i", company[companyCode].employees[x].customerIDNumber, company[companyCode].employees[x].personalIDNumber);
	int toUpdate = displayArrowMenu("Choose the customer to be updated", options, sizeof(options) / sizeof(options[0]));
	updateCustomerInfoType(companyCode, toUpdate - 1);
}

void updateInfo()
{
	char options[][32] = {"Company Info", "Customer Info"};
	int toUpdate = displayArrowMenu("Choose the type of field to update", options, sizeof(options) / sizeof(options[0]));
	int updateQuerry;
	printf("Enter companyCode\n");
	fflush(stdin);
	scanf("%i", &updateQuerry);
	if(updateQuerry % 1000 == 0 && (updateQuerry / 1000) <= numberOfCompanies && (updateQuerry / 1000) > 0)
		switch(toUpdate)
		{
			case 1:
				updateCompanyInfo(updateQuerry);
				break;
			case 2:
				updateCustomerInfo(updateQuerry);
		}
	else
		printf("Invalid company code\n");
		system("pause");
}

//UODATED PRICE PER LITR MOVED UP


//Print all purchases
void printAllPurchaseReceipts()
{
	if(fopen("purchaseData.dat", "rb")){
		PURCHASE temp;
		FILE * fp;
		fp = fopen("purchaseData.dat", "rb");
		while (!feof(fp)) {
			fread(&temp, sizeof(PURCHASE), 1, fp);
			receipt(&temp);
		}
		fclose(fp);
	}
}


void getCompanyTotals(float * companyTotals)
{
	PURCHASE temp;
	FILE * fp;
	fp = fopen("purchaseData.dat", "rb");
	int x;
	for (x = 0; x < numberOfCompanies; x++)
		*(companyTotals + x) = 0.0;
	while (!feof(fp))
	{
		fread(&temp, sizeof(PURCHASE), 1, fp);
		*(companyTotals + ((temp.companyCode / 1000) - 1)) += temp.costOfSale;
	}
	companyTotals[(temp.companyCode / 1000) - 1] -= temp.costOfSale;
	fclose(fp);
}

void printCompanyReport(float * companyTotals)
{
	int x;
	system("cls");
	printf("Company Code\tTotal Due\n\n");
	for(x = 0; x < numberOfCompanies; x++)
		printf("%i\t\t%.2f\n", (x + 1) * 1000, *(companyTotals + x));
}

void generateCompanyReport()
{
	float companyTotals[numberOfCompanies];
	getCompanyTotals(companyTotals);
	printCompanyReport(companyTotals);
	system("pause");
}

void printReceiptsAndSumForGasType(char * option, int typeOfGas) {
	FILE * fp;
	fp = fopen("purchaseData.dat", "rb");
	float sum = 0;
	PURCHASE temp;
	while(!feof(fp))
	{
		fread(&temp, sizeof(PURCHASE), 1, fp);
		if(temp.gasType == typeOfGas)
		{
			receipt(&temp);
			sum += temp.costOfSale;
		}
	}
	if(temp.gasType == typeOfGas)
		sum -= temp.gasType;
	printf("\n\nTotal sales for %s petrol: $%.2f\n", option, sum);
	fclose(fp);
	system("pause");
}

void generateGasTypeReport()
{
	char options[][32] = {"87", "90", "Diesel"};
	int typeOfGas = displayArrowMenu("Choose the type of gas to generate the report for", options, sizeof(options) / sizeof(options[0]));
	printReceiptsAndSumForGasType(options[typeOfGas - 1], typeOfGas);
}

void printReceiptsAndSumForCustomer(int personalID)
{
	FILE * fp;
	fp = fopen("purchaseData.dat", "r");
	float sum = 0.0;
	PURCHASE temp;
	while (!feof(fp))
	{
		fread(&temp, sizeof(PURCHASE), 1, fp);
		if(temp.customerIDNumber == personalID)
		{
			receipt(&temp);
			sum += temp.costOfSale;
		}
	}
	if(temp.customerIDNumber == personalID)
		sum -= temp.costOfSale;
	sum > 0.0 ? printf("\n\nTotal sales in petrol: $%.2f\n", sum) : printf("No valid sales records found\n");;
	system("pause");
	fclose(fp);
}

void generateCustomerPurchaseReport()
{
	puts("Enter the Customer's Personal ID number");
	int personalID;
	scanf("%i", &personalID);
	printReceiptsAndSumForCustomer(personalID);
}

void displayMonthlyReport()
{
	if(fopen("purchaseData.dat", "rb")){
		char options[][32] = {"Company Report", "Gas Type Report", "Client Report"};
		int reportType = displayArrowMenu("Choose the type of report to be generated", options, sizeof(options) / sizeof(options[0]));
		switch (reportType) {
			case 1:
				generateCompanyReport();
				break;
			case 2:
				generateGasTypeReport();
				break;
			case 3:
				generateCustomerPurchaseReport();
				break;
		}
	}
	else
	{
		printf("No purchases found\n");
		system("pause");
	}
}


void endMonth()
{
	displayArrowMenu("Should a Company Report be generated before ending the month?", yesNoOptions, sizeof(yesNoOptions) / sizeof(yesNoOptions[0])) == 1 ? generateCompanyReport() : false;
	int date = getDate();
	 date = date / 10000 < 12 ? date + 10000 : date - 109999;
	FILE * fp;
	fp = fopen("date.txt", "w");
	fprintf(fp, "%i\n%i\n", date / 10000, date % 10000);
	fclose(fp);
	fp = fopen("purchaseData.dat", "w");
	fclose(fp);
}

void getCompanyToAppend()
{
	int companyCode;
	clearScreen();
	printf("Enter companyCode\n");
	scanf(" %i", &companyCode);
	if(companyCode / 1000 - 1 < numberOfCompanies && (companyCode / 1000) * 1000 == companyCode)
		appendEmployees(companyCode);
	else
	{
		printf("Company Code not valid\n");
		system("pause");
	}
}

void managerOptions()
{
	char options[][32] = {"Print all customer data", "Add new Eagle Account", "Update customer/company info", "Update gas prices", "Print all purchase receipts", "End Month", "Add new employees", "Exit"};
	int choice = displayArrowMenu("Manager Menu\nChoose an option", options, sizeof(options) / sizeof(options[0]));
	switch (choice) {
		case 1:
			printAllData();
			break;
		case 2:
			createNewEagleAccount();
			break;
		case 3:
			updateInfo();
			break;
		case 4:
			updatePricePerLitre();
			break;
		case 5:
			printAllPurchaseReceipts();
			break;
		case 6:
			endMonth();
			break;
		case 7:
			getCompanyToAppend();
	}
}

void fullMenuFunctions(int menuOption)
{
	switch (menuOption)
	{
		case 1:
			pumpGas();
			break;
		case 2:
			fileWrite();
			writeEagleEmployeeData();
			break;
		case 3:
			searchInfo();
			break;
		case 4:
			displayMonthlyReport();
			break;
		case 5:
			addCompany();
			break;
		case 6:
			managerOptions();
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
	int attempts = 0;
	while(attempts < 3)
	{
		printf("Enter Your UserName:");
		do
			gets(credentials[0]);
		while(strcmp(credentials[0], "") == 0);
		printf("Enter Your Password:");
		do
			gets(credentials[1]);
		while (strcmp(credentials[1], "") == 0);
		int workingAccount = searchAccount(credentials);
		system("cls");
		if(workingAccount != -1)
		{
			activeAccount = workingAccount;
			return true;
		}
		attempts++;
		printf("Failed login attempt (%i)\n", attempts);
	}
	return false;
}

void displayManagerMenu()
{
	int menuOption = 0;
	char * message = "Choose an option";
	while (menuOption != 2)
	{
		char options[][32] = { "Pump Gas", "Save and Exit", "Search Information", "Generate Report", "Register Company", "Manager Options"};
		menuOption = displayArrowMenu(message, options, sizeof(options) / sizeof(options[0]));
		clearScreen();
		fullMenuFunctions(menuOption);
	}
}

void displayCashierMenu()
{
	int menuOption = 1;
	char * message = "Choose an option";
	while (menuOption != 2)
	{
		char options[][32] = { "Pump Gas", "Save and Exit", "Search Information", "Generate Report"};
		menuOption = displayArrowMenu(message, options, sizeof(options) / sizeof(options[0]));
		clearScreen();
		fullMenuFunctions(menuOption);
	}
}

void displayPumpAttendantMenu()
{
	int menuOption = 1;
	char * message = "Choose an option";
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
	srand(time(NULL));
	getEagleEmployeeData();
	fileRead();
	if(login())
	{
		displayEmployeeMenu();
	} else {
		puts("Incorrect login information has been entered more than three times.\nThe system will now be closed.");
	}
}
