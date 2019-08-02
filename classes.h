#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

class user{
  protected:
    int ID;
    string firstName, lastName, password, email;

  public:
    user(){}
    user(int i, string fn, string ln, string e, string p):ID(i), firstName(fn), lastName(ln), email(e), password(p){}
    ~user(){}

    void registerClass();

    int getID(){return ID;}
    string getUSRN(){return email;}
    virtual int options(){
      //this is where users can choose an action based on user type
      //virtual so each class has it's own appropriate options
    }
};

class course{
  protected:
    int CRN, credits, year;
    string title, department, instructor, time, dow, semester; //must be junior, senior, etc to register for this class

  public:
    course(){}
    course(int c, int cr, int yr, string t, string d, string i, string ti, string days, string sem){CRN = c, credits = cr, year = yr, title = t, department = d, instructor = i, time = ti, dow = days, semester = sem;}
    ~course(){}


};

class student:public user{
  protected:
    string major;
    int gradYear;

  public:
    student(){}
    student(int i, string fn, string ln, int y, string m, string e, string p){ID = i, firstName = fn, lastName = ln, email = e, password = p, major = m, gradYear = y;}
    ~student(){}





    void dropClass(){
      int crn;
      cout << "Please enter a course crn: ";
      cin >> crn;
      //do db stuff
    }

    void listCourses(){
      cout << "Availible courses: ";
      //do db stuff
    }

    void currentEnrolled(){
      cout << "Enrolled courses: ";
      //do db stuff
    }


};


class instructor:public user{
  protected:
    string title, department; //CS, electrical, mechanical, etc...
    int hireYear;

  public:
    instructor(){}
    instructor(string fn, string ln, string e, string p, string t, string d, int hy){firstName = fn, lastName = ln, email = e, password = p, title = t, department = d, hireYear = hy;}
    ~instructor(){}



    void viewRoster(){ //may need to change completely when databases get implemented.
      //do db stuff
    }

    void viewClasses(){
      cout << "Currently teaching classes: ";
      //do db stuff
    }


};

class admin:public user{
  protected:
    string title, office; //sys admin, registrar, etc. May not be necessary

  public:
    admin(){}
    admin(int i, string fn, string ln, string t, string o, string p, string e){firstName = fn, lastName = ln, email = e, password = p, title = t, office = o, ID = i;}
    ~admin(){}

    void viewSchedule(){
        string name;
        cout << "Enter the user name of the student/instructor you wish to view the schedule of: ";
        cin >> name;
        //do db stuff
    }

    void addCourse(){
      int c, cr, yr;
      string t, d, i, ti, days, sem;
      cout << "Enter a CRN: ";
      cin >> c;
      cout << "Enter # of credits: ";
      cin >> cr;
      cout << "\nEnter the year: ";
      cin >> yr;
      cout << "\nEnter the course title: ";
      cin >> ti;
      cout << "\nEnter department: ";
      cin >> d;
      cout << "\nEnter instructor email (without @wit.edu): ";
      cin >> i;
      cout << "\nEnter the class time: ";
      cin >> ti;
      cout << "\nEnter the days of the week the class will take place: ";
      cin >> days;
      cout << "\nEnter the semester: ";
      cin >> sem;
      course newCourse(c, cr, yr, t, d, i, ti, days, sem);


    }
    int removeCourse(){
      int c;
      cout << "Enter the CRN of the course you wish to remove: ";
      cin >> c;
      //do db stuff
      return 0;
    }


    void addStudent(){
      string fn, ln, e, p, m;
      int y;

      cout << "Enter a first name: ";
      cin >> fn;
      cout << "\nEnter a last name: ";
      cin >> ln;
      cout << "\nEnter an email (without @wit.edu on the end): ";
      cin >> e;
      cout << "\nEnter a password: ";
      cin >> p;
      cout << "\nEnter a major: ";
      cin >> m;
      cout << "\nEnter a graduation year: ";
      cin >> y;
      //do db stuff
    }

    
};
