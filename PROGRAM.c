#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_CUSTOMERS 100
#define MAX_NAME_LEN 50
#define MAX_EMAIL_LEN 50
#define MAX_MOBILE_LEN 15
#define MAX_ADDRESS_LEN 100
#define MAX_GENDER_LEN 10
#define MAX_ACCOUNT_TYPE_LEN 20
#define MAX_AADHAR_LEN 20
#define MAX_KYC_DOC_LEN 50
#define MAX_CARD_NUMBER_LEN 20
typedef struct
{
    char username[10];
    char password[8];
} employees;

employees employee[3];
int employeeCount = 0;

typedef struct
{
    int accountNumber;
    char name[MAX_NAME_LEN];
    char email[MAX_EMAIL_LEN];
    char mobile[MAX_MOBILE_LEN];
    char address[MAX_ADDRESS_LEN];
    int age;
    char gender[MAX_GENDER_LEN];
    char accountType[MAX_ACCOUNT_TYPE_LEN];
    char aadhar[MAX_AADHAR_LEN];
    int isAadharLinked;
    int isKYCCompleted;
    char kycDocument[MAX_KYC_DOC_LEN];
    float balance;
    char creditCardNumber[MAX_CARD_NUMBER_LEN];
    char debitCardNumber[MAX_CARD_NUMBER_LEN];
} Customer;

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;
int user=0;

const char *EMPLOYEE_FILE = "employee.txt";
const char *CUSTOMER_FILE;
const char *TRANSACTION_FILE = "transactions.log";

void clearInputBuffer();
int isValidEmail(const char *email);
int isValidMobile(const char *mobile);
void loadEmployee();
void loadCustomers();
void saveCustomers();
void logTransaction(int accountNumber, const char *action, float amount, int user);
void createAccount();
void displayAccount();
void depositMoney();
void withdrawMoney();
void showTransactionHistory();
void linkAadhar();
void completeKYC();
void deleteAccount();
void showMenu();
void program();

void login()
{
    loadEmployee();
    char username1[10];
    char password1[8];
    printf("Enter your username: ");
    scanf("%s", username1);
    printf("Enter your password (8 chars): ");
    scanf("%s", password1);
    for (int i = 0; i < employeeCount; i++)
    {
        if (strcmp(employee[i].username, username1) == 0 && strcmp(employee[i].password, password1) == 0)
        {
            switch (i)
            {
            case 0:
                CUSTOMER_FILE = "customers0.dat";
                user=0;
                program();
                break;
            case 1:
                CUSTOMER_FILE = "customers1.dat";
                user=1;
                program();
                break;
            case 2:
                CUSTOMER_FILE = "customers2.dat";
                user=2;
                program();
                break;
            default:
                printf("Invalid employee index\n");
                return;
            }
            loadCustomers(); // Load customers after setting the file
           
            return;
        }
    }
    printf("Entered details are incorrect\n");
}
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return at && dot && at < dot;
}

int isValidMobile(const char *mobile)
{
    if (strlen(mobile) != 10)
        return 0;
    for (int i = 0; i < 10; i++)
        if (!isdigit(mobile[i]))
            return 0;
    return 1;
}

void loadCustomers()
{
    FILE *file = fopen(CUSTOMER_FILE, "rb");
    if (file)
    {
        fread(&customerCount, sizeof(int), 1, file);
        fread(customers, sizeof(Customer), customerCount, file);
        fclose(file);
    }
}

void loadEmployee()
{
    FILE *file = fopen("employee.txt", "r");
    if (!file)
    {
        // File doesn't exist yet, probably first run
        return;
    }

    employeeCount = 0;
    while (fscanf(file, "%s %s\n",
                  employee[employeeCount].username,
                  employee[employeeCount].password) != EOF)
    {
        employeeCount++;
    }

    fclose(file);
}

void saveCustomers()
{
    FILE *file = fopen(CUSTOMER_FILE, "wb");
    if (file)
    {
        fwrite(&customerCount, sizeof(int), 1, file);
        fwrite(customers, sizeof(Customer), customerCount, file);
        fclose(file);
    }
}

