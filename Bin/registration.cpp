#include <iostream>
#include <string>
#include <list>

using namespace std;
class user{
  protected:
    int clearanceLevel; //optional. might not need
    string name;
    string userName;
    string password; //storing in plain text for now
  public:
    user(){}
    user(int c, string n, string u, string p ):clearanceLevel(c), name(n), userName(u), password(p){}
    ~user(){}

    void registerClass();

    void setName(string n){name = n;}
    string getName(){return name;}
    void setUserName(string u){userName = u;}
    string getUserName(){return userName;}
    void setPassword(string p){password = p;}
    string getPassword(){return password;}
};

int attemptlogin(string u, string p){ //called somewhere at the beginning of main
  if (u == usr.getUserName() && p == usr.getPassword()){return 1;}
  else {return 0;}
}
