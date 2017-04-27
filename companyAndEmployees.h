#define employeesPerCompany 32

int numberOfEagleEmployees = 0;
int numberOfCompanies = 0;

typedef enum jobType {MANAGER = 1, CASHIER = 2, PUMP_ATTENDANT = 3} eagleJobType;

typedef struct employee{
  char customerName[32], iDType;
  int customerIDNumber, numberOfPurchases, personalIDNumber;
} EMPLOYEE;

typedef struct company{
  char companyName[32], companyContactTelephoneNumber[32], companyContactName[32], companyContactPersonEmail[32];
  int companyCode, numberOfCustomers;
  EMPLOYEE employees[employeesPerCompany];
} COMPANY;


//Job Numbers,
typedef struct eagleEmployee{
  int eagleEmployeeNumber, branchNumber;
  eagleJobType jobType;
  char eagleEmployeeName[32], eagleUserName[32], eaglePassword[32];
} EAGLEEMPLOYEE;

typedef struct purchase{
  int saleIDNumber, stationNumber, companyCode, customerIDNumber;
  int gasType, pumpNumber, eightDigitSaleDate, employeeID;
  float litresOfPetrol, costPerLitre, costOfSale;
} PURCHASE;