void logTransaction(int accountNumber, const char *action, float amount,int user)
{
    FILE *file = fopen(TRANSACTION_FILE, "a");
    if (file)
    {
        fprintf(file, "User: %d | Account: %d | Action: %s | Amount: %.2f\n", user, accountNumber, action, amount);
        fclose(file);
    }
}

void showMenu()
{
    printf("\n====== ADITYA BANK OF INDIA (ABI) ======\n");
    printf("           CUSTOMER PORTAL\n");
    printf("1. Create a new account\n");
    printf("2. View account details\n");
    printf("3. Deposit money\n");
    printf("4. Withdraw money\n");
    printf("5. View transaction history\n");
    printf("6. Link Aadhar\n");
    printf("7. Complete KYC\n");
    printf("8. Delete account\n");
    printf("9. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

void createAccount()
{
    if (customerCount >= MAX_CUSTOMERS)
    {
        printf("Maximum customer limit reached!\n");
        return;
    }

    Customer newCustomer;
    newCustomer.accountNumber = customerCount + 1;

    printf("Enter name: ");
    fgets(newCustomer.name, sizeof(newCustomer.name), stdin);
    strtok(newCustomer.name, "\n");

    do
    {
        printf("Enter email: ");
        fgets(newCustomer.email, sizeof(newCustomer.email), stdin);
        strtok(newCustomer.email, "\n");
        if (!isValidEmail(newCustomer.email))
            printf("Invalid email format. Please try again.\n");
    } while (!isValidEmail(newCustomer.email));

    do
    {
        printf("Enter mobile number (10 digits): ");
        fgets(newCustomer.mobile, sizeof(newCustomer.mobile), stdin);
        strtok(newCustomer.mobile, "\n");
        if (!isValidMobile(newCustomer.mobile))
            printf("Invalid mobile number. Please try again.\n");
    } while (!isValidMobile(newCustomer.mobile));

    printf("Enter address: ");
    fgets(newCustomer.address, sizeof(newCustomer.address), stdin);
    strtok(newCustomer.address, "\n");

    do
    {
        printf("Enter age (18+): ");
        scanf("%d", &newCustomer.age);
        clearInputBuffer();
        if (newCustomer.age < 18)
            printf("Age must be 18 or older. Please try again.\n");
    } while (newCustomer.age < 18);

    printf("Enter gender: ");
    fgets(newCustomer.gender, sizeof(newCustomer.gender), stdin);
    strtok(newCustomer.gender, "\n");

    printf("Enter account type (Savings/Current): ");
    fgets(newCustomer.accountType, sizeof(newCustomer.accountType), stdin);
    strtok(newCustomer.accountType, "\n");

    newCustomer.balance = 0.0;
    newCustomer.isAadharLinked = 0;
    newCustomer.isKYCCompleted = 0;

    customers[customerCount++] = newCustomer;

    saveCustomers();

    printf("Account created successfully! Your account number is %d.\n", newCustomer.accountNumber);
}

void displayAccount()
{
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    clearInputBuffer();

    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            printf("\n--- Account Details ---\n");
            printf("Account Number: %d\n", customers[i].accountNumber);
            printf("Name: %s\n", customers[i].name);
            printf("Email: %s\n", customers[i].email);
            printf("Mobile: %s\n", customers[i].mobile);
            printf("Address: %s\n", customers[i].address);
            printf("Age: %d\n", customers[i].age);
            printf("Gender: %s\n", customers[i].gender);
            printf("Account Type: %s\n", customers[i].accountType);
            printf("Balance: %.2f\n", customers[i].balance);
            if (customers[i].isAadharLinked)
                printf("Aadhar Linked: %s\n", customers[i].aadhar);
            if (customers[i].isKYCCompleted)
                printf("KYC Completed: Yes\n");
            else
                printf("KYC Completed: No\n");
        }
        else
        {
            printf("Account not found!\n");
        }
    }
}

