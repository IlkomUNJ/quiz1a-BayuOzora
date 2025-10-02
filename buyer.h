#ifndef BUYER_H
#define BUYER_H

#include <cstddef>
#include <string>
#include "bank_customer.h"

using namespace std;

class Buyer
{
private:
    int id;
    string name;
    string address;
    string phone;
    BankCustomer &account; // Association with BankCustomer

public:
    Buyer(int id, const string &name, BankCustomer &account0)
        : id(id), name(name), account(account0)
    {
        address = string();
        phone = string();
    }

    Buyer(int id, const string &name, const string &address, const string &phone, BankCustomer &account0)
        : id(id), name(name), address(address), phone(phone), account(account0) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getPhone() const { return phone; }
    BankCustomer &getAccount() { return account; }

    void setId(int newId) { id = newId; }
    void setName(const std::string &newName) { name = newName; }
    void setAddress(const std::string &newAddress) { address = newAddress; }
    void setPhone(const std::string &newPhone) { phone = newPhone; }
};

#endif // BUYER_H