#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "classes.h"

using namespace std;


int main(){
	user nullUser("NULL", "NULL", "NULL", "NULL"); //NULL object. Very important, don't delete
	userList.push_back(nullUser);
	admin newAdmin("Nick", "Krysko", "password1", "kryskon", "sysadmin"); //need at least one default admin to start
	userList.push_front(newAdmin); //make sure all new users get pushed to the front, NOT THE BACK
	string usrN;
	string usrP;
	int logout = 0;
	cout << "Enter your username: ";
	cin >> usrN;
	cout << "Enter your password: ";
	cin >> usrP;
	list<user>::iterator user = attemptlogin(usrN, usrP); //find the user, return it's pointer
	if(user->getUserName()!="NULL"){ //if successfull login:
		while(!logout){
			user->options();
			//start main loop here. This is where the switch statement will go with different options, aka the options() virtual funtion
		}
		//user has logged out. Back to login menu?
	}
	else{ //unsuccessfull login. should put in loop so it gives another attempt instead of stopping here
		cout << "Error, invalid username or password\n";
	}
}
