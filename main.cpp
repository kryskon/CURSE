#include <iostream>
#include <string>
#include <list>
#include "classes.h"

using namespace std;

int main(){
	student nullStudent("NULL", "NULL", "NULL", "NULL", "NULL", "NULL");
	studentList.push_back(nullStudent);
	student newStudent("Will", "Kelsey", "willk", "password1", "Computer Engineer", "Fall 2016");
	studentList.push_front(newStudent);

	instructor nullInstructor("NULL", "NULL", "NULL", "NULL", "NULL");
	instructorList.push_back(nullInstructor);
	instructor newInstructor("Aaron", "Carpenter", "carpentera1", "professor", "APC");
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
	int logout = 0;
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
			user1->options();
		}
	}
	else if(type == 2){ //if user is an instructor...
		while(!logout){
			user2->options();
		}
	}
	else {
		if (user3->getUserName() != "NULL"){ //if user is an admin...
			while(!logout){
				user3->options();
			}
		}
		else {
			cout << "Error, invalid username or password\n";
		}
	}
}
