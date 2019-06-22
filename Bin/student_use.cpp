#include <string>

using namespace std;

class student:public user{
  protected:
    string major;
    int year; //freshman, sophmore, etc
  public:
    student(){}
    student(string m, int y){major = m, year = y;}
    ~student(){}


    void setMajor(string m){major = m;}
    string getMajor(){return major;}
    void setYear(int y){year = y;}
    int getYear(){return year;}

    void print(){
      std::cout << getMajor() << getYear() << std::endl;
    }

};


weawefadsgfjawergoawrga
tHIUWEpoijaoieshfaoesifjisefnojwaehfiubevi;brbdlnab