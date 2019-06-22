#include <iostream>
#include <string>

class student:public user{
  protected:
    std::string major;
    int year; //freshman, sophmore, etc
  public:
    student(){}
    student(std::string m, int y){major = m, year = y;}
    ~student(){}


    void setMajor(std::string m){major = m;}
    std::string getMajor(){return major;}
    void setYear(int y){year = y;}
    int getYear(){return year;}

    void print(){
      std::cout << getMajor() << getYear() << std::endl;
    }

};
