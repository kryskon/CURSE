#include <string>
#include <iostream>
#include <vector>
#include ""

using namespace std;

class student:public user{
  protected:
    string major;
    vector<int> classes;
    int year; //freshman, sophmore, etc
  public:
    student(){}
    student(string m, int y, vector<int> crn){major = m, year = y;}
    ~student(){}

    void setMajor(string m){major = m;}
    string getMajor(){return major;}
    void setYear(int y){year = y;}
    int getYear(){return year;}

    void print(){
      cout << getMajor() << getYear() << endl;
    }

    void register(string m, int y){ //put inside of class?
      int crn;
      cout << "Please enter a course crn: ";
      cin >> crn;
      //search database for crn. Find course and requirements
      //compare prereqs and class sizez. If no issues:
      classes.push_back(crn);
    }

};
