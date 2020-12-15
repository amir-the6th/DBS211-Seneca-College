
//----------------------------------------------------------------*
// Amirhossein Sabagh | #152956199 | Final Project | 2020-08-11 --*
//----------------------------------------------------------------*

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <occi.h>
#include <iomanip>
#include <string>

/*
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
*/

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;


struct Employee {
    int employeeNumber;
    char lastName[50];
    char firstName[50];
    char email[100];
    char phone[50];
    char extension[10];
    char reportsTo[100];
    char jobTitle[50];
    char city[50];
};


/*********** Function prototype ***********/

int menu(void);
int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp);
void displayEmployee(Connection* conn, struct Employee* emp);
void displayAllEmployees(Connection* conn);
void insertEmployee(Connection* conn, struct Employee emp);
void updateEmployee(Connection* conn, int employeeNumber);
void deleteEmployee(Connection* conn, int employeeNumber);
int getPositive(int max, int min);	// Utility function to get a positive number from user prompt
void getStringInput(int length, char* field);  // Utility function to get string from user prompt


int main(void)
{
    Environment* env = nullptr;
    Connection* conn = nullptr;
    //Statement* stmt = nullptr;
   // ResultSet* rs = nullptr;

    string str;
    string usr = "dbs211_202c25";
    string pass = "14013167";
    string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";
    int userPromptInput = 0;

    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(usr, pass, srv);
        cout << "Connection is successful\n" << endl;
        Statement* stmt = conn->createStatement();

        struct Employee emp = { 0, "", "" , "" , "" , "" , "" , "" , "" };       
        int pass = 0;

        do {
            int chMenu = menu();
            if (chMenu == 6) {	// Exit
                cout << "Terminating the system. Goodbye " << usr << endl;
                pass = 1;
            }
            else if (chMenu == 1) {
                // Find Employee
                cout << "Employee Number: ";
                int employeeNum = getPositive(9999, 1);	// user Input for searching employee number
                int returnedValue = findEmployee(conn, employeeNum, &emp);	// call findEmployee function
                if (returnedValue != 0) {	// If the searching user exists in DB
                    displayEmployee(conn, &emp);	// Display (single) user information
                }
                else {	// If the searching user does not exist in DB
                    cout << "Employee " << employeeNum << " does not exist" << endl;
                }
            }
            else if (chMenu == 2) {	// Employees Report
                displayAllEmployees(conn);
            }
            else if (chMenu == 3) {	// Add Employee
                cout << "Employee Number: ";
                emp.employeeNumber = getPositive(9999, 1);	// user Input for employee number
                cout << "Last Name: ";
                getStringInput(50, emp.lastName);	// user Input for last name
                cout << "First Name: ";
                getStringInput(50, emp.firstName);	// user Input for first name
                cout << "Email: ";
                getStringInput(100, emp.email);	// user Input for email
                cout << "extension: ";
                getStringInput(10, emp.extension);	// user Input for extension
                cout << "Job Title: ";
                getStringInput(50, emp.jobTitle);	// user Input for job title
                cout << "City: ";
                getStringInput(50, emp.city);	// user Input for city
                insertEmployee(conn, emp);
            }
            else if (chMenu == 4) {	// Update Employee
                cout << "Enter employeenumber: ";
                int employeeNum = getPositive(9999, 1);	// user Input for employee number
                updateEmployee(conn, employeeNum);	// call updateEmployee function
            }
            else if (chMenu == 5) {
                //Remove Employee
                cout << "Enter employeenumber: ";
                int employeeNum = getPositive(9999, 1);	// user Input for employee number
                deleteEmployee(conn, employeeNum);	// call deleteEmployee function
            }
        } while (pass == 0);                
                                     
        conn->terminateStatement(stmt);
        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    }

    catch (SQLException& sqlExcp) 
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
        return 0;
}

int menu(void) {
    int choice = 0;
    do {
        cout << "********************* HR Menu *********************" << endl;
        cout << "1) Find Employee" << endl << "2) Employees Report" << endl << "3) Add Employee"
            << endl << "4) Update Employee" << endl << "5) Delete Employee" << endl << "6) Exit" << ": " << endl;
        cin >> choice;
        cout << endl;
    } while (choice < 0 || choice > 6);

    return choice;
}

