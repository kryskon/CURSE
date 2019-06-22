#include <iostream>
#include <string>
#include <list>

class user{
  protected:
    int clearanceLevel;
    std::string name;
    std::string userName;
    std::string password; //storing in plain text for now
  public:
    user(){}
    user(int c, std::string n, std::string u, std::string p ):clearanceLevel(c), name(n), userName(u), password(p){}
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
    student(){}
    student(std::string m, int y){major = m, year = y;}
    ~student(){}

    void setMajor(std::string m){major = m;}
    std::string getMajor(){return major;}
    void setYear(int y){year = y;}
    int getYear(){return year;}
};

class instructor:public user{
  protected:
    std::string instructorType; //CS, electrical, etc...
  public:



};

class admin:public user{
  protected:

  public:


}
