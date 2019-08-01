#include <iostream>
#include <string>
#include <list>
#include "classes.h"
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

//TO COMPILE: g++ main.cpp -lsqlite3 -std=c++11

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
	int step;
	string sql;


	//begin main loop
	while(!done){
		int logout = 0;
		int userChoice;
		cout << "\n---------------------------------------------\n";
		cout << "Enter 1 to login\nEnter 2 to exit the program\n";
		cin >> userChoice;
		if(userChoice == 1){ //if logging in...
			cout << "Enter your username: ";
			cin >> usrN;
			cout << "Enter your password: ";
			cin >> usrP;

			//begin login process
			query = "SELECT EMAIL, PASSWORD FROM ADMIN WHERE EMAIL = '" + usrN + "';"; //query to find result (email is the same as username)
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
							query = "SELECT * FROM STUDENT WHERE EMAIL = '" + usrN + "';";
							c = query.c_str();
							sqlite3_prepare_v2(DB, c, -1, &res, 0);
							sqlite3_bind_int(res, 1, 3);
							step = sqlite3_step(res);
							if (step == SQLITE_ROW){		//if query actually has a row (i.e match found)
								string QresultU = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 5))); //have to convert const char* to string
								string QresultP = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 6)));
								if (QresultU == usrN && QresultP == usrP){ //successful student login
									cout << "Login Successful\n";
									int Q1 = int(sqlite3_column_int(res, 0));
									string Q2 = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 1)));
									string Q3 = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
									int Q4 = int(sqlite3_column_int(res, 3));
									string Q5 = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 4)));
									student currentStudent(Q1, Q2, Q3, Q4, Q5, QresultU, QresultP); //create new object with all info here to do comparisons
									while(!logout){
										cout << "\nEnter 1 to view all available courses\nEnter 2 to register for courses\nEnter 3 to drop a class\nEnter 4 to list enrolled classes\nEnter 5 to logout\n";
									  cin >> userChoice;
										switch(userChoice){
											case 1: //view all courses
												cout << "\n----------------All Courses----------------\n";
												query = "SELECT * FROM COURSE;";
												sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
												cout << "---------------------------------------------\n";
												break;
											case 2:
												int crn;
												cout << "\nPlease enter the CRN for your desired course: ";
												cin >> crn;
												for (int i = 1; i <= 8; i++){
													query = "SELECT STUDENT" + to_string(i) + " FROM COURSE WHERE CRN = " + to_string(crn) + " AND STUDENT" + to_string(i) + " IS NULL;";
													c = query.c_str();
													sqlite3_prepare_v2(DB, c, -1, &res, 0);
													sqlite3_bind_int(res, 1, 3);
													step = sqlite3_step(res);
													if (step == SQLITE_ROW){
														sql = "UPDATE COURSE SET STUDENT" + to_string(i) + " = " + to_string(currentStudent.getID()) + " WHERE CRN = " + to_string(crn) + ";";
														exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
														if (exit != SQLITE_OK){
																std::cerr << "Error adding class to schedule" << std::endl;
																sqlite3_free(messageError);
														}
														else{
															cout << "Course successfully added to schedule!\n";
															break;
														}
													}
													else
														cout << "Error, class is at full capacity\n";
												}
												break;
											case 3:

												break;
											case 4:
												cout << "\n----------Current Class Schedule-----------\n";
												query = "SELECT * FROM COURSE WHERE STUDENT1 = " + to_string(currentStudent.getID()) + " OR STUDENT2 = " + to_string(currentStudent.getID()) + " OR STUDENT3 = " + to_string(currentStudent.getID()) + " OR STUDENT4 = " + to_string(currentStudent.getID()) + " OR STUDENT5 = " + to_string(currentStudent.getID()) + " OR STUDENT6 = " + to_string(currentStudent.getID()) + " OR STUDENT7 = " + to_string(currentStudent.getID()) + " OR STUDENT8 = " + to_string(currentStudent.getID()) + ";";
												exit = sqlite3_exec(DB, query.c_str(), callback, NULL, &messageError);
												if (exit != SQLITE_OK){
														std::cerr << "Error adding class to schedule" << std::endl;
														sqlite3_free(messageError);
												}
												else{
													cout << "Course successfully added to schedule!\n";
												}
												cout << "---------------------------------------------\n";
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