int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp) {
    int returnValue = 0;

    try {
        // Quary for joining tables
        Statement* stmtJoin = conn->createStatement("SELECT\n"
            "e.employeenumber, e.lastname, e.firstname, e.email, o.phone, e.extension, e.reportsTo, e2.firstname || ' ' || e2.lastname managerName, e.jobtitle, o.city\n"
            "FROM employees e\n"
            "JOIN offices o ON e.officecode = o.officecode\n"
            "LEFT JOIN employees e2 ON e.reportsto = e2.employeenumber\n"
            "WHERE e.employeenumber = :1");
        stmtJoin->setNumber(1, employeeNumber);
        ResultSet* rsJoin = stmtJoin->executeQuery();

        if (rsJoin->next()) {	// if (a) result(s) exist(s), store data to structure
            emp->employeeNumber = rsJoin->getInt(1);
            strcpy(emp->lastName, rsJoin->getString(2).c_str());
            strcpy(emp->firstName, rsJoin->getString(3).c_str());
            strcpy(emp->email, rsJoin->getString(4).c_str());
            strcpy(emp->phone, rsJoin->getString(5).c_str());
            strcpy(emp->extension, rsJoin->getString(6).c_str());
            strcpy(emp->reportsTo, rsJoin->getString(8).c_str());
            strcpy(emp->jobTitle, rsJoin->getString(9).c_str());
            strcpy(emp->city, rsJoin->getString(10).c_str());
            returnValue = 1;	// change return value
        }
        conn->terminateStatement(stmtJoin);
        return returnValue;
    }
    catch (SQLException& sqlExcp) {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
        cout << "There is an error in your quiry statement. Refer error code." << endl << endl;
    }
}

void insertEmployee(Connection* conn, struct Employee emp) {
    int returnVal = findEmployee(conn, emp.employeeNumber, &emp);
    if (returnVal == 1) {	// if the employee already exists
        cout << "An employee with the same employee number exists." << endl;
    }
    else {	// if the employee does not exist
        int maxOfficeCode;
        try {
            Statement* stmtGetMaxOfficCode = conn->createStatement();
            ResultSet* rsGetMaxOfficCode = stmtGetMaxOfficCode->executeQuery("SELECT MAX(TO_NUMBER(officecode)) FROM offices");

            if (!rsGetMaxOfficCode->next()) {	// if the query does not return any rows
                maxOfficeCode = 0;
            }
            else {	// if the query does return any rows
                maxOfficeCode = rsGetMaxOfficCode->getInt(1);	// store max officecode into a variable maxOfficeCode
            }
            conn->terminateStatement(stmtGetMaxOfficCode);
        }
        catch (SQLException& sqlExcp) {
            cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
            cout << "There is an error in your quiry statement. Refer error code." << endl << endl;
        }

        bool isCityExist = false;
        int officeCode = 0;

        if (isCityExist == true) {
            try {
                Statement* stmtInsert = conn->createStatement();
                stmtInsert->setSQL("INSERT INTO employees VALUES(:1, :2, :3, :4, :5, :6, NULL, :7)");
                stmtInsert->setNumber(1, emp.employeeNumber);
                stmtInsert->setString(2, emp.lastName);
                stmtInsert->setString(3, emp.firstName);
                stmtInsert->setString(4, emp.extension);
                stmtInsert->setString(5, emp.email);
                stmtInsert->setNumber(6, officeCode);
                stmtInsert->setString(7, emp.jobTitle);
                stmtInsert->executeUpdate();

                cout << "The new employee is added successfully." << endl;
                conn->terminateStatement(stmtInsert);
            }
            catch (SQLException& sqlExcp) {
                cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
                cout << "There is an error in your quiry statement. Refer error code." << endl << endl;
            }
        }
        else {
            try {
                Statement* stmtInsert = conn->createStatement();
                stmtInsert->setSQL("INSERT INTO offices VALUES(:1, :2, :3, :4, NULL, NULL, :5, :6, :7)");
                int input = maxOfficeCode + 1;
                stmtInsert->setNumber(1, input);
                stmtInsert->setString(2, emp.city);
                stmtInsert->setString(3, "+6 666 666 6666");
                stmtInsert->setString(4, "Esfahan");
                stmtInsert->setString(5, "Iran");
                stmtInsert->setString(6, "000000");
                stmtInsert->setString(7, "NA");
                stmtInsert->executeUpdate();

                stmtInsert->setSQL("INSERT INTO employees VALUES(:1, :2, :3, :4, :5, :6, NULL, :7)");
                stmtInsert->setNumber(1, emp.employeeNumber);
                stmtInsert->setString(2, emp.lastName);
                stmtInsert->setString(3, emp.firstName);
                stmtInsert->setString(4, emp.extension);
                stmtInsert->setString(5, emp.email);
                stmtInsert->setNumber(6, input);
                stmtInsert->setString(7, emp.jobTitle);
                stmtInsert->executeUpdate();
                cout << "The new employee is added successfully." << endl;
                conn->terminateStatement(stmtInsert);
            }
            catch (SQLException& sqlExcp) {
                cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
                cout << "There is an error in your quiry statement. Refer error code." << endl << endl;
            }
        }
    }
}

