#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <stdio.h>
#include <sqlite3.h>

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

class course{
  protected:
    int CRN;
    string minYear, subject, instructorUsername; //must be junior, senior, etc to register for this class
    //list<student> students;

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
    void setClasses(list<int> c){classes = c;}
    list<int> getClasses(){return classes;}

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

    void listCourses(){
      cout << "Availible courses: ";
      for (list<course>::iterator it = courseList.begin(); it != courseList.end(); it++)
        cout << (it->getCRN()) << ' ';
        cout << '\n';
    }

    void currentEnrolled(){
      cout << "Enrolled courses: ";
      for (list<int>::iterator it = classes.begin(); it != classes.end(); it++)
        cout << (*it) << ' ';
        cout << '\n';
    }

    int options(){
      int userChoice;
      cout << "\nEnter 1 to view courses\nEnter 2 to register for courses\nEnter 3 to drop a class\nEnter 4 to list enrolled classes\nEnter 5 to logout\n";
      cin >> userChoice;
      switch(userChoice){
        case 1:
          this->listCourses();
          break;
        case 2:
          this->Register();
          break;
        case 3:
          this->dropClass();
          break;
        case 4:
          this->currentEnrolled();
        case 5:
          return 1;
          break;  //need to somehow logout here
      }
      return 0;
    }
};

list<student> studentList; //list of all students until database integration

class instructor:public user{
  protected:
    string instructorSubject; //CS, electrical, mechanical, etc...
    list<int> classes; //listed by CRN code

  public:
    instructor(){}
    instructor(string fn, string ln, string u, string p, string s){firstName = fn, lastName = ln, userName = u, password = p, instructorSubject = s;}
    ~instructor(){}

    void setInstructorSubject(string s){instructorSubject = s;}
    string getInstructorSubject(){return instructorSubject;}
    void setClasses(list<int> c){classes = c;}
    list<int> getClasses(){return classes;}

    void viewRoster(){ //may need to change completely when databases get implemented.
      for(list<int>::iterator it = classes.begin(); it != classes.end(); it++){  //start with first class
        cout << "\nIn course " << *it << ": ";
        for(list<student>::iterator ptr = studentList.begin(); ptr != studentList.end(); ptr++){ //scan for students
          if(ptr->getUserName() != "NULL"){
            list<int> slist = ptr->getClasses();
            for(list<int>::iterator ptr2 = slist.begin(); ptr2 != slist.end(); ptr2++){ //scan for students courses
              if(*ptr2 == *it){  //if match, output username;
                cout << ptr->getUserName() << endl;
              }
            }
          }
        }
      }
    }

    void viewClasses(){
      cout << "Currently teaching classes: ";
      for(list<int>::iterator it = classes.begin(); it != classes.end(); it++){
        cout << *it << " ";
      }
      cout << endl;
    }

    int options(){
      int userChoice;
      cout << "\nEnter 1 to view roster\nEnter 2 to view classes\nEnter 3 to logout\n";
      cin >> userChoice;
      switch(userChoice){
        case 1:
          this->viewRoster();
          break;
        case 2:
          this->viewClasses();
          break;
        case 3:
          return 1;
          break;  //need to somehow logout here
      }
      return 0;
    }
};

list<instructor> instructorList; //list of all instructors until database integration

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
      string sql("NSERT INTO PROGRAMMER VALUES(1, 'ADA', 'LOVELACE', 1815);"
               	"INSERT INTO PROGRAMMER VALUES(2, 'GRACE', 'HOPPER', 1906);"
		              "INSERT INTO PROGRAMMER VALUES(3, 'MARY KENNETH', 'KELLER', 1913);"
               	"INSERT INTO PROGRAMMER VALUES(4, 'EVELYN', 'BOYD GRANVILLE', 1924);"
		              "INSERT INTO PROGRAMMER VALUES(5, 'CAROL', 'SHAW', 1955);"
		);

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
      studentList.push_front(newStudent); //always push to front
    }

    int options(){
      int userChoice;
      cout << "\nEnter 1 to add a course\nEnter 2 to remove a course\nEnter 3 to logout\n";
      cin >> userChoice;
      switch(userChoice){
        case 1:
          this->addCourse();
          break;
        case 2:
          this->removeCourse();
          break;
        case 3:
          return 1;
          break;  //need to somehow logout here
      }
      return 0;
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
