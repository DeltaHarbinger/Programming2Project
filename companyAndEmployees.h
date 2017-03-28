#define employeesPerCompany 32

int numberOfCompanies = 0;
int totalNumberOfCompanies = 32;

typedef struct employee{
  char customerName[32], iDType;
  int customerIDNumber;
} EMPLOYEE;

typedef struct company{
  char companyName[32], companyContactTelephoneNumber[32], companyContactName[32], companyContactPersonEmail[32];
  int companyCode, numberOfCustomers;
  EMPLOYEE employees[employeesPerCompany];
} COMPANY;


//Job Numbers,
typedef struct eagleEmployee{
  int eagleEmployeeNumber, eagleJobNumber;
  char eagleEmployeeName[32], eagleUserName[32], eaglePassword[32];
} EAGLEEMPLOYEE;

typedef struct purchase{
  int saleIDNumber, stationNumber, companyCode, customerIDNumber;
  int gasType, pumpNumber, eightDigitSaleDate, employeeID;
  float gallonsOfPetrol, costPerGallon, costOfSale;
} PURCHASE;
