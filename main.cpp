#include <iostream>
#include <string>
#include <list>
#include "classes.h"

using namespace std;

int main(){
	user nullUser("NULL", "NULL", "NULL", "NULL"); //NULL objects. Very important, don't delete
	userList.push_back(nullUser);
	student nullStudent("NULL", "NULL", "NULL", "NULL", "NULL", "NULL");
	studentList.push_back(nullStudent);
	instructor nullInstructor("NULL", "NULL", "NULL", "NULL", "NULL");
	instructorList.push_back(nullInstructor);
	admin nullAdmin("NULL", "NULL", "NULL", "NULL", "NULL");
	adminList.push_back(nullAdmin);
	admin newAdmin("Nick", "Krysko", "password1", "kryskon", "sysadmin"); //need at least one default admin to start
	adminList.push_front(newAdmin); //make sure all new users get pushed to the front, NOT THE BACK
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
