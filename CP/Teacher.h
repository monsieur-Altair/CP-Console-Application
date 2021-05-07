#pragma once
#include "Student.h"

class Teacher : public User
{
    string subject;
    shared_ptr<list<int>> ptrGroupList;
    enum MenuChoice
    {
        CREATE_TEST = 1,
        DELETE_TEST,
        VIEW_OWN_INF,
        EDIT_TEST,
        VIEW_ALL_AVAIBLE_TEST,
        VIEW_ALL_STUDENTS,
        VIEW_ONE_STUDENT,
        VIEW_ONE_TEST_FULLY, 
        SORT_STUDENTS_BY_GROUPS,
        SORT_STUDENT_ALPHABETICAL
    };
    enum QuestionMenu
    {
        EXIT,
        DELETE,
        CHANGE_QUESTION,
        CHANGE_ANSWER_OPTION,
        CHANGE_CORRECT_ANSWER,
        CHANGE_POINTS,
        ADD_NEW_QUESTION
    };
public:
    Teacher();
    Teacher
    (
        string,  //name
        int,     //hashed password
        int,     //id
        string,  //subject
        shared_ptr<list<int>>  //list of groups
    );
    ~Teacher();
    void Unload(string)     override;
    void PrintInformation() override;
    void PrintOwnStudents(list<Student*>*);
    void Menu(list<Test*>**,list<Student*>*);
    int  GetHashedPassword();
    bool PrintAvailableTest(list<Test*>**);
    shared_ptr<list<int>> ptrGetGroupList();
    string GetSubject();
    Test*  CreateTest();
    Test*  SearchAvailableTest(list<Test*>**);
    Question* CreateQuestion(int);
    friend void EditTest(Teacher*, Test*,bool*);

};