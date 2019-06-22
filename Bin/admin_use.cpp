#include <string>
#include "registration.cpp"


using namespace std;

class admin:public user{
  protected:
    string title; //sys admin, registrar, etc. May not be necessary

  public:
    admin(){}
    admin(string t){title = t;}
    ~admin(){}


    void viewSchedule(){
        string name;
        cout << "Enter the user name of the student/instructor you wish to view the schedule of: "
        cin >> name;
        for(vector<int>::iterator ptr = classes.begin(); ptr != classes.end(); ptr++){
          //take username and lookup in database
          //return schedule
        }
    }
    void manageClasses(){
      //have access to whole database
      int choice;
      cout << "Enter 1 to add a class\nEnter 2 to delete a class\nEnter 3 to edit a class\n";
      cin >> choice;
      switch(choice){
        case 1:
          int addCRN;
          cout << "Enter the crn of the class you want to add: ";
          cin >> addCRN;
          //add an entry in the database for this course
          //fill in course details (instrutor, capacity, time, etc)
          break;
        case 2:
          int delCRN;
          cout << "Enter the crn of the lass you want to delete: ";
          cin >> delCRN;
          //scan database for matching crn
          //remove course from database if found
          break;
        case 3:
          int editCRN;
          cout << "Enter the crn of the course you wish to edit: ";
          cin >> editCRN;
          //search database and find matching crn
          //specify which attribute to modify
          //make changes
          break;
      }
    }

}
