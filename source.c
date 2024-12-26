#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables (not ideal for bigger projects, but we'll keep them as is):
char email[50], fname[50], lname[50], password[50], bank[50], secretq[50], answer[50];
int balance;

// Forward declarations (helps to avoid implicit-function declarations)
void signup();
int log_in();
int menu();
void change_user_information(int user);
int shop_section();
void complete(int price);
void logout();
void delete_account();

int log_in()
{
    int flag = 0, user = 0, d_balance;
    char em[100], pw[100], ans[100];
    char d_email[50], d_fname[50], d_lname[50], d_password[50], d_bank[50];
    char d_secretq[50], d_answer[50];
    char temp;

    FILE *file, *ptr;
    file = fopen("database.txt", "r");
    ptr = fopen("output.txt", "w");
    if (!file || !ptr)
    {
        printf("Error opening file!\n");
        if (file) fclose(file);
        if (ptr)  fclose(ptr);
        return -1;
    }

    printf("Welcome to Amazon!\n");
    printf("Enter your Email: ");
    scanf("%s", em);
    printf("Enter your Password: ");
    scanf("%s", pw);

    // Search for the user in database
    while (fscanf(file, "%s %s %s %s %s %d %s %s",
                  email, fname, lname, password,
                  bank, &balance, secretq, answer) == 8)
    {
        if (strcmp(em, email) == 0)
        {
            flag = 1;
            break;
        }
        user++;
    }

    // If user is found (flag=1), check password
    if (flag == 1)
    {
        if (strcmp(pw, password) == 0)
        {
            printf("You successfully logged in to your account!\n");

            // Copy entire database to output.txt
            rewind(file);
            while (fscanf(file, "%s %s %s %s %s %d %s %s",
                          d_email, d_fname, d_lname, d_password,
                          d_bank, &d_balance, d_secretq, d_answer) == 8)
            {
                fprintf(ptr, "%s %s %s %s %s %d %s %s\n",
                        d_email, d_fname, d_lname, d_password,
                        d_bank, d_balance, d_secretq, d_answer);
            }
        }
        else
        {
            // Try the “swapped password” approach
            int match_count = 0;
            size_t len = strlen(pw);
            for (size_t i = 0; i < len - 1; i++)
            {
                // Swap adjacent chars
                temp = pw[i];
                pw[i] = pw[i + 1];
                pw[i + 1] = temp;

                if (strcmp(pw, password) == 0)
                {
                    match_count = 1;
                }

                // Swap back
                temp = pw[i];
                pw[i] = pw[i + 1];
                pw[i + 1] = temp;
            }

            if (match_count == 1)
            {
                // Must answer secret question
                printf("Wrong password, please enter the answer to the secret question: %s\n", secretq);
                scanf("%s", ans);
                if (strcmp(ans, answer) == 0)
                {
                    printf("You successfully logged in to your account!\n");
                    rewind(file);
                    while (fscanf(file, "%s %s %s %s %s %d %s %s",
                                  d_email, d_fname, d_lname, d_password,
                                  d_bank, &d_balance, d_secretq, d_answer) == 8)
                    {
                        fprintf(ptr, "%s %s %s %s %s %d %s %s\n",
                                d_email, d_fname, d_lname, d_password,
                                d_bank, d_balance, d_secretq, d_answer);
                    }
                }
                else
                {
                    printf("This account does not exist.\n");
                    fclose(file);
                    fclose(ptr);
                    signup();
                    return user;
                }
            }
            else
            {
                printf("This account does not exist.\n");
                fclose(file);
                fclose(ptr);
                signup();
                return user;
            }
        }
    }
    else
    {
        printf("This account does not exist.\n");
        fclose(file);
        fclose(ptr);
        signup();
        return user;
    }

    fclose(file);
    fclose(ptr);
    return user;
}

