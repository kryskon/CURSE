#include <string>
#include "registration.cpp"
#include <vector>
using namespace std;

class instructor:public user{
  protected:
    string instructorType; //CS, electrical, mechanical, etc...
    vector<int> classes;

  public:
    instructor(){}
    instructor(string t){instructorType = t;}
    ~instructor(){}

    void setInstructorType(string t){instructorType = t;}
    string getInstructorType(){return instructorType;}

    void viewSchedule(){
        for(vector<int>::iterator ptr = classes.begin(); ptr != classes.end(); ptr++){
          //take crn and lookup in database
          //return class info (students, time, etc)
        }
    }

};