void depositMoney()
{
    int accountNumber;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    clearInputBuffer();

    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            clearInputBuffer();

            if (amount <= 0)
            {
                printf("Invalid amount! Must be greater than 0.\n");
                return;
            }

            customers[i].balance += amount;
            saveCustomers();
            logTransaction(accountNumber, "Deposit", amount, user);

            printf("Deposit successful! New balance: %.2f\n", customers[i].balance);
            return;
        }
        else
        {
            printf("Account not found!\n");
        }
    }
}

void withdrawMoney()
{
    int accountNumber;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    clearInputBuffer();

    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            clearInputBuffer();

            if (amount <= 0 || amount > customers[i].balance)
            {
                printf("Invalid amount! Must be within available balance.\n");
                return;
            }

            customers[i].balance -= amount;
            saveCustomers();
            logTransaction(accountNumber, "Withdrawal", amount, user);

            printf("Withdrawal successful! New balance: %.2f\n", customers[i].balance);
            return;
        }
        else
        {
            printf("Account not found!\n");
        }
    }
}

void showTransactionHistory()
{
    FILE *file = fopen(TRANSACTION_FILE, "r");
    if (file)
    {
        char line[256];
        printf("\n--- Transaction History ---\n");
        while (fgets(line, sizeof(line), file))
        {
            printf("%s", line);
        }
        fclose(file);
    }
    else
    {
        printf("No transaction history found.\n");
    }
}

void linkAadhar()
{
    int accountNumber;
    char aadhar[MAX_AADHAR_LEN];

    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    clearInputBuffer();

    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            if (customers[i].isAadharLinked)
            {
                printf("Aadhar is already linked.\n");
                return;
            }

            printf("Enter Aadhar number: ");
            fgets(aadhar, sizeof(aadhar), stdin);
            strtok(aadhar, "\n");

            strcpy(customers[i].aadhar, aadhar);
            customers[i].isAadharLinked = 1;
            saveCustomers();

            printf("Aadhar linked successfully!\n");
            return;
        }
        else
        {
            printf("Account not found!\n");
        }
    }
}

void completeKYC()
{
    int accountNumber;
    char kycID[MAX_KYC_DOC_LEN];
    int kycOption;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            printf("Choose KYC Document Type:\n");
            printf("1. Passport\n");
            printf("2. Voter's Identity Card\n");
            printf("3. Driving Licence\n");
            printf("4. Aadhaar Letter/Card\n");
            printf("5. NREGA Card\n");
            printf("Enter your choice: ");
            scanf("%d", &kycOption);

            switch (kycOption)
            {
            case 1:
                strcpy(kycID, "Passport");
                break;
            case 2:
                strcpy(kycID, "Voter's Identity Card");
                break;
            case 3:
                strcpy(kycID, "Driving Licence");
                break;
            case 4:
                strcpy(kycID, "Aadhaar Letter/Card");
                break;
            case 5:
                strcpy(kycID, "NREGA Card");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                return;
            }

            strcpy(customers[i].kycDocument, kycID);
            customers[i].isKYCCompleted = 1;

            saveCustomers();

            printf("KYC completed successfully using %s!\n", kycID);
            return;
        }
        else
        {
            printf("Account not found!\n");
        }
    }
}

void deleteAccount()
{
    int accountNumber;
    printf("Enter account number to delete: ");
    scanf("%d", &accountNumber);
    clearInputBuffer();

    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {

            for (int j = i; j < customerCount - 1; j++)
            {
                customers[j] = customers[j + 1];
            }
            customerCount--;
            saveCustomers();

            printf("Account deleted successfully!\n");
            return;
        }
        else
        {
            printf("Account not found!\n");
        }
    }
}
void program(){
    int choice;
    do
    {
        showMenu();
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            displayAccount();
            break;
        case 3:
            depositMoney();
            break;
        case 4:
            withdrawMoney();
            break;
        case 5:
            showTransactionHistory();
            break;
        case 6:
            linkAadhar();
            break;
        case 7:
            completeKYC();
            break;
        case 8:
            deleteAccount();
            break;

        case 9:
            printf("Exiting program. Thank you!\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);

    saveCustomers();
}

int main()
{
  
    login();
    
    return 0;
}