void signup()
{
    char d_email[50], d_fname[50], d_lname[50], d_password[50];
    char d_secretq[50], d_answer[50], d_bank[50];
    int d_balance;

    FILE *ptr, *fptr;
    ptr = fopen("database.txt", "r");
    fptr = fopen("output.txt", "w+");

    if (!ptr || !fptr)
    {
        printf("Error opening file!\n");
        if (ptr)  fclose(ptr);
        if (fptr) fclose(fptr);
        return;
    }

    // Copy all existing records from "database.txt" -> "output.txt"
    while (fscanf(ptr, "%s %s %s %s %s %d %s %s",
                  d_email, d_fname, d_lname, d_password,
                  d_bank, &d_balance, d_secretq, d_answer) == 8)
    {
        fprintf(fptr, "%s %s %s %s %s %d %s %s\n",
                d_email, d_fname, d_lname, d_password,
                d_bank, d_balance, d_secretq, d_answer);
    }

    printf("Enter your email: ");
    scanf("%s", email);

    // Check for existing email
    int found_duplicate = 1;
    while (found_duplicate)
    {
        found_duplicate = 0;
        rewind(fptr);
        while (fscanf(fptr, "%s %s %s %s %s %d %s %s",
                      d_email, d_fname, d_lname, d_password,
                      d_bank, &d_balance, d_secretq, d_answer) == 8)
        {
            if (strcmp(email, d_email) == 0)
            {
                printf("This email already exists, enter a different email: ");
                scanf("%s", email);
                found_duplicate = 1;
                break;
            }
        }
    }

    printf("Enter your first name: ");
    scanf("%s", fname);
    printf("Enter your last name: ");
    scanf("%s", lname);
    printf("Enter your password: ");
    scanf("%s", password);
    printf("Enter your bank account number: ");
    scanf("%s", bank);

    // Check for existing bank account
    found_duplicate = 1;
    while (found_duplicate)
    {
        found_duplicate = 0;
        rewind(fptr);
        while (fscanf(fptr, "%s %s %s %s %s %d %s %s",
                      d_email, d_fname, d_lname, d_password,
                      d_bank, &d_balance, d_secretq, d_answer) == 8)
        {
            if (strcmp(bank, d_bank) == 0)
            {
                printf("This bank account number already exists, enter a different bank account number: ");
                scanf("%s", bank);
                found_duplicate = 1;
                break;
            }
        }
    }

    printf("Enter your balance: ");
    scanf("%d", &balance);
    printf("Enter your secret question: ");
    scanf("%s", secretq);
    printf("Enter the answer to your secret question: ");
    scanf("%s", answer);

    // Append new user to output.txt
    fprintf(fptr, "%s %s %s %s %s %d %s %s\n",
            email, fname, lname, password,
            bank, balance, secretq, answer);

    fclose(fptr);
    fclose(ptr);
}

int menu()
{
    int result;
    printf("\n\t--- Welcome to the Menu ---\n");
    printf("Where would you like to go?\n");
    printf("1- Change account information\n");
    printf("2- Shop\n");
    printf("3- Logout\n");
    printf("4- Delete account\n");
    printf("Enter your choice: ");
    scanf(" %d", &result);
    return result;
}

