#pragma once
#include "User.h"

class Student : public User
{
    string faculty;
    int group, course;
    list<string>* ptrSubjectList;
    list<SolvedTest*>* ptrSolvedTestList;
    enum MenuChoice
    {
        SOLVE_TEST = 1,
        VIEW_ALL_AVAIBLE_TEST,
        VIEW_OWN_INF,
        VIEW_ALL_SOLVED_TESTS_BRIEFLY,
        VIEW_ONE_SOLVED_TEST_FULLY
    };
public:
    Student();
    Student
    (
        string, //name
        string, //password
        string, //faculty
        int,    //id
        int,    //group
        int,    //course
        list<string>*, //strings for list
        list<SolvedTest*>*
    );
    ~Student();

    int  GetCourse();
    int  GetGroup();
    void Menu(list<Test*>*);
    void PrintInformation() override;
    void Unload(string);
    bool CheckSolvedTestList(Test*);
    bool PrintAvailableAndNoSolvedTest(list<Test*>*);
    bool PrintAllSolvedTestBriefly();
    bool PrintAllSolvedTestBriefly(string);
    //string GetID();
    list<string>*       GetPtrSubjectList();
    list<SolvedTest*>*  GetPtrSolvedTestList();
    SolvedTest*         SearchSolvedTestWithID(string);
};

Test* SearchTestWithID(list<Test*>*,string);
