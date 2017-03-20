#define employeesPerCompany 32

int numberOfCompanies = 0;
int totalNumberOfCompanies = 32;

typedef struct employee{
  char customerName[32], iDType;
  int companyCode, customerIDNumber;
} EMPLOYEE;

typedef struct company{
  char companyName[32], companyContactName[32], companyContactPersonEmail[32];
  int companyCode, companyContactTelephoneNumber, numberOfCustomers;
  EMPLOYEE employees[employeesPerCompany];
} COMPANY;

typedef struct stationEmployee{
  char employeeUsername[64], employeePassword[64];
} STATIONEMPLOYEE;