void change_user_information(int user)
{
    char pw[50];
    int x;

    printf("Please re-enter your password: ");
    scanf("%s", pw);

    // Keep prompting if wrong
    while (strcmp(pw, password) != 0)
    {
        printf("You entered the wrong password, try again: ");
        scanf("%s", pw);
    }

    printf("What information would you like to change?\n");
    printf("1- First name and last name\n");
    printf("2- Email\n");
    printf("3- Password\n");
    printf("4- Bank account number\n");
    printf("Enter choice: ");
    scanf("%d", &x);

    switch (x)
    {
    case 1:
        printf("Enter your new first name and last name: ");
        scanf("%s %s", fname, lname);
        break;
    case 2:
        printf("Enter your new email: ");
        scanf("%s", email);
        break;
    case 3:
        printf("Enter your new password: ");
        scanf("%s", password);
        break;
    case 4:
        printf("Enter your new bank account number: ");
        scanf("%s", bank);
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}

int shop_section()
{
    char response[20];
    int product;
    int qb = 0, qs = 0, qw = 0, qd = 0, ql = 0;
    int price = 0;

    printf("\n\t--- Welcome to the Shop Section ---\n");
    do
    {
        printf("\nPlease choose a product number:\n");
        printf("1- Book (200 MAD)\n");
        printf("2- Skin Care (700 MAD)\n");
        printf("3- Watch (1000 MAD)\n");
        printf("4- Desk (4000 MAD)\n");
        printf("5- Laptop (6000 MAD)\n");
        scanf("%d", &product);

        switch (product)
        {
        case 1:
            printf("Please select quantity: ");
            scanf("%d", &qb);
            break;
        case 2:
            printf("Please select quantity: ");
            scanf("%d", &qs);
            break;
        case 3:
            printf("Please select quantity: ");
            scanf("%d", &qw);
            break;
        case 4:
            printf("Please select quantity: ");
            scanf("%d", &qd);
            break;
        case 5:
            printf("Please select quantity: ");
            scanf("%d", &ql);
            break;
        default:
            printf("Invalid product choice.\n");
            break;
        }

        printf("Do you wish to continue shopping? (yes/no): ");
        scanf("%s", response);

    } while (strcmp(response, "yes") == 0);

    price = (qb * 200) + (qs * 700) + (qw * 1000) + (qd * 4000) + (ql * 6000);
    return price;
}

void complete(int price)
{
    char d_bank[50], dummy[50], d_dbank[50];
    int d_balance, i, flag;
    FILE *ptr = fopen("output.txt", "r");

    if (!ptr)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("The total price is %d\n", price);
    if (balance >= price)
    {
        balance -= price;
        printf("You have successfully bought your items, remaining balance = %d\n", balance);
        fclose(ptr);
        return;
    }

    // If not enough in current balance, ask for another bank
    printf("Your balance is not enough, please enter another bank account: ");
    scanf("%s", d_bank);

    for (i = 0; i < 2; i++)
    {
        if (strcmp(d_bank, bank) == 0)
        {
            printf("This is the same bank; your balance is not enough. Enter another: ");
            scanf("%s", d_bank);
            continue;
        }

        // Check if bank already exists
        flag = 0;
        rewind(ptr);
        while (fscanf(ptr, "%s %s %s %s %s %d %s %s",
                      dummy, dummy, dummy, dummy,
                      d_dbank, &d_balance, dummy, dummy) == 8)
        {
            if (strcmp(d_bank, d_dbank) == 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
        {
            printf("This bank account number already exists, enter a different one: ");
            scanf("%s", d_bank);
            continue;
        }

        // Now that the bank is unique, ask for its balance
        printf("Please enter your balance for this new bank: ");
        scanf("%d", &d_balance);

        if (d_balance >= price)
        {
            // Update global bank & balance
            strcpy(bank, d_bank);
            balance = d_balance - price;
            printf("You have successfully bought your items, remaining balance = %d\n", balance);
            fclose(ptr);
            return;
        }

        printf("Insufficient balance, please enter another bank account: ");
        scanf("%s", d_bank);
    }

    printf("Your order has been dropped!\n");
    fclose(ptr);
}

void logout()
{
    char d_email[300][50], d_fname[300][50], d_lname[300][50];
    char d_password[300][50], d_secretq[300][50], d_answer[300][50];
    char d_bank[300][50], temp[50];
    int d_balance[300], i = 0, j, length = 0;
    int temp2;

    FILE *ptr = fopen("output.txt", "r+");
    if (!ptr)
    {
        printf("Error opening output.txt for logout!\n");
        return;
    }

    // Read everything into arrays
    while (fscanf(ptr, "%s %s %s %s %s %d %s %s",
                  d_email[i], d_fname[i], d_lname[i], d_password[i],
                  d_bank[i], &d_balance[i], d_secretq[i], d_answer[i]) == 8)
    {
        i++;
    }
    length = i;

    // Sort by last name
    for (j = 0; j < length - 1; j++)
    {
        for (i = j + 1; i < length; i++)
        {
            if (strcmp(d_lname[j], d_lname[i]) > 0)
            {
                // swap d_lname
                strcpy(temp, d_lname[j]);
                strcpy(d_lname[j], d_lname[i]);
                strcpy(d_lname[i], temp);

                // swap d_email
                strcpy(temp, d_email[j]);
                strcpy(d_email[j], d_email[i]);
                strcpy(d_email[i], temp);

                // swap d_fname
                strcpy(temp, d_fname[j]);
                strcpy(d_fname[j], d_fname[i]);
                strcpy(d_fname[i], temp);

                // swap d_bank
                strcpy(temp, d_bank[j]);
                strcpy(d_bank[j], d_bank[i]);
                strcpy(d_bank[i], temp);

                // swap d_password
                strcpy(temp, d_password[j]);
                strcpy(d_password[j], d_password[i]);
                strcpy(d_password[i], temp);

                // swap d_secretq
                strcpy(temp, d_secretq[j]);
                strcpy(d_secretq[j], d_secretq[i]);
                strcpy(d_secretq[i], temp);

                // swap d_answer
                strcpy(temp, d_answer[j]);
                strcpy(d_answer[j], d_answer[i]);
                strcpy(d_answer[i], temp);

                // swap d_balance
                temp2 = d_balance[j];
                d_balance[j] = d_balance[i];
                d_balance[i] = temp2;
            }
        }
    }

    // Overwrite sorted data
    rewind(ptr);
    for (i = 0; i < length; i++)
    {
        fprintf(ptr, "%s %s %s %s %s %d %s %s\n",
                d_email[i], d_fname[i], d_lname[i], d_password[i],
                d_bank[i], d_balance[i], d_secretq[i], d_answer[i]);
    }

    printf("You have been logged out!\nThank you for visiting!\n");
    fclose(ptr);
}

void delete_account()
{
    char d_email[50], d_fname[50], d_lname[50], d_password[50];
    char d_secretq[50], d_answer[50], d_bank[50], temp[50];
    int d_balance, flag = 1;

    FILE *ptr = fopen("temp.txt", "w");
    FILE *fptr = fopen("output.txt", "r+");
    if (!ptr || !fptr)
    {
        printf("Error opening files for account deletion!\n");
        if (ptr)  fclose(ptr);
        if (fptr) fclose(fptr);
        return;
    }

    // Copy all records except the one with global 'email'
    while (fscanf(fptr, "%s %s %s %s %s %d %s %s",
                  d_email, d_fname, d_lname, d_password,
                  d_bank, &d_balance, d_secretq, d_answer) == 8)
    {
        if (strcmp(d_email, email) != 0)
        {
            fprintf(ptr, "%s %s %s %s %s %d %s %s\n",
                    d_email, d_fname, d_lname, d_password,
                    d_bank, d_balance, d_secretq, d_answer);
        }
    }
    fclose(fptr);
    fclose(ptr);

    remove("output.txt");
    fptr = fopen("output.txt", "w");
    ptr  = fopen("temp.txt", "r");

    if (!fptr || !ptr)
    {
        printf("Error rewriting output.txt!\n");
        if (fptr) fclose(fptr);
        if (ptr)  fclose(ptr);
        return;
    }

    // Now we copy from temp -> output, skipping duplicates
    // (In your logic, it looks like you wanted to skip consecutive lines if repeated)
    rewind(ptr);
    char last_email[50] = "";
    while (fscanf(ptr, "%s %s %s %s %s %d %s %s",
                  d_email, d_fname, d_lname, d_password,
                  d_bank, &d_balance, d_secretq, d_answer) == 8)
    {
        // If it's the first line or a different email than the last
        if (strcmp(d_email, last_email) != 0)
        {
            fprintf(fptr, "%s %s %s %s %s %d %s %s\n",
                    d_email, d_fname, d_lname, d_password,
                    d_bank, d_balance, d_secretq, d_answer);
        }
        strcpy(last_email, d_email);
    }

    fclose(fptr);
    fclose(ptr);

    remove("temp.txt");

    printf("Your account has been deleted.\n");
}

int main()
{
    int user, status = 1;
    int user_choice, shop_selection;

    user = log_in();
    if (user < 0) // if file open error or something
        return 1;

    while (status == 1)
    {
        user_choice = menu();
        switch (user_choice)
        {
        case 1:
            change_user_information(user);
            break;
        case 2:
            shop_selection = shop_section();
            complete(shop_selection);
            break;
        case 3:
            logout();
            status = 0;
            break;
        case 4:
            delete_account();
            status = 0;
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    }
    return 0;
}
