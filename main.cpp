#include <iostream>
#include <string>
#include <list>
#include "classes.h"
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{ 				// number of things to print; query result to print; query column name;
	int i;

    	for (i = 0; i < argc; i++){
        	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    	}

    	printf("\n");
    	return 0;
}

int main(int argc, char** argv){
	sqlite3* DB;
	sqlite3_stmt *res;
	int exit = 0;
	sqlite3_open("assignment7.db", &DB); //open database
	char* messageError;

	string query;
	string usrN;
	string usrP;
	int type;
	int done = 0;
	int userChoice = 0;

	//begin main loop
	while(!done){
		int logout = 0;
		int userChoice;
		cout << "Enter 1 to login\nEnter 2 to exit the program\n";
		cin >> userChoice;
		if(userChoice == 1){ //if logging in...
			cout << "Enter your username: ";
			cin >> usrN;
			cout << "Enter your password: ";
			cin >> usrP;

			//begin login process
			query = "SELECT EMAIL, PASSWORD FROM ADMIN WHERE EMAIL = '" + usrN + "';"; //query to find result
			const char *c = query.c_str();
			sqlite3_prepare_v2(DB, c, -1, &res, 0);
			sqlite3_bind_int(res, 1, 3);
			int step = sqlite3_step(res);
			if (step == SQLITE_ROW){		//if query actually has a row (i.e match found)
				string QresultU = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 0))); //have to convert const char* to string
				string QresultP = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 1)));
				if (QresultU == usrN && QresultP == usrP){ //successful admin login
					cout << "Login Successful\n";
				}
				else
					cout << "invalid password\n";
			}
			else{
				if(step != SQLITE_ROW){
					query = "SELECT EMAIL, PASSWORD FROM INSTRUCTOR WHERE EMAIL = '" + usrN + "';";
					c = query.c_str();
					sqlite3_prepare_v2(DB, c, -1, &res, 0);
					sqlite3_bind_int(res, 1, 3);
					int step = sqlite3_step(res);
					if (step == SQLITE_ROW){		//if query actually has a row (i.e match found)
						string QresultU = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 0))); //have to convert const char* to string
						string QresultP = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 1)));
						if (QresultU == usrN && QresultP == usrP){ //successful instructor login
							cout << "Login Successful\n";
						}
						else
							cout << "Invalid Password\n";
					}
					else{
						if(step != SQLITE_ROW){
							query = "SELECT EMAIL, PASSWORD FROM STUDENT WHERE EMAIL = '" + usrN + "';";
							c = query.c_str();
							sqlite3_prepare_v2(DB, c, -1, &res, 0);
							sqlite3_bind_int(res, 1, 3);
							int step = sqlite3_step(res);
							if (step == SQLITE_ROW){		//if query actually has a row (i.e match found)
								string QresultU = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 0))); //have to convert const char* to string
								string QresultP = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 1)));
								if (QresultU == usrN && QresultP == usrP){ //successful student login
									cout << "Login Successful\n";
									while(!logout){
										cout << "\nEnter 1 to view all available courses\nEnter 2 to register for courses\nEnter 3 to drop a class\nEnter 4 to list enrolled classes\nEnter 5 to logout\n";
									  cin >> userChoice;
										switch(userChoice){
											case 1: //view all courses
												query = "SELECT * FROM COURSE;";
												sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
												break;
											case 5:
												logout = 1;
												break;

										}
									}
								}
								else
									cout << "invalid password\n";
							}
							else
								cout << "Invalid username\n";
						}
					}
				}
			}
		}
		else
			done = 1; //exit program
	}
	sqlite3_close(DB);
	return 0;
}
