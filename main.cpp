#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"

enum PrimaryPrompt
{
    LOGIN,
    REGISTER,
    EXIT,
    ADMIN_LOGIN
};
enum RegisterPrompt
{
    CREATE_BUYER,
    CREATE_SELLER,
    BACK
};
using namespace std;

// starter configuration
const int MAX_ACCOUNTS = 50;
BankCustomer *bankAccounts[MAX_ACCOUNTS];
Buyer *buyers[MAX_ACCOUNTS];
seller *sellers[MAX_ACCOUNTS];
int bankCount = 0, buyerCount = 0, sellerCount = 0;

// declare needed function
void viewAllUsers();
void viewUserDetails();
void searchUser();
void createNewAccount();
void deleteUser();
void systemReport();

int main()
{
    // create a loop prompt
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    const char *ADMIN_USERNAME = "root";
    const char *ADMIN_PASSWORD = "toor";
    string username, password;

    // Initialize counters and create sample data for testing
    bankCount = 0;
    buyerCount = 0;
    sellerCount = 0;

    // Create sample bank accounts
    string bankName1, bankName2, bankName3;
    bankName1 = "John Smith";
    bankName2 = "Jane Doe";
    
    bankAccounts[0] = new BankCustomer(101, bankName1, 5000.0);
    bankAccounts[1] = new BankCustomer(102, bankName2, 3500.0);
    bankCount = 2;

    // buyer samples
    string buyerName1, buyerName2;
    string buyerAddr1, buyerAddr2;
    string buyerPhone1, buyerPhone2;

    buyerName1 = "John Smith";
    buyerName2 = "Jane Doe";
    buyerAddr1 = "Jakarta";
    buyerAddr2 = "Bandung";
    buyerPhone1 = "12345";
    buyerPhone2 = "123456";

    buyers[0] = new Buyer(1, buyerName1, buyerAddr1, buyerPhone1, *bankAccounts[0]);
    buyers[1] = new Buyer(2, buyerName2, buyerAddr2, buyerPhone2, *bankAccounts[1]);
    buyerCount = 2;

    // seller samples
    string storeName;
    storeName = "John's Electronics Store";

    sellers[0] = new seller(*buyers[0], 201, storeName);
    sellerCount = 1;

    cout << "=== Sample Data Loaded ===" << endl;
    cout << "3 Bank Accounts, 2 Buyers, 1 Seller created for testing" << endl;
    cout << "Use Admin Login (root/toor) to manage accounts" << endl
         << endl;

    while (prompt != EXIT)
    {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Admin Login" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt)
        {
        case LOGIN:
            cout << "Login selected." << endl;
            /* if Login is selected, based on authority then provide options:
            assume user is logged in as Buyer for now
            1. Chek Account Status (will display if user is Buyer or Seller or both and linked banking account status)
            Will display Buyer, Seller and Banking Account details
            2. Upgrade Account to Seller
            Will prompt user to enter Seller details and create a Seller account linked to Buyer account
            Will reject if a user dont have a banking account linked
            3. Create Banking Account (if not already linked), will be replaced with banking functions
            Must provides: initial deposit amount, Address, Phone number, Email
            Banking functions will provides: Balance checking, Transaction History, Deposit, Withdraw
            4. Browse Store Functionality
            Will display all stores initially
            Need to select a store to browse each store inventory
            Will display all items in the store inventory
            After selecting an item, will display item details and option to add to cart
            After adding to cart, will notify user item is added to cart
            5. Order Functionality
            Will display all items in cart
            Will provide option to remove item from cart
            Will provide option to checkout
            After checkout invoide will be generated (will go to payment functionality)
            6. Payment Functionality
            Will display all listed invoices
            Pick an invoice to pay
            Will display invoice details and total amount
            Will provide option to pay invoice
            Payment is done through confirmation dialogue
            In confirmation dialogue, will display account balance as precursor
            User will need to manually enter invoice id to pay
            After paying balance will be redacted from buyer and added to the responding seller account
            After payment, order status will be changed to paid
            7. Logout (return to main menu)
            Display confirmation dialogue
            If confirmed, return to main menu
            If not, return to Buyer menu
            8. Delete Account (remove both Buyer and Seller account and relevant banking account)
            Display confirmation dialogue
            If confirmed, delete account and return to main menu
            If not, return to Buyer menu

            assume user is logged in as Seller for now
            9. Check Inventory
            10. Add Item to Inventory
            11. Remove Item from Inventory
            12. View Orders (will display all orders placed to this seller
            Only orders with paid status will be listed
            Order details will listing items, quantity, total amount, buyer details, order status (paid, cancelled, completed)
            extra functions
            9. Exit to main Menu
            10. Exit Program
            **/
            break;
        case REGISTER:
            regPrompt = CREATE_BUYER; // reset regPrompt to CREATE_BUYER when entering register menu
            while (regPrompt != BACK)
            {
                cout << "Register selected. " << endl;
                cout << "Select an option: " << endl;
                cout << "1. Create Buyer Account" << endl;
                cout << "2. Create Seller Account" << endl;
                cout << "3. Back" << endl;
                int regChoice;
                cin >> regChoice;
                regPrompt = static_cast<RegisterPrompt>(regChoice - 1);
                switch (regPrompt)
                {
                case CREATE_BUYER:
                    cout << "Create Buyer Account selected." << endl;
                    break;
                case CREATE_SELLER:
                    cout << "Create Seller Account selected." << endl;
                    break;
                case BACK:
                    cout << "Back selected." << endl;
                    break;
                default:
                    cout << "Invalid option." << endl;
                    break;
                }
            }
            /* if register is selected then went throuhh registration process:
            1. Create a new Buyer Account
            Must provides: Name, Home Address, Phone number, Email
            2. Option to create a Seller Account (will be linked to Buyer account)
            Must Provides 1: Home Address, Phone number, Email
            Must provides 2: Store Name, Store Address, Store Phone number, Store Email
            Must provides 3: initial deposit amount
            After finished immediately logged in as Buyer/Seller
            */
            break;
        case EXIT:
            cout << "Exiting." << endl;
            break;
        case ADMIN_LOGIN:
            /* Prompt for username & password then check the entries with our hard coded features */
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD)
            {
                cout << "Admin login successful." << endl;
                /** After login create a sub prompt that provides the following features
                1. Account Management
                    - View All Buyers, Sellers
                    - View All details of Buyers, Sellers
                    - Seek certain buyer of seller based on Name / account Id / address / phone number
                    - Create new buyer/seller/Bank account
                    - Remove buyer/seller based on ID (all related info will be deleted)
                2. System Report
                    - Total number of Buyers, Sellers
                    - Total number of Banking Accounts
                */

                // Simple admin menu implementation
                int adminChoice;
                while (true)
                {
                    cout << "\n=== Admin Panel ===" << endl;
                    cout << "1. Account Management" << endl;
                    cout << "2. System Report" << endl;
                    cout << "3. Exit to Main Menu" << endl;
                    cout << "Choice: ";
                    cin >> adminChoice;

                    if (adminChoice == 1)
                    {
                        // Account Management submenu
                        int mgmtChoice;
                        while (true)
                        {
                            cout << "\n=== Account Management ===" << endl;
                            cout << "1. View All Buyers and Sellers" << endl;
                            cout << "2. View User Details" << endl;
                            cout << "3. Search User" << endl;
                            cout << "4. Create New User/Account" << endl;
                            cout << "5. Delete User by ID" << endl;
                            cout << "6. Back to Admin Menu" << endl;
                            cout << "Choice: ";
                            cin >> mgmtChoice;

                            switch (mgmtChoice)
                            {
                            case 1:
                                viewAllUsers();
                                break;
                            case 2:
                                viewUserDetails();
                                break;
                            case 3:
                                searchUser();
                                break;
                            case 4:
                                createNewAccount();
                                break;
                            case 5:
                                deleteUser();
                                break;
                            case 6:
                                goto admin_menu; 
                            default:
                                cout << "Invalid option!" << endl;
                                break;
                            }
                        }
                    }
                    else if (adminChoice == 2)
                    {
                        systemReport();
                    }
                    else if (adminChoice == 3)
                    {
                        break; 
                    }
                    else
                    {
                        cout << "Invalid option!" << endl;
                    }
                admin_menu:; 
                }
            }
            else
            {
                cout << "Admin login failed." << endl;
                break; 
            }
            break;
        default:
            cout << "Invalid option." << endl;
            break;
        }
        cout << endl;
    }

    
    return 0;
}

