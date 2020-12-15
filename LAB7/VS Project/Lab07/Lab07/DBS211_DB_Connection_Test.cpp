
//--------------------------------------------------------*
// Amirhossein Sabagh | #152956199 | Lab07 | 2020-07-14 --*
//--------------------------------------------------------*

#include <iostream>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

int main(void)
{
    Environment* env = nullptr;
    Connection* conn = nullptr;
    

    //int num;

    string str;
    string usr = "dbs211_202c25";
    string pass = "14013167";
    string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(usr, pass, srv);
        cout << "Connection is successful" << endl;
       
        Statement* stmt = conn->createStatement();

        ResultSet* rs = stmt->executeQuery("SELECT a.employeenumber, a.firstname || ' ' || a.lastname AS Name, b.phone, a.extension FROM employees a, offices b WHERE a.officecode = 1 AND b.officecode = 1 ORDER BY a.employeenumber");

        cout << "********** Employee Report **********" << endl;
        cout << "Employee Report: " << endl;
        
        while (rs->next())
        {
            int id = rs->getInt(1); // get the first column as int
            string name = rs->getString(2);
            string phone = rs->getString(3);
            string extension = rs->getString(4);
            cout << "ID: " << id << "     " << "Name: " << name << "      " << "Phone: " << phone << "      " << "Extension: " << extension << "      " << endl;
        }

        cout << endl;

        stmt = conn->createStatement();
        rs = stmt->executeQuery("SELECT a.employeenumber, a.firstname || ' ' || a.lastname AS Name, b.phone, a.extension FROM employees a INNER JOIN offices b ON a.officecode = b.officecode Where a.jobtitle LIKE '%Manager%' OR a.reportsto IS NULL OR a.reportsto = '1002' OR a.reportsto = '1056' ORDER BY a.employeenumber");

        cout << "Manager Report: " << endl;

        while (rs->next())
        {
            int id = rs->getInt(1); // get the first column as int
            string name = rs->getString(2);
            string phone = rs->getString(3);
            string extension = rs->getString(4);
            cout << "ID: " << id << "     " << "Name: " << name << "      " << "Phone: " << phone << "      " << "Extension: " << extension << "      " << endl;
        }
                       
                                     
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