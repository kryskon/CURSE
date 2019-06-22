#include <string>
#include <iostream>
#include <vector>
#include ""

using namespace std;

class student:public user{
  protected:
    string major;
    vector<int> classes;
    vector<string> priorCourses; //used to check for prerequisites
    int year; //freshman, sophmore, etc
  public:
    student(){}
    student(string m, int y, vector<int> crn, vector<string> pc){major = m, year = y, classes = crn, priorCourses = pc}
    ~student(){}

    void setMajor(string m){major = m;}
    string getMajor(){return major;}
    void setYear(int y){year = y;}
    int getYear(){return year;}

    void print(){
      cout << getMajor() << getYear() << endl;
    }

    void register(){ //put inside of class?
      int crn;
      cout << "Please enter a course crn: ";
      cin >> crn;
      //search database for crn. Find course and requirements
      //compare prereqs and class sizez. If no issues:
      classes.push_back(crn);
    }

    void viewSchedule(){
        for(vector<int>::iterator ptr = classes.begin(); ptr != classes.end(); ptr++){
          //take crn and lookup in database
          //return class info (students, time, etc)
        }
    }

    void dropClass(){
      int crn;
      cout << "Please enter a course crn: ";
      cin >> crn;
      for(vector<int>::iterator ptr = classes.begin(); ptr != classes.end(); ptr++){
        if (crn == *ptr){
          classes.erase(ptr)
        }
      }
    }

};
