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

    /*
    void setFirstName(string fn){firstName = fn;}
    string getFirstName(){return firstName;}
    void setLastName(string ln){lastName = ln;}
    void setUserName(string u){userName = u;}
    string getUserName(){return userName;}
    void setPassword(string p){password = p;}
    string getPassword(){return password;}
    */
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
    //list<student> students;

  public:
    course(){}
    course(int c, int cr, int yr, string t, string d, string i, string ti, string days, string sem){CRN = c, credits = cr, year = yr, title = t, department = d, instructor = i, time = ti, dow = days, semester = sem;}
    ~course(){}

    /*
    void setCRN(int c){CRN = c;}
    int getCRN(){return CRN;}
    void setMinYear(string y){minYear = y;}
    string getMinYear(){return minYear;}
    void setSubject(string s){subject = s;}
    string getSubject(){return subject;}
    */

};

class student:public user{
  protected:
    string major;
    int gradYear;

  public:
    student(){}
    student(int i, string fn, string ln, int y, string m, string e, string p){ID = i, firstName = fn, lastName = ln, email = e, password = p, major = m, gradYear = y;}
    ~student(){}

    /*
    void setMajor(string m){major = m;}
    string getMajor(){return major;}
    void setYear(string y){year = y;}
    string getYear(){return year;}
    void setClasses(list<int> c){classes = c;}
    list<int> getClasses(){return classes;}
    */


    void Register(){
      int crn;
      cout << "Please enter a course crn: ";
      cin >> crn;
      //search database for crn. Find course and requirements
      //compare prereqs and class sizez. If no issues:

    }

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

    /*()
    void setInstructorSubject(string s){instructorSubject = s;}
    string getInstructorSubject(){return instructorSubject;}
    void setClasses(list<int> c){classes = c;}
    list<int> getClasses(){return classes;}
    */

    void viewRoster(){ //may need to change completely when databases get implemented.
      //do db stuff
    }

    void viewClasses(){
      cout << "Currently teaching classes: ";
      //do db stuff
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
      /*
      string sql("INSERT INTO PROGRAMMER VALUES(1, 'ADA', 'LOVELACE', 1815);"
               	"INSERT INTO PROGRAMMER VALUES(2, 'GRACE', 'HOPPER', 1906);"
		              "INSERT INTO PROGRAMMER VALUES(3, 'MARY KENNETH', 'KELLER', 1913);"
               	"INSERT INTO PROGRAMMER VALUES(4, 'EVELYN', 'BOYD GRANVILLE', 1924);"
		              "INSERT INTO PROGRAMMER VALUES(5, 'CAROL', 'SHAW', 1955);"
		   );
    */
    //may want to avoid doing db stuff in header file. instead pass variables through functions and alter in main??

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
