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

    	for (i = 0; i < argc; i++) {
        	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    	}

    	printf("\n");
    	return 0;
}

int main(int argc, char** argv){
	sqlite3* DB;
	string table = "CREATE TABLE COURSE("
                "CRN INT PRIMARY KEY     NOT NULL, "
                "TITLE           TEXT   	NOT NULL, "
                "DEPARTMENT       	  TEXT    	NOT NULL, "
                "INSTRUCTOR     	TEXT    NOT NULL, "
									"TIME					TEXT 				NOT NULL, "
								 	"DOW					TEXT 				NOT NULL, "
									"SEMESTER 	TEXT NOT NULL, "
									"YEAR 			INT NOT NULL, "
									"CREDITS			INT NOT NULL); ";
	int exit = 0;
	exit = sqlite3_open("assignment7.db", &DB);
	char* messageError;
	exit = sqlite3_exec(DB, table.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK){
		cerr << "Error Create Table" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Table created successfully" << endl;


		string sql("INSERT INTO COURSE VALUES(5436, 'Computer Architecture', 'Computer Engineering', 'Alan Turing', '5:00', 'WF', 'Summer', 2019, 3);");

	 exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

 if (exit != SQLITE_OK) {
				 cerr << "Error Insert" << endl;
				 sqlite3_free(messageError);
		 }
		 else
				 cout << "Records created Successfully!" << endl;


		 sqlite3_open("assignment7.db", &DB);
	 	string query = "SELECT * FROM COURSE;";
	 		cout << endl << query << endl;

	 		sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

	student nullStudent("NULL", "NULL", "NULL", "NULL", "NULL", "NULL");
	studentList.push_back(nullStudent);
	student newStudent("Will", "Kelsey", "willk", "password1", "Computer Engineer", "Fall 2016");
	list<int> studentClasses; //gives this student a list of classes to test with
	studentClasses.push_front(12345);
	studentClasses.push_front(66666);
	newStudent.setClasses(studentClasses);
	studentList.push_front(newStudent);

	instructor nullInstructor("NULL", "NULL", "NULL", "NULL", "NULL");
	instructorList.push_back(nullInstructor);
	instructor newInstructor("Aaron", "Carpenter", "carpentera1", "professor", "APC");
	list<int> carpenterClasses; //gives this instructor a basic course list to test with
	carpenterClasses.push_front(12345);
	carpenterClasses.push_front(66666);
	newInstructor.setClasses(carpenterClasses);
	instructorList.push_front(newInstructor);

	admin nullAdmin("NULL", "NULL", "NULL", "NULL", "NULL");
	adminList.push_back(nullAdmin);
	admin newAdmin("Nick", "Krysko", "password1", "kryskon", "sysadmin"); //need at least one default admin to start
	adminList.push_front(newAdmin); //make sure all new users get pushed to the front, NOT THE BACK

	course nullCourse(00000, "NULL", "NULL", "NULL");
	courseList.push_back(nullCourse);
	course newCourse0(12345, "2016", "Computer Stuff", "Aaron Carpenter");
	courseList.push_front(newCourse0);
	course newCourse1(66666, "2016", "More Computer Stuff", "Aaron Carpenter");
	courseList.push_front(newCourse1);
	course newCourse2(77777, "2016", "Some Computer Stuff", "Aaron Carpenter");
	courseList.push_front(newCourse2);
	course newCourse3(13579, "2016", "Just Computer Stuff", "Aaron Carpenter");
	courseList.push_front(newCourse3);

	string usrN;
	string usrP;
	list<student>::iterator user1; //potential user type student
	list<instructor>::iterator user2; //potential user type instructor
	list<admin>::iterator user3; //potential user type admin
	int type;
	int done = 0;
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
			user1 = attemptloginS(usrN, usrP); //cehck if user is a student
			if (user1->getUserName()=="NULL"){
				user2 = attemptloginI(usrN, usrP); //check if user is an instructor
					if(user2->getUserName()=="NULL"){
						user3 = attemptloginA(usrN, usrP); //check if user is an admin
						type = 3;
					}
					else{type = 2;}
			}
			else{type = 1;}
			if(type == 1){ //if user is a student...
				while(!logout){
					logout = user1->options();
				}
			}
			else if(type == 2){ //if user is an instructor...
				while(!logout){
					logout = user2->options();
				}
			}
			else {
				if (user3->getUserName() != "NULL"){ //if user is an admin...
					while(!logout){
						logout = user3->options();
					}
				}
				else {
					cout << "Error, invalid username or password\n";
				}
			}
		}
		else done = 1; //exit program
	}
}
