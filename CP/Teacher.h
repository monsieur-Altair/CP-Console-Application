#pragma once
#include "Student.h"

class Teacher : public User
{
    string subject;
    list<int>* ptrGroupList;//список групп препода, мб список спецух 
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
        string,     //name
        string,     //password
        int,        //id
        string,     //subject
        list<int>*  //list of groups
    );

    ~Teacher();
    void Menu(list<Test*>**,list<Student*>*);
    void PrintInformation() override;
    void Unload(string);

    list<int>* ptrGetGroupList();
    Test* CreateTest();
    Question* CreateQuestion(int);
    void PrintAvailableTest(list<Test*>**);
    void PrintOwnStudents(list<Student*>*);
    Test* SearchAvailableTest(list<Test*>**);
    friend void EditTest(Teacher*, Test*,bool*);
    string GetSubject();
    string GetPassword();
};

//bool SortByAnswerPercentage(SolvedTest* ptr1, SolvedTest* ptr2)
//{
//    return (ptr1->GetPercent() > ptr2->GetPercent());
//}
//
//bool SortSolvedBySubject(const SolvedTest* ptr1, const SolvedTest* ptr2)
//{
//    return (ptr1->subject.compare(ptr2->subject) < 0);
//}


//bool SortTestBySubject(const Test* ptr1, const Test* ptr2)
//{
//    return (ptr1->subject.compare(ptr2->subject) < 0);
//}

//bool SortStudentByGroups(const Student* ptr1, const Student* ptr2)
//{
//    return (ptr1->group) < (ptr2->group);
//}
//
//bool SortStudentAlphabetic(Student* ptr1, Student* ptr2)
//{
//    return (ptr1->GetName().compare(ptr2->GetName()) < 0);
//}