// ADMIN function implementations
void viewAllUsers()
{
    cout << "\n=== All Buyers ===" << endl;
    if (buyerCount == 0)
    {
        cout << "No buyers in system." << endl;
    }
    else
    {
        for (int i = 0; i < buyerCount; i++)
        {
            cout << "ID: " << buyers[i]->getId() << " | Name: " << buyers[i]->getName() << endl;
        }
    }

    cout << "\n=== All Sellers ===" << endl;
    if (sellerCount == 0)
    {
        cout << "No sellers in system." << endl;
    }
    else
    {
        for (int i = 0; i < sellerCount; i++)
        {
            cout << "ID: " << sellers[i]->getId() << " | Name: " << sellers[i]->getName() << endl;
        }
    }
}

void viewUserDetails()
{
    cout << "\n=== View User Details ===" << endl;
    cout << "1. View Buyer Details" << endl;
    cout << "2. View Seller Details" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter Buyer ID: ";
        int id;
        cin >> id;

        bool found = false;
        for (int i = 0; i < buyerCount; i++)
        {
            if (buyers[i]->getId() == id)
            {
                cout << "\n--- Buyer Details ---" << endl;
                cout << "ID: " << buyers[i]->getId() << endl;
                cout << "Name: " << buyers[i]->getName() << endl;
                cout << "Address: " << buyers[i]->getAddress() << endl;
                cout << "Phone: " << buyers[i]->getPhone() << endl;
                cout << "Bank Account Details:" << endl;
                buyers[i]->getAccount().printInfo();
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Buyer with ID " << id << " not found!" << endl;
        }
    }
    else if (choice == 2)
    {
        cout << "Enter Seller ID: ";
        int id;
        cin >> id;

        bool found = false;
        for (int i = 0; i < sellerCount; i++)
        {
            if (sellers[i]->getId() == id)
            {
                cout << "\n--- Seller Details ---" << endl;
                cout << "ID: " << sellers[i]->getId() << endl;
                cout << "Name: " << sellers[i]->getName() << endl;
                cout << "Address: " << sellers[i]->getAddress() << endl;
                cout << "Phone: " << sellers[i]->getPhone() << endl;
                cout << "Bank Account Details:" << endl;
                sellers[i]->getAccount().printInfo();
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Seller with ID " << id << " not found!" << endl;
        }
    }
}

void searchUser()
{
    cout << "\n=== Search User ===" << endl;
    cout << "1. Search by Name" << endl;
    cout << "2. Search by Account ID" << endl;
    cout << "3. Search by Address" << endl;
    cout << "4. Search by Phone Number" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter name to search: ";
        string searchName;
        cin.ignore();
        getline(cin, searchName);

        bool found = false;
        cout << "\n--- Search Results ---" << endl;

        for (int i = 0; i < buyerCount; i++)
        {
            if (buyers[i]->getName().find(searchName) != string::npos)
            {
                cout << "Buyer - ID: " << buyers[i]->getId() << " | Name: " << buyers[i]->getName() << endl;
                found = true;
            }
        }

        for (int i = 0; i < sellerCount; i++)
        {
            if (sellers[i]->getName().find(searchName) != string::npos)
            {
                cout << "Seller - ID: " << sellers[i]->getId() << " | Name: " << sellers[i]->getName() << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "No users found with name containing: " << searchName << endl;
        }
    }
    else if (choice == 2)
    {
        cout << "Enter Account ID to search: ";
        int searchId;
        cin >> searchId;

        bool found = false;
        cout << "\n--- Search Results ---" << endl;

        for (int i = 0; i < buyerCount; i++)
        {
            if (buyers[i]->getId() == searchId)
            {
                cout << "Buyer - ID: " << buyers[i]->getId() << " | Name: " << buyers[i]->getName() << endl;
                found = true;
            }
        }

        for (int i = 0; i < sellerCount; i++)
        {
            if (sellers[i]->getId() == searchId)
            {
                cout << "Seller - ID: " << sellers[i]->getId() << " | Name: " << sellers[i]->getName() << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "No users found with ID: " << searchId << endl;
        }
    }
    else if (choice == 3)
    {
        cout << "Enter address to search: ";
        string searchAddress;
        cin.ignore();
        getline(cin, searchAddress);

        bool found = false;
        cout << "\n--- Search Results ---" << endl;

        for (int i = 0; i < buyerCount; i++)
        {
            if (buyers[i]->getAddress().find(searchAddress) != string::npos)
            {
                cout << "Buyer - ID: " << buyers[i]->getId() << " | Name: " << buyers[i]->getName() << " | Address: " << buyers[i]->getAddress() << endl;
                found = true;
            }
        }

        for (int i = 0; i < sellerCount; i++)
        {
            if (sellers[i]->getAddress().find(searchAddress) != string::npos)
            {
                cout << "Seller - ID: " << sellers[i]->getId() << " | Name: " << sellers[i]->getName() << " | Address: " << sellers[i]->getAddress() << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "No users found with address containing: " << searchAddress << endl;
        }
    }
    else if (choice == 4)
    {
        cout << "Enter phone number to search: ";
        string searchPhone;
        cin.ignore();
        getline(cin, searchPhone);

        bool found = false;
        cout << "\n--- Search Results ---" << endl;

        for (int i = 0; i < buyerCount; i++)
        {
            if (buyers[i]->getPhone().find(searchPhone) != string::npos)
            {
                cout << "Buyer - ID: " << buyers[i]->getId() << " | Name: " << buyers[i]->getName() << " | Phone: " << buyers[i]->getPhone() << endl;
                found = true;
            }
        }

        for (int i = 0; i < sellerCount; i++)
        {
            if (sellers[i]->getPhone().find(searchPhone) != string::npos)
            {
                cout << "Seller - ID: " << sellers[i]->getId() << " | Name: " << sellers[i]->getName() << " | Phone: " << sellers[i]->getPhone() << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "No users found with phone containing: " << searchPhone << endl;
        }
    }
}

void createNewAccount()
{
    cout << "\n=== Create New Account ===" << endl;
    cout << "1. Create Bank Account" << endl;
    cout << "2. Create Buyer Account" << endl;
    cout << "3. Create Seller Account" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        if (bankCount >= MAX_ACCOUNTS)
        {
            cout << "Maximum bank accounts reached!" << endl;
            return;
        }

        cout << "Enter Bank Account ID: ";
        int id;
        cin >> id;

        cout << "Enter Account Holder Name: ";
        string name;
        cin.ignore();
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        double balance;
        cin >> balance;

        bankAccounts[bankCount] = new BankCustomer(id, name, balance);
        bankCount++;
        cout << "Bank account created successfully!" << endl;
    }
    else if (choice == 2)
    {
        if (buyerCount >= MAX_ACCOUNTS)
        {
            cout << "Maximum buyers reached!" << endl;
            return;
        }

        if (bankCount == 0)
        {
            cout << "No bank accounts available. Create a bank account first." << endl;
            return;
        }

        cout << "Enter Buyer ID: ";
        int id;
        cin >> id;

        cout << "Enter Buyer Name: ";
        string name;
        cin.ignore();
        getline(cin, name);

        cout << "Enter Buyer Address: ";
        string address;
        getline(cin, address);

        cout << "Enter Buyer Phone: ";
        string phone;
        getline(cin, phone);

        cout << "Available Bank Accounts:" << endl;
        for (int i = 0; i < bankCount; i++)
        {
            cout << i << ": " << bankAccounts[i]->getName() << " (ID: " << bankAccounts[i]->getId() << ")" << endl;
        }

        cout << "Select bank account index: ";
        int bankIndex;
        cin >> bankIndex;

        if (bankIndex >= 0 && bankIndex < bankCount)
        {
            buyers[buyerCount] = new Buyer(id, name, address, phone, *bankAccounts[bankIndex]);
            buyerCount++;
            cout << "Buyer account created successfully!" << endl;
        }
        else
        {
            cout << "Invalid selection!" << endl;
        }
    }
    else if (choice == 3)
    {
        if (sellerCount >= MAX_ACCOUNTS)
        {
            cout << "Maximum sellers reached!" << endl;
            return;
        }

        if (buyerCount == 0)
        {
            cout << "No buyer accounts available. Create a buyer account first." << endl;
            return;
        }

        cout << "Available Buyers:" << endl;
        for (int i = 0; i < buyerCount; i++)
        {
            cout << i << ": " << buyers[i]->getName() << " (ID: " << buyers[i]->getId() << ")" << endl;
        }

        cout << "Select buyer index to upgrade: ";
        int buyerIndex;
        cin >> buyerIndex;

        if (buyerIndex >= 0 && buyerIndex < buyerCount)
        {
            cout << "Enter Seller ID: ";
            int sellerId;
            cin >> sellerId;

            cout << "Enter Store Name: ";
            string storeName;
            cin.ignore();
            getline(cin, storeName);

            sellers[sellerCount] = new seller(*buyers[buyerIndex], sellerId, storeName);
            sellerCount++;
            cout << "Seller account created successfully!" << endl;
        }
        else
        {
            cout << "Invalid selection!" << endl;
        }
    }
}

void deleteUser()
{
    cout << "\n=== Delete User ===" << endl;
    cout << "1. Delete Buyer" << endl;
    cout << "2. Delete Seller" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter Buyer ID to delete: ";
        int id;
        cin >> id;

        for (int i = 0; i < buyerCount; i++)
        {
            if (buyers[i]->getId() == id)
            {
                cout << "Delete buyer '" << buyers[i]->getName() << "'? (y/n): ";
                char confirm;
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y')
                {
                    delete buyers[i];
                    
                    for (int j = i; j < buyerCount - 1; j++)
                    {
                        buyers[j] = buyers[j + 1];
                    }
                    buyerCount--;
                    cout << "Buyer deleted successfully!" << endl;
                }
                else
                {
                    cout << "Deletion cancelled." << endl;
                }
                return;
            }
        }
        cout << "Buyer with ID " << id << " not found!" << endl;
    }
    else if (choice == 2)
    {
        cout << "Enter Seller ID to delete: ";
        int id;
        cin >> id;

        for (int i = 0; i < sellerCount; i++)
        {
            if (sellers[i]->getId() == id)
            {
                cout << "Delete seller '" << sellers[i]->getName() << "'? (y/n): ";
                char confirm;
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y')
                {
                    delete sellers[i];
                    
                    for (int j = i; j < sellerCount - 1; j++)
                    {
                        sellers[j] = sellers[j + 1];
                    }
                    sellerCount--;
                    cout << "Seller deleted successfully!" << endl;
                }
                else
                {
                    cout << "Deletion cancelled." << endl;
                }
                return;
            }
        }
        cout << "Seller with ID " << id << " not found!" << endl;
    }
}

void systemReport()
{
    cout << "\n=== System Report ===" << endl;
    cout << "Total Buyers: " << buyerCount << endl;
    cout << "Total Sellers: " << sellerCount << endl;
    cout << "Total Bank Accounts: " << bankCount << endl;

    double totalBalance = 0;
    for (int i = 0; i < bankCount; i++)
    {
        totalBalance += bankAccounts[i]->getBalance();
    }
    cout << "Total System Balance: $" << totalBalance << endl;
}