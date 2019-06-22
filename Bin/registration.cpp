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