void displayAllEmployees(Connection* conn) {
    try {
        // Standard SQL Query (without user input) //
        Statement* stmtJoin = conn->createStatement();
        ResultSet* rsJoin = stmtJoin->executeQuery("SELECT e.employeenumber, e.firstname || ' ' || e.lastname employeeName, e.email, o.phone, e.extension, e2.firstname || ' ' || e2.lastname managerName FROM employees e JOIN offices o ON e.officecode = o.officecode LEFT JOIN employees e2 ON e.reportsto = e2.employeenumber ORDER BY e.employeenumber");

        if (!rsJoin->next()) {	// if the query does not return any rows
            cout << "There is no employees¡¯ information to be displayed" << endl << endl;
        }
        else {	// if the query does return any rows
            cout.width(10);
            cout << "E";
            cout.width(20);
            cout << "Employee Name";
            cout.width(35);
            cout << "Email";
            cout.width(20);
            cout << "Phone";
            cout.width(10);
            cout << "Ext";
            cout.width(20);
            cout << "Manager" << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

            do {
                int employeeNumber = rsJoin->getInt(1);
                string employeeName = rsJoin->getString(2);
                string email = rsJoin->getString(3);
                string phone = rsJoin->getString(4);
                string ext = rsJoin->getString(5);
                string manager = rsJoin->getString(6);

                cout.width(10);
                cout << employeeNumber;
                cout.width(20);
                cout << employeeName;
                cout.width(35);
                cout << email;
                cout.width(20);
                cout << phone;
                cout.width(10);
                cout << ext;
                cout.width(20);
                cout << manager << endl;
            } while (rsJoin->next());
            cout << endl;
        }
        conn->terminateStatement(stmtJoin);
    }
    catch (SQLException& sqlExcp) {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
        cout << "There is an error in your quiry statement. Refer error code." << endl << endl;
    }
}


void updateEmployee(Connection* conn, int employeeNumber) {
    struct Employee emp = { 0, "", "" , "" , "" , "" , "" , "" , "" };
    int returnVal = findEmployee(conn, employeeNumber, &emp);
    if (returnVal == 0) {
        cout << "Employee " << employeeNumber << " does not exist" << endl;
    }
    else {
        char newExtension[10];
        cout << "New Extension: ";
        getStringInput(10, newExtension);
        try {
            Statement* stmtUpdate = conn->createStatement();
            stmtUpdate->setSQL("UPDATE employees SET extension = :1\n"
                "WHERE employeenumber = :2");
            stmtUpdate->setString(1, newExtension);
            stmtUpdate->setNumber(2, employeeNumber);
            stmtUpdate->executeUpdate();

            cout << "The employee is updated successfully." << endl;
            conn->terminateStatement(stmtUpdate);
        }
        catch (SQLException& sqlExcp) {
            cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
            cout << "There is an error in your quiry statement. Refer error code." << endl << endl;
        }
    }
}


void deleteEmployee(Connection* conn, int employeeNumber) {
    struct Employee emp = { 0, "", "" , "" , "" , "" , "" , "" , "" };
    int returnVal = findEmployee(conn, employeeNumber, &emp);
    if (returnVal == 0) {
        cout << "The employee does not exist" << endl;
    }
    else {
        try {
            Statement* stmtDelete = conn->createStatement();
            stmtDelete->setSQL("DELETE FROM employees WHERE employeenumber = :1");
            stmtDelete->setNumber(1, employeeNumber);
            stmtDelete->executeUpdate();
            cout << "The employee is deleted" << endl;
            conn->terminateStatement(stmtDelete);
        }
        catch (SQLException& sqlExcp) {
            cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
            cout << "There is an error in your quiry statement. Refer error code." << endl << endl;
        }
    }
}


void displayEmployee(Connection* conn, Employee* emp) {	// display "single" user
    cout << "Employee Number = " << emp->employeeNumber << endl;
    cout << "Lastname = " << emp->lastName << endl;
    cout << "Firstname = " << emp->firstName << endl;
    cout << "Email = " << emp->email << endl;
    cout << "Phone = " << emp->phone << endl;
    cout << "Extension = " << emp->extension << endl;
    cout << "Reports To = " << emp->reportsTo << endl;
    cout << "Job Title = " << emp->jobTitle << endl;
    cout << "City = " << emp->city << endl << endl;
}

void getStringInput(int length, char* userInputString) {
    int keepreading = 1;
    char* userInput = nullptr;
    do {
        userInput = new char[length + 1];
        cin.get(userInput, length);
        if (cin.fail()) {
            cerr << "Invalid Input, try again: ";
            cin.clear();
            cin.ignore(2000, '\n');
            delete[] userInput;
            userInput = nullptr;
        }
        else if (userInput[0] == '\0' || char(cin.get()) != '\n') {	// check if the istream object failed while reading
            cerr << "Invalid Input, try again: ";
            cin.ignore(2000, '\n');
            delete[] userInput;
            userInput = nullptr;
        }
        else {
            keepreading = 0;
            strncpy(userInputString, userInput, length);
            userInputString[length] = '\0';
            delete[] userInput;
            userInput = nullptr;
        }
    } while (keepreading == 1);
}


int getPositive(int max, int min) {
    int value;
    int keepreading = 1;
    do {
        cin >> value;

        if (cin.fail()) {   // check for invalid character
            cerr << "Invalid Integer, try again: ";
            cin.clear();
            cin.ignore(2000, '\n');
        }
        else if (value < min || value > max) {
            cerr << "Invalid selection, try again: ";
            cin.ignore(2000, '\n');
        }
        else if (char(cin.get()) != '\n') {
            cerr << "Trailing characters.  Try Again." << endl;
            cin.ignore(2000, '\n');
        }
        else {
            keepreading = 0;
        }
    } while (keepreading == 1);
    return value;
}