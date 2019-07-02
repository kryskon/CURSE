#include <string>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class course{
  protected:
    int CRN;
    string minYear, subject, instructorUsername; //must be junior, senior, etc to register for this class
    list<student> students;

  public:
    course(){}
    course(int c, string y, string s, string i){CRN = c, minYear = y, subject = s, instructorUsername = i;}
    ~course(){}

    void setCRN(int c){CRN = c;}
    int getCRN(){return CRN;}
    void setMinYear(string y){minYear = y;}
    string getMinYear(){return minYear;}
    void setSubject(string s){subject = s;}
    string getSubject(){return subject;}

};

class user{
  protected:
    string firstName, lastName, userName, password;

  public:
    user(){}
    user(string fn, string ln, string u, string p):firstName(fn), lastName(ln), userName(u), password(p){}
    ~user(){}

    void registerClass();

    void setFirstName(string fn){firstName = fn;}
    string getFirstName(){return firstName;}
    void setLastName(string ln){lastName = ln;}
    void setUserName(string u){userName = u;}
    string getUserName(){return userName;}
    void setPassword(string p){password = p;}
    string getPassword(){return password;}

    virtual void options(){
      //this is where users can choose an action based on user type
      //virtual so each class has it's own appropriate options
    }
};

list<user> userList; //holds all users until database integration
list<course> courseList; //holds all available courses until database integration

class student:public user{
  protected:
    string major, year;
    list<int> classes;

  public:
    student(){}
    student(string fn, string ln, string u, string p, string m, string y){firstName = fn, lastName = ln, userName = u, password = p, major = m, year = y;}
    ~student(){}

    void setMajor(string m){major = m;}
    string getMajor(){return major;}
    void setYear(string y){year = y;}
    string getYear(){return year;}

    void Register(){ //put inside of class?
      int crn;
      cout << "Please enter a course crn: ";
      cin >> crn;
      //search database for crn. Find course and requirements
      //compare prereqs and class sizez. If no issues:
      classes.push_back(crn);
    }

    void viewSchedule(){
        for(list<int>::iterator ptr = classes.begin(); ptr != classes.end(); ptr++){
          //take crn and lookup in database
          //return class info (students, time, etc)
        }
    }

    void dropClass(){
      int crn;
      cout << "Please enter a course crn: ";
      cin >> crn;
      for(list<int>::iterator ptr = classes.begin(); ptr != classes.end(); ptr++){
        if (crn == *ptr){
          classes.erase(ptr);
        }
      }
    }

    void options(){
      //options here
    }
};

class instructor:public user{
  protected:
    string instructorSubject; //CS, electrical, mechanical, etc...
    vector<int> classes; //listed by CRN code

  public:
    instructor(){}
    instructor(string s){instructorSubject = s;}
    ~instructor(){}

    void setInstructorType(string s){instructorSubject = s;}
    string getInstructorType(){return instructorType;}

    void viewSchedule(){
        for(vector<int>::iterator ptr = classes.begin(); ptr != classes.end(); ptr++){
          //take crn and lookup in database
          //return class info (students, time, etc)
        }
    }

    void options(){
      //options here
    }
};

class admin:public user{
  protected:
    string title; //sys admin, registrar, etc. May not be necessary

  public:
    admin(){}
    admin(string fn, string ln, string p, string u, string t){firstName = fn, lastName = ln, userName = u, password = p, title = t;}
    ~admin(){}

    void viewSchedule(){
        string name;
        cout << "Enter the user name of the student/instructor you wish to view the schedule of: ";
        cin >> name;
        //scan for user. view thier schedule
    }
    /*
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
    */
    void addCourse(){
      int c;
      string y, s, i;
      cout << "Enter a CRN: ";
      cin >> c;
      cout << "\nEnter a minimum year requirement (freshman, sophmore, junior, or senior): ";
      cin >> y;
      cout << "\nEnter the course subject (history, math, etc): ";
      cin >> s;
      cout << "\nEnter an instructor username: ";
      cin >> i;
      course newCourse(c, y, s, i);
      courseList.push_front(newCourse);

    }
    void removeCourse(){
      int c;
      cout << "Enter the CRN of the course you wish to remove: ";
      cin >> c;
      for(list<course>::iterator ptr = courseList.begin(); ptr != courseList.end(); ptr++){
        if(ptr->getCRN() == c){
          courseList.erase(ptr);
          cout << "\nCourse successfully removed.\n";
        }
      }
    }


    void addStudent(){
      string fn, ln, u, p, m y;

      cout << "Enter a first name: ";
      cin >> fn;
      cout << "\nEnter a last name: ";
      cin >> ln;
      cout << "\nEnter a username: ";
      cin >> u;
      cout << "\nEnter a password: ";
      cin >> p;
      student newStudent(fn, ln, u, p, m , y);
      userList.push_front(newStudent); //always push to front
    }

    void options(){
      //options here
    }
};



list<user>::iterator attemptlogin(string n, string p){ //return a pointer to some object in the list
  list<user>::iterator ptr;
  for(ptr = userList.begin(); ptr != userList.end(); ptr++){ //search list for matching username
    if((ptr->getUserName() == n) && (ptr->getPassword() == p)){return ptr;} //if match, return pointer
  }
  for(ptr = userList.begin(); ptr != userList.end(); ptr++){  //if no match, return NULL pointer
    if(ptr->getUserName() == "NULL"){return ptr;}
  }
}
