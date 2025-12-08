/**
 * 
 * @file dbSetupScript.c
 * 
 * This is the source code to create, populate and query the database
 * 
 * This is a part of the Project 2 submission for the class COMP-443 Ethical Hacking December 2025
 * 
 */


/**********************************
 * Includes
 **********************************/
#include "dbSetupScript.h"
#include <stdio.h>
#include <sqlite3.h>

/**********************************
 * Prototypes
 **********************************/
static int callback(void *, int argc, char **argv, char **azColName);

/**********************************
 * Functions
 **********************************/

int createDB(){

    sqlite3 *db;
    char *zErrMsg = 0; //Error message for when executing the sqlite3_execute() function call
    int rc;
    char *sql;
    const char* data = "Callback was called";

    rc = sqlite3_open("employee.db", &db);


    if(rc){
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }else{
        printf("Opened database successfully\n");
    }

    sql = "CREATE TABLE EMPLOYEES(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50)," \
        "SALARY         REAL );";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        printf("Error executing the SQL query : %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        printf("The table has been created\n");
    }

    sqlite3_close(db);

}

int populateDB(){

    sqlite3 *db;
    char *zErrMsg = 0; //Error message for when executing the sqlite3_execute() function call
    int rc;
    char *sql;
    const char* data = "Callback was called";

    rc = sqlite3_open("employee.db", &db);

    sql = "INSERT INTO EMPLOYEES(ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'ANDERS', 34, 'Oslo', 540000 ); " \
         "INSERT INTO EMPLOYEES (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allan', 65, 'Trondheim', 870000 ); "     \
         "INSERT INTO EMPLOYEES (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Olav', 43, 'Revetal', 354000 );" \
         "INSERT INTO EMPLOYEES (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Morten', 28, 'Fredrikstad ', 550000 );";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        printf("Error executing the SQL query : %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        printf("The data has been added\n");
    }

    sqlite3_close(db);

    return 0;
}

int queryDB(char* query){

    sqlite3 *db;
    char *zErrMsg = 0; //Error message for when executing the sqlite3_execute() function call
    int rc;
    char *sql;
    const char* data = "Callback was called";

    rc = sqlite3_open("employee.db", &db);

    sql = query;

    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if(rc != SQLITE_OK){
        printf("Error executing the SQL query : %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        printf("Callback successfully called\n");
    }

    sqlite3_close(db);

    return 0;

}

static int callback(void *, int argc, char **argv, char **azColName){
    for(int i = 0; i < argc; i++){
        if(argv[i] != NULL){
            printf("%s = %s\n", azColName[i], argv[i]);
        }else{
            printf("%s = %s\n", azColName[i], "NULL");
        }
        printf("\n");       
    }

    return 0; 

}