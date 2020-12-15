//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <occi.h>
//#include <iomanip>
//#include <string>
//
///*
//#include <windows.h>
//#include <sqlext.h>
//#include <sqltypes.h>
//#include <sql.h>
//*/
//
//using oracle::occi::Environment;
//using oracle::occi::Connection;
//using namespace oracle::occi;
//using namespace std;
//
//
//struct Employee {
//    int employeeNumber;
//    char lastName[50];
//    char firstName[50];
//    char email[100];
//    char phone[50];
//    char extension[10];
//    char reportsTo[100];
//    char jobTitle[50];
//    char city[50];
//};
//
//
//int menu(void);
//int findEmployee(*conn, int employeeNumber, struct Employee* emp);
//void displayEmployee(oracle conn, struct Employee emp);
//void displayAllEmployees(*conn);
//
//
//int main(void)
//{
//    Environment* env = nullptr;
//    Connection* conn = nullptr;
//    //Statement* stmt = nullptr;
//   // ResultSet* rs = nullptr;
//
//    string str;
//    string usr = "      ";
//    string pass = "         ";
//    string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";
//    
//
//    try {
//        env = Environment::createEnvironment(Environment::DEFAULT);
//        conn = env->createConnection(usr, pass, srv);
//        cout << "Connection is successful\n" << endl;
//        Statement* stmt = conn->createStatement();
//
//           
//
//
//
//
//        conn->terminateStatement(stmt);
//        env->terminateConnection(conn);
//        Environment::terminateEnvironment(env);
//    }
//    catch (SQLException& sqlExcp)
//    {
//        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
//    }
//    return 0;
//}
//
//int menu(void) {
//    int option = 0;
//    do {
//        cout << "********************* HR Menu *********************" << endl;
//        cout << "1) Find Employee" << endl << "2) Employees Report" << endl << "3) Add Employee"
//            << endl << "4) Update Employee" << endl << "4) Update Employee" << endl << "6) Exit" << ": " << endl;
//        cin >> option;
//        cout << endl;
//    } while (option < 0 || option > 6);
//
//    return choice;
//}
//
//int findEmployee(*conn, int employeeNumber, struct Employee* emp) {
//
//
//    return 0;
//}
//
//void displayEmployee(oracle conn, struct Employee emp) {
//
//
//}
//
//void displayAllEmployees(*conn) {
//
//
//}