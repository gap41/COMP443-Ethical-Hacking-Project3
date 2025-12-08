/**
 * 
 * @file project.c
 * 
 * This is the main project file with the tool to connect to the database
 * 
 * This is a part of the Project 2 submission for the class COMP-443 Ethical Hacking December 2025
 * 
 */


/**********************
 * Includes
 **********************/
#include <stdio.h>
#include "dbSetupScript.h"
#include <sqlite3.h>


int main(){

    createDB();
    populateDB();
    queryDB("SELECT * FROM EMPLOYEES");


    return 0;
}