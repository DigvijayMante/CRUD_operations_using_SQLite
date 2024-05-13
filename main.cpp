#include<iostream>
#include<string>
#include <limits>
#include"sqlite3.h"

// Callback function for SELECT queries
int selectCallback(void* data, int argc, char** argv, char** azColName) {
    int i;
    std::cout << "--------------------------" << std::endl;
    for (i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
    return 0;
}

int main() 
{
    sqlite3* db;
    char* errMsg = nullptr;


    // Open the database
    int rc = sqlite3_open("Digvijay.db", &db);
    if (rc) 
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Create table
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Contacts("
        "EMP_ID INTEGER PRIMARY KEY ,"
        "Empolyee_Name TEXT NOT NULL,"
        "Empolyee_Phone TEXT NOT NULL);";
    
    rc = sqlite3_exec(db, createTableSQL, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) 
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else 
    {
        std::cout << "Table created successfully." << std::endl;
    }


    int iCounter = 0, iChoice = 1;

    char chInsertSQL[500] = { 0 };
    short iEmpId = 0;
    long lEmpNumber;
    std::string sEmpName;

    while(iChoice != 9)
    { 
        std::cout << "\n#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#   Select below one     #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#  ";
        std::cout << "\n1. INSERT";
        std::cout << "\n2. UPDATE";
        std::cout << "\n3. SELECT";
        std::cout << "\n4. DELETE";
        std::cout << "\n9. EXIT";
        std::cout << "\nEnter your choice :: ";
        std::cin >> iChoice;

        switch(iChoice)
        {
           case 1 :
               // Insert data
               std::cout << "\nEnter Employee ID ::  ";
               std::cin >> iEmpId;

               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               std::cout << "\nEnter Employee Name ::  ";
               std::getline(std::cin, sEmpName);

               std::cout << "\nEnter Employee Number ::  ";
               std::cin >> lEmpNumber;

               sprintf_s(chInsertSQL,sizeof(chInsertSQL),"INSERT INTO Contacts (EMP_ID, Empolyee_Name, Empolyee_Phone) VALUES (%d,'%s', '%ld');",iEmpId,sEmpName.c_str(),lEmpNumber);

               rc = sqlite3_exec(db, chInsertSQL, nullptr, 0, &errMsg);
               if (rc != SQLITE_OK) 
               {
                   std::cerr << "SQL error: " << errMsg << std::endl;
                   sqlite3_free(errMsg);
               }
               else 
               {
                   std::cout << "Data inserted successfully." << std::endl;
               }

               break;

           case 2:

              sprintf_s(chInsertSQL,sizeof(chInsertSQL),"SELECT * FROM Contacts;");
               rc = sqlite3_exec(db, chInsertSQL, selectCallback, nullptr, &errMsg);
               if (rc != SQLITE_OK)
               {
                   std::cerr << "SQL error: " << errMsg << std::endl;
                   sqlite3_free(errMsg);
               }

               std::cout << "\n Please enter valid data(data present table*) which you want to update";
               // Update data
               std::cout << "\nPlease Enter Employee ID First ::  ";
               std::cin >> iEmpId;
               std::cout << "\nEnter Updated Employee Name ::  ";
               std::getline(std::cin, sEmpName);
               std::cout << "\nEnter Updated Employee Number ::  ";
               std::cin >> lEmpNumber;

               //const char* updateSQL = "UPDATE Contacts SET Empolyee_Phone='9876543210' WHERE Empolyee_Name ='John Doe';";
               sprintf_s(chInsertSQL, sizeof(chInsertSQL), "UPDATE Contacts SET Phone='%ld' and  Name='%s' where EMP_ID = %d;", lEmpNumber, sEmpName.c_str(), iEmpId);
               rc = sqlite3_exec(db, chInsertSQL, nullptr, 0, &errMsg);
               if (rc != SQLITE_OK) 
               {
                   std::cerr << "SQL error: " << errMsg << std::endl;
                   sqlite3_free(errMsg);
               }
               else 
               {
                   std::cout << "Data updated successfully." << std::endl;
               }

               break;
           case 3:
               // Select data
               sprintf_s(chInsertSQL,sizeof(chInsertSQL),"SELECT * FROM Contacts;");
               rc = sqlite3_exec(db, chInsertSQL, selectCallback, nullptr, &errMsg);
               if (rc != SQLITE_OK) 
               {
                   std::cerr << "SQL error: " << errMsg << std::endl;
                   sqlite3_free(errMsg);
               }
               
               break;
           case 4:
               sprintf_s(chInsertSQL, sizeof(chInsertSQL), "SELECT * FROM Contacts;");
               rc = sqlite3_exec(db, chInsertSQL, selectCallback, nullptr, &errMsg);
               if (rc != SQLITE_OK)
               {
                   std::cerr << "SQL error: " << errMsg << std::endl;
                   sqlite3_free(errMsg);
               }

               std::cout << "\nEnter Employee ID To Be Deleted::  ";
               std::cin >> iEmpId;
               // Delete data
               sprintf_s(chInsertSQL,sizeof(chInsertSQL),"DELETE FROM Contacts WHERE EMP_ID='%d';", iEmpId);
               rc = sqlite3_exec(db, chInsertSQL, nullptr, 0, &errMsg);
               if (rc == SQLITE_DONE) 
               {
                   std::cout << "No record found with Employee ID " << iEmpId << std::endl;
               }
               else if (rc != SQLITE_OK) 
               {
                   std::cerr << "SQL error: " << errMsg << std::endl;
                   sqlite3_free(errMsg);
               }
               else
               {
                   std::cout << "Data deleted successfully." << std::endl;
               }
               break;
           case 9:
               std::cout << "\nOkk... Bye ;)";
               
               break;
           default:
               std::cout << "\nooops.... Wrong Choice";
               
               break;
        }
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}

