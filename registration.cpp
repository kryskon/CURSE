#include <iostream>
#include <string>
#include <list>

class user{
  protected:
    std::string name;
    std::string userName;
    std::string password; //storing in plain text for now
  public:
    user() {}
    user(std::string n):name(n){}
    ~user(){}

    void registerClass();

    void setName(std::string n){name = n;}
    std::string getName(){return name;}
    void setUserName(std::string u){userName = u;}
    std::string getUserName(){return userName;}
    void setPassword(std::string p){password = p;}
    std::string getPassword(){return password;}
};

class student:public user{
  protected:
    std::string major;
    std::int year; //freshman, sophmore, etc
  public:


    void set


};

class instructor:public user{
  protected:
    std::string instructorType; //CS, electrical, etc...


};

class admin:public user{
  protected:
  public:


}
