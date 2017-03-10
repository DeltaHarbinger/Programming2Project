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

void printMenu(){
    printf("Select Menu Option\n");
    printf("1.\tPump Gas\n");
    printf("2.\tEmployee Log In\n");
    printf("3.\tRegister Company\n");
    printf("4.\tExit\n");
}

int * findCustomer(int companyCodeSearch, int customerIDNumberSearch){
    int x = 0, y = 0;
    int customerInfo[2] = {-1, -1};
    bool foundCustomer = false;
    while(x < 10 && !foundCustomer){
        if(companyCode[x] == companyCodeSearch){
            printf("Found Company Code.\n");
            while(y < 10 && !foundCustomer){
                if(customerIDNumberSearch == customerPersonalIDNumber[x][y]){
                    customerInfo[0] = x;
                    customerInfo[1] = y;
                }
                y++;
            }
        }
        x++;
    }
    return customerInfo;

}

void getCustomerInfo(int arr[2]){
    int customerInfoSearch[2];
    printf("Enter the Company Code:\n");
    scanf(" %i", arr);
    printf("Enter Customer Identification Number\n");
    scanf(" %i", (arr + 1));
}

double getAmountToPump(){
    double amountToPump;
    printf("Enter the amount of the gas to pump (In gallons)\n");
    scanf(" %f", &amountToPump);
    return amountToPump;
}

//Option 1
void pumpGas(){
    int customerInfo[2];
    getCustomerInfo(customerInfo);
    double amountToPump = getAmountToPump();
}
////////////////////////////////////
//Option 2
void employeeLogIn(){

}

char * getCompanyInfo(char * message){
    char companyInfo[30];
    printf("%s", message);
    scanf(" %s", companyInfo);
    return companyInfo;
}

void storeCompanyInfo(char companyInfo[3][30]){
    strcpy(companyName[numberOfCompanies], companyInfo[0]);
    strcpy(companyContactName[numberOfCompanies], companyInfo[1]);
    strcpy(companyContactPersonEmail[numberOfCompanies], companyInfo[2]);
}

void incramentNumberOfCompanies(){
    numberOfCompanies++;
}

//Option 3
void AddCompany(){
    char isCorrect = 'n', reEnter = 'y';
    while(isCorrect == 'n' && reEnter == 'y'){
        char companyInfo[3][30] = {"Company Name\n", "Company Contact Name\n", "Company Contact Email\n"};
        int x;
        for(x = 0; x < 3; x++)
            strcpy(companyInfo[x], getCompanyInfo(companyInfo[x]));


        printf("%s\n%s\n%s\n\nIs this correct (y/n)", companyInfo[0], companyInfo[1], companyInfo[2]);
        isCorrect = getch();
        while(isCorrect != 'y' && isCorrect != 'n'){
            printf("\nPlease enter y or n");
            isCorrect = getch();
        }
        if(isCorrect == 'n'){
            printf("\nWould you like to enter the data again?\n");
            reEnter = getch();
            while(reEnter != 'y' && reEnter != 'n'){
                printf("\nPlease enter y or n\n");
                reEnter = getch();
            }
        } else {
            storeCompanyInfo(companyInfo);
            companyCode[numberOfCompanies] = (numberOfCompanies + 1) * 1000;
            incramentNumberOfCompanies();

            char continueEnteringClients = 'y';
            x = 0;
            while(continueEnteringClients == 'y' && x < 10){
                system("cls");
                char tempcustomerName[30];
                char iDType;
                printf("Enter the Customer's Name\n");
                scanf(" %s", tempcustomerName);
                printf("\nEnter the type of ID the customer will use (P - Passport, N - National ID, D - Driver's License)\n");
                iDType = getch();
                iDType = toupper(iDType);
                printf("\n%s\n%c\nIs this correct? (y/n)\n", tempcustomerName, iDType);
                char correct = getch();
                while(correct != 'y' && correct != 'n'){
                    printf("\nPlease enter a valid option\n\n%s\n%c\nIs this correct? (y/n)\n", tempcustomerName, iDType);
                    correct = getch();
                }
                if(correct == 'y'){
                    strcpy(customerName[numberOfCompanies - 1][x], tempcustomerName);
                    customerIDNumber[numberOfCompanies - 1][x] = companyCode[numberOfCompanies - 1] + ((x + 1) * 60);
                    customerTypeOfID[numberOfCompanies - 1][x] = iDType;
                    x++;
                    printf("%s\n", customerName[numberOfCompanies - 1][x - 1]);
                    printf("Would you like to continue entering clients? (y/n)");
                    continueEnteringClients = getch();
                    while(continueEnteringClients != 'y' && continueEnteringClients != 'n'){
                        printf("Would you like to continue entering clients? (y/n)");
                        continueEnteringClients = getch();
                    }
                } else {
                    printf("Would you like to re-enter the information? (y/n)\n");
                    reEnter = getch();
                    while(reEnter != 'y' && reEnter != 'n'){
                        printf("Please enter a valid option\nWould you like to re-enter the information?(y/n)\n");
                        reEnter = getch();
                    }
                    if(reEnter != 'y'){
                        printf("\nContinue entering clients?\n");
                        continueEnteringClients = getch();
                        while(continueEnteringClients != 'y' && continueEnteringClients != 'n'){
                            printf("Please enter a valid response.\nStop entering clients?\n");
                            continueEnteringClients = getch();
                        }
                    }
                }
            }
            int z;
            system("cls");
            for(z = 0; z < x; z++)
                printf("\n%s\t%c", customerName[numberOfCompanies - 1][z], customerTypeOfID[numberOfCompanies - 1][z]);
            printf("\nThese employees have been registered\n");
            system("pause");
        }
    }
    system("cls");

}

void menuFunctions(int menuOption){
    switch(menuOption){
    case 1:
        pumpGas();
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

int getMenuOption(char menu[][30], int s) {
	int position = 0;
	char test = 0;
	while (test != 8 && test != 13)
	{
		system("cls");
		int x;
		for (x = 0; x < s; x++) {
			printf("%s%s%s\n", position == x ? "-->" : "  ", menu[x], position == x ? "<--" : "  ");
		}
		test = _getch();
		if (test == -32) {
			test = _getch();
		}
		(test == 72 && position != 0) ? position-- : NULL;
		(test == 80 && position != s - 1) ? position++ : NULL;
	}
	return  position + 1;
}

int main()
{
    int menuOption;
    while(menuOption != 4){
        char options[][30] = {"Pump Gas", "Employee Login", "Register Company", "Exit", "FIFTH"};
        menuOption = getMenuOption(options, sizeof(options) / sizeof(options[0]));
        system("cls");
        menuFunctions(menuOption);
    }
    return 0;
}
