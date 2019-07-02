#include <string>
#include <iostream>
#include <list>

using namespace std;

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

    virtual int options(){
      //this is where users can choose an action based on user type
      //virtual so each class has it's own appropriate options
    }
};


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

    void Register(){
      int crn;
      cout << "Please enter a course crn: ";
      cin >> crn;
      //search database for crn. Find course and requirements
      //compare prereqs and class sizez. If no issues:
      classes.push_front(crn);
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

    int options(){
      //options here
    }
};

list<student> studentList; //list of all students until database integration

class instructor:public user{
  protected:
    string instructorSubject; //CS, electrical, mechanical, etc...
    vector<int> classes; //listed by CRN code

  public:
    instructor(){}
    instructor(string fn, string ln, string u, string p, string s){firstName = fn, lastName = ln, userName = u, password = p, instructorSubject = s;}
    ~instructor(){}

    void setInstructorSubject(string s){instructorSubject = s;}
    string getInstructorSubject(){return instructorSubject;}

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

list<instructor> instructorList; //list of all instructors until database integration

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

list<course> courseList; //holds all available courses until database integration


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
    int removeCourse(){
      int c;
      cout << "Enter the CRN of the course you wish to remove: ";
      cin >> c;
      for(list<course>::iterator ptr = courseList.begin(); ptr != courseList.end(); ptr++){
        if(ptr->getCRN() == c){
          courseList.erase(ptr);
          cout << "\nCourse successfully removed.\n";
          return 0;
        }
      }
      cout << "Error, course doesn't exist.\n";
      return 0;
    }


    void addStudent(){
      string fn, ln, u, p, m, y;

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

    int options(){
      int userChoice;
      cout << "Enter 1 to add a course\nEnter 2 to remove a course\nEnter 3 to logout\n";
      cin >> userChoice;
      switch(userChoice){
        case 1:
          this->addCourse();
          break;
        case 2:
          this->removeCourse();
          break;
        case 3:
          return 0;
          break;  //need to somehow logout here
      }
      //options here
    }
};

list<admin> adminList; //list of all admins until database integration

list<student>::iterator attemptloginS(string n, string p){
  list<student>::iterator ptr;
  for(ptr = studentList.begin(); ptr != studentList.end(); ptr++){ //search list for matching username
    if((ptr->getUserName() == n) && (ptr->getPassword() == p)){return ptr;} //if match, return pointer
  }
  for(ptr = studentList.begin(); ptr != studentList.end(); ptr++){  //if no match, return NULL pointer
    if(ptr->getUserName() == "NULL"){return ptr;}
  }
}

list<instructor>::iterator attemptloginI(string n, string p){
  list<instructor>::iterator ptr;
  for(ptr = instructorList.begin(); ptr != instructorList.end(); ptr++){ //search list for matching username
    if((ptr->getUserName() == n) && (ptr->getPassword() == p)){return ptr;} //if match, return pointer
  }
  for(ptr = instructorList.begin(); ptr != instructorList.end(); ptr++){  //if no match, return NULL pointer
    if(ptr->getUserName() == "NULL"){return ptr;}
  }
}

list<admin>::iterator attemptloginA(string n, string p){
  list<admin>::iterator ptr;
  for(ptr = adminList.begin(); ptr != adminList.end(); ptr++){ //search list for matching username
    if((ptr->getUserName() == n) && (ptr->getPassword() == p)){return ptr;} //if match, return pointer
  }
  for(ptr = adminList.begin(); ptr != adminList.end(); ptr++){  //if no match, return NULL pointer
    if(ptr->getUserName() == "NULL"){return ptr;}
  }
}
