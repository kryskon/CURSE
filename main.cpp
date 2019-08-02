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
	int crn;
	string sql;
	string title;
	string department;
	string instructor;
	string time;
	string dow;
	string semester;
	string order;
	int year;
	int credits;
	int Q;
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
			query = "SELECT * FROM ADMIN WHERE EMAIL = '" + usrN + "';"; //query to find result (email is the same as username)
			const char *c = query.c_str();
			sqlite3_prepare_v2(DB, c, -1, &res, 0);
			sqlite3_bind_int(res, 1, 3);
			int step = sqlite3_step(res);
			if (step == SQLITE_ROW){		//if query actually has a row (i.e match found)
				string QresultU = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 5))); //have to convert const char* to string
				string QresultP = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 6)));
				if (QresultU == usrN && QresultP == usrP){ //successful admin login
					cout << "Login Successful\n";
					int Q1 = int(sqlite3_column_int(res, 0));
					string Q2 = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 1)));
					string Q3 = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
					string Q4 = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3)));
					string Q5 = string(reinterpret_cast<const char*>(sqlite3_column_text(res, 4)));
					admin currentAdmin(Q1, Q2, Q3, Q4, Q5, QresultU, QresultP); //create new object with all info here to do comparisons
					while(!logout)
					{
						cout << "\nEnter 1 to view courses \nEnter 2 to view rosters\nEnter 3 to create a course\nEnter 4 to delete a course\nEnter 5 to logout\n";
						cin >> userChoice;
						switch(userChoice)
						{
							case 1: //view all courses
								cout << "\n----------------All Courses----------------\n";
								query = "SELECT * FROM COURSE;";
								sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
								cout << "---------------------------------------------\n";
								break;
							case 2: // view rosters
								cout << "\nEnter the CRN for the course roster you'd like to view: ";
								cin >> crn;
								cout << "\n---------------Roster----------------------\n";
								cout << "For course CRN " << crn << ":\n";
								query = "SELECT STUDENT1, STUDENT2, STUDENT3, STUDENT4, STUDENT5, STUDENT6, STUDENT7, STUDENT8 FROM COURSE WHERE CRN = " + to_string(crn) + ";";
								sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
								cout << "\n-------------------------------------------\n";
								break;
							case 3: //create course

								cout << "\nEnter a new CRN (numbers only): ";
								cin >> crn;
								cout << "\nEnter a title for the course: ";
								cin.ignore(); //needed to allow for spaces
								getline(cin, title, '\n');
								cout << "\nEnter a department (ex. BSCO):";
								cin >> department;
								cout << "\nEnter an instructor username: ";
								cin >> instructor;
								cout << "\nEnter a start time: ";
								cin >> time;
								cout << "\nEnter the days of the week with no spaces (MTWRF): ";
								cin >> dow;
								cout << "\nEnter the semester (spring, summer, fall): ";
								cin >> semester;
								cout << "\nEnter the year (2019, 2020, etc): ";
								cin >> year;
								cout << "\nEnter the credits this course is worth (no decimal points): ";
								cin >> credits;
								query = "SELECT ID FROM INSTRUCTOR WHERE EMAIL = '" + instructor + "';";
								sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
								c = query.c_str();
								sqlite3_prepare_v2(DB, c, -1, &res, 0);
								sqlite3_bind_int(res, 1, 3);
								step = sqlite3_step(res);
								if (step == SQLITE_ROW){
									Q = int(sqlite3_column_int(res, 0));

								}
								cout << "MADE IT HERE. ql is : " << Q << endl;
								sql = "INSERT INTO COURSE VALUES(" + to_string(crn) + ", '" + title + "', '" + department + "', '" + instructor + "', '" + time + "', '" + dow + "', '" + semester + "', " + to_string(year) + ", " + to_string(credits) + ", " + to_string(Q) + " , NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);";
								exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
								if (exit != SQLITE_OK) {
				        	std::cerr << "Error creating course." << std::endl;
				        	sqlite3_free(messageError);
							  }
							  else
							  	std::cout << "Course created Successfully!" << std::endl;
								break;
							case 4: //delete a course
								cout << "\nEnter the CRN for the course you wish to delete: ";
								cin >> crn;
								sql = "DELETE FROM COURSE WHERE CRN = " + to_string(crn) + ";";
								exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
								if (exit != SQLITE_OK) {
				        	std::cerr << "Error deleting course." << std::endl;
				        	sqlite3_free(messageError);
							  }
							  else
							  	std::cout << "Course deleted Successfully!" << std::endl;
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
							while(!logout)
							{
								cout << "\nEnter 1 to view rosters \nEnter 2 to view courses\nEnter 3 to logout\n";
								cin >> userChoice;
								switch(userChoice)
								{
									case 1:
										cout << "\n----------------Course Roster----------------\n";
										query = "SELECT STUDENT1, STUDENT2, STUDENT3, STUDENT4, STUDENT5, STUDENT6, STUDENT7, STUDENT8, TITLE FROM COURSE WHERE INSTRUCTOR = '" + usrN + "';";
										sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
										cout << "-----------------------------------------------\n";
										break;
									case 2:
										cout << "\n----------------Courses Taught----------------\n";
										query = "SELECT TITLE FROM COURSE WHERE INSTRUCTOR = '" + usrN + "';";
										sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
										cout << "------------------------------------------------\n";
										break;
									case 3:
										logout = 1;
										break;
								}
							}
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
												cout << "Press 1 to order by CRN, 2 to order by Title, or 3 to order by Instructor: ";
												cin >> userChoice;
												if (userChoice == 1)
													order = "CRN";
												else if (userChoice == 2)
													order = "TITLE";
												else
													order = "INSTRUCTOR";
												cout << "\n----------------All Courses----------------\n";
												query = "SELECT CRN, TITLE, DEPARTMENT, INSTRUCTOR, TIME, DOW, SEMESTER, YEAR, CREDITS FROM COURSE ORDER BY " + order + " ASC;";
												sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
												cout << "---------------------------------------------\n";
												break;
											case 2: //add a course
												crn;
												cout << "\nPlease enter the CRN for your desired course: ";
												cin >> crn;
												for (int i = 1; i <= 8; i++){ //search through DB to find if the course has an empty slot
													query = "SELECT STUDENT" + to_string(i) + " FROM COURSE WHERE CRN = " + to_string(crn) + " AND STUDENT" + to_string(i) + " IS NULL;";
													c = query.c_str();
													sqlite3_prepare_v2(DB, c, -1, &res, 0);
													sqlite3_bind_int(res, 1, 3);
													step = sqlite3_step(res);
													if (step == SQLITE_ROW){ //if empty slot found, add student to that spot
														sql = "UPDATE COURSE SET STUDENT" + to_string(i) + " = '" + currentStudent.getUSRN() + "' WHERE CRN = " + to_string(crn) + ";";
														exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
														if (exit != SQLITE_OK){
																std::cerr << "Error adding class to schedule" << std::endl;
																sqlite3_free(messageError);
																break;
														}
														else{
															cout << "Course successfully added to schedule!\n";
															break;
														}
													}
													if (i == 8){
														cout << "Error, class is at full capacity\n";
													}
												}
												break;
											case 3:	//drop a class
												cout << "Enter the CRN of the course you wish to drop: ";
												cin >> crn;
												for (int i = 1; i <= 8; i++){ //search through DB to find if the course has an empty slot
													query = "SELECT STUDENT" + to_string(i) + " FROM COURSE WHERE CRN = " + to_string(crn) + " AND STUDENT" + to_string(i) + " = '" + currentStudent.getUSRN() + "';";
													c = query.c_str();
													sqlite3_prepare_v2(DB, c, -1, &res, 0);
													sqlite3_bind_int(res, 1, 3);
													step = sqlite3_step(res);
													if (step == SQLITE_ROW){ //if match found, remove student from that course
														sql = "UPDATE COURSE SET STUDENT" + to_string(i) + " = NULL WHERE CRN = " + to_string(crn) + ";";
														exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
														if (exit != SQLITE_OK){
																std::cerr << "Error dropping class" << std::endl;
																sqlite3_free(messageError);
																break;
														}
														else{
															cout << "Course successfully dropped.\n";
															break;
														}
													}
													if (i == 8){
														cout << "You are not currently registered for that class\n";
													}
												}
												break;
											case 4: //print schedule
												cout << "\n----------Current Class Schedule-----------\n";
												query = "SELECT CRN, TITLE, DEPARTMENT, INSTRUCTOR, TIME, DOW, SEMESTER, YEAR, CREDITS FROM COURSE WHERE STUDENT1 = '" + currentStudent.getUSRN() + "' OR STUDENT2 = '" + currentStudent.getUSRN() + "' OR STUDENT3 = '" + currentStudent.getUSRN() + "' OR STUDENT4 = '" + currentStudent.getUSRN() + "' OR STUDENT5 = '" + currentStudent.getUSRN() + "' OR STUDENT6 = '" + currentStudent.getUSRN() + "' OR STUDENT7 = '" + currentStudent.getUSRN() + "' OR STUDENT8 = '" + currentStudent.getUSRN() + "';";
												exit = sqlite3_exec(DB, query.c_str(), callback, NULL, &messageError);
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
