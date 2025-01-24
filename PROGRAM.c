#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CUSTOMERS 100

typedef struct
{
    int accountNumber;
    char name[50];
    char email[50];
    char mobile[15];
    char address[100];
    int age;
    char gender[10];
    char accountType[20];
    float balance;
} Customer;

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

void createAccount();
void displayAccount();
void depositMoney();
void withdrawMoney();

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
    scanf("%s", newCustomer.name);
    printf("Enter email: ");
    scanf("%s", newCustomer.email);
    printf("Enter mobile number: ");
    scanf("%s", newCustomer.mobile);
    printf("Enter address: ");
    scanf(" %s", newCustomer.address);
    printf("Enter age: ");
    scanf("%d", &newCustomer.age);
    printf("Enter gender: ");
    scanf("%s", newCustomer.gender);
    printf("Enter account type (Savings/Current): ");
    scanf("%s", newCustomer.accountType);
    newCustomer.balance = 0.0;

    customers[customerCount++] = newCustomer;

    printf("Account created successfully! Your account number is %d.\n", newCustomer.accountNumber);
}

void displayAccount()
{
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            printf("\nAccount Number: %d\n", customers[i].accountNumber);
            printf("Name: %s\n", customers[i].name);
            printf("Email: %s\n", customers[i].email);
            printf("Mobile: %s\n", customers[i].mobile);
            printf("Address: %s\n", customers[i].address);
            printf("Age: %d\n", customers[i].age);
            printf("Gender: %s\n", customers[i].gender);
            printf("Account Type: %s\n", customers[i].accountType);
            printf("Balance: %.2f\n", customers[i].balance);
            return;
        }
    }

    printf("Account not found!\n");
}

void depositMoney()
{
    int accountNumber;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid amount!\n");
                return;
            }

            customers[i].balance += amount;
            printf("Amount deposited successfully! New balance: %.2f\n", customers[i].balance);
            return;
        }
    }

    printf("Account not found!\n");
}

void withdrawMoney()
{
    int accountNumber;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].accountNumber == accountNumber)
        {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid amount!\n");
                return;
            }

            if (amount > customers[i].balance)
            {
                printf("Insufficient balance!\n");
                return;
            }

            customers[i].balance -= amount;
            printf("Amount withdrawn successfully! New balance: %.2f\n", customers[i].balance);
            return;
        }
    }

    printf("Account not found!\n");
}

void main()
{
    int choice, a;
    do
    {
        printf("ADITYA BANK OF INDIA (ABI)\n");
        printf("     CUSTOMER PORTAL      \n\n\n");
        printf("1. To create new account and display of bank account\n");
        printf("2. To deposit and withdraw money from bank account\n");
        printf("3. To link aadhar to existing bank account and display of aadhar linked accounts\n");
        printf("4. Updation of mobile,address and  email of existing bank account\n");
        printf("5. New credit card \n");
        printf("6. New debit card \n");
        printf("7. Delete bank account \n");
        printf("8. exit\n\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            do
            {
                printf("1. Create Account\n");
                printf("2. View Account Details\n");
                printf("3. Exit\n");
                printf("\nEnter your choice: ");
                scanf("%d", &a);
                switch (a)
                {
                case 1:
                    createAccount();
                    break;
                case 2:
                    displayAccount();
                    break;
                case 3:
                    printf("Exiting. Thank you!\n");
                    break;
                }
            } while (a != 3);

            break;
        case 2:
            do
            {
                printf("1. Deposit Money\n");
                printf("2. Withdraw Money \n");
                printf("3. Exit\n");
                printf("\nEnter your choice: ");
                scanf("%d", &a);
                switch (a)
                {
                case 1:
                    depositMoney();
                    break;
                case 2:
                    withdrawMoney();

                    break;
                case 3:
                    printf("Exiting. Thank you!\n");
                    break;
                }
            } while (a != 3);

            break;
            // case 3:

            //     break;
            // case 4:

            //     break;
            // case 5:

            // case 6:
            // case 7:

        case 8:
            printf("Exiting program. Thank you!\n");

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);
}
