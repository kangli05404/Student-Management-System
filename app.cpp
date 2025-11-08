#include	<iostream>
#include 	<fstream>
#include	<string>
#include	<cstdlib>
#include	"List.h"
#include	"Student.h"

using namespace std;


bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool PrintList(List, int);
bool InsertExamResult(const char*, List*);
bool PrintStatistic(List);
bool FilterStudent(List, List*, char*, int, int);
bool UpdateIDandPhone(List*);
bool FindPotentialFirstClass(List, List*, char*);
int menu();

using namespace std;

int main() {
    List list1;
    List list2;
    int print;
    int choice;

    do {
        choice = menu();
        if (choice == 1) {
            if (CreateStuList("student.txt", &list1)) {
                cout << "\n\033[1;32mStudent list read successfully!\033[0m" << endl;
            }
            else {
                cout << "\n\033[1;31mFailed to read student list!!!\033[0m" << endl;
            }
        }
        else if (choice == 2) {
        
            char student_id[11];
            cout << "\nEnter Student ID to delete: ";
            cin >> student_id;

            if (DeleteStudent(&list1, student_id)) {
                cout << "\n\033[1;32mStudent with ID " << student_id << " has been deleted successfully.\033[1;32m\n";
            }
            else {
                cout << "\n\033[1;31mStudent with ID " << student_id << " not found in the list!!!\033[0m\n";
            }
        }

        else if (choice == 3) {
            do {
                cout << "\nPlease key in '1' (display on screen) or key in '2' (display on textfile): ";
                cin >> print;
                if (!PrintList(list1, print))
                    cout << "\033[1;31mUnsuccessful to display the student details!!!\033[0m" << endl;
                else {
                    if (print == 1) {
                        cout << "\n\n\033[1;32mSuccessful to display the student details on screen.\033[0m" << endl;
                    }
                    else if (print == 2) {
                        cout << "\n\n\033[1;32mSuccessful to display the student details in the textfile.\033[0m" << endl;
                    }
                    else {
                        cout << "\033[1;31mInvalid input.Please key in either '1' (display on screen) or '2' (display on textfile) only.\033[0m" << endl;
                    }
                }
            } while (print != 1 && print != 2);
        }

        else if (choice == 4) {
            if (!InsertExamResult("exam.txt", &list1)) {
                cout << "\n\033[1;31mFailed to insert exam results!!!\033[0m\n";
            }
        }
        else if (choice == 5) {
            if (PrintStatistic(list1)) {
                cout << "\033[1;32mSuccessful to print the statistic report.\033[0m" << endl;
            }
            else {
                cout << "\033[1;31mUnable to print the statistic report!!!\033[0m" << endl;
            }
        }

        else if (choice == 6) {
            char course[3];
            int year;
            int totalcredit;
            cout << "\nPlease enter the course that want to filter (CS/IB/IA/CN/CT): ";
            cin >> course;

            //standardize the letter first to easier the comparison
            for (int i = 0; i < course[i]; i++) {
                course[i] = toupper(course[i]);
            }
            while (strcmp(course, "CS") != 0 && strcmp(course, "IB") != 0 && strcmp(course, "IA") != 0 && strcmp(course, "CN") != 0 && strcmp(course, "CT") != 0) {
                cout << "\033[1;31mThe subject key in is not available.Please key in another subject.\033[0m" << endl;
                cout << "\nPlease enter the course that want to filter (CS/IB/IA/CN/CT): ";
                cin >> course;

                for (int i = 0; i < strlen(course); i++) {
                    course[i] = toupper(course[i]);
                }
            }
            cout << "Please enter the year that want to filter: ";
            while (!(cin >> year) || year < 1 || year > 9999) {
                cout << "\033[1;31mInvalid year. Please enter a valid year between 1 and 9999.\033[0m" << endl;

                cin.clear();          
                cin.ignore(1000, '\n');  // Discard invalid input from the buffer
                cout << "Please enter the year that want to filter: ";
            }
            cin.ignore(1000, '\n');  // Clear leftover newline if needed

            cout << "Please enter the minimum total credit hours: ";
            cin >> totalcredit;
            while (totalcredit < 0) {
                cout << "\n\033[1;31mInvalid total credit hour key in.Please key in again.\033[0m" << endl;
                cout << "Please enter the minimum total credit hours: ";
                cin >> totalcredit;
            }
            if (FilterStudent(list1, &list2, course, year, totalcredit)) {
                cout << "\nFiltered students successfully. Displaying list2:\n";
                PrintList(list2, 1);
            }
            else {
                cout << "\n\033[1;31mFailed to filter students.\033[0m\n";
            }
            list2.clear();

        }

        else if (choice == 7) {
            if (UpdateIDandPhone(&list1)) {
                cout << "\033[1;32mSuccesfully to update the student id and phone number.\033[0m" << endl;
                PrintList(list1, 1);
            }
            else {
                cout << "\033[1;31mUnable to update the student id and phone number.\033[0m" << endl;
            }
        }

        else if (choice == 8) {
            char course[3];
            cout << "Enter the course (CS/IB/IA/CN/CT): ";
            cin >> course;

            for (int i = 0; i < strlen(course); i++) {
                course[i] = toupper(course[i]);
            }

            while (strcmp(course, "CS") != 0 && strcmp(course, "IB") != 0 && strcmp(course, "IA") != 0 && strcmp(course, "CN") != 0 && strcmp(course, "CT") != 0) {

                cout << "\033[1;31mThe subject key in is not available.Please key in another subject.\033[0m" << endl;
                cout << "\nPlease enter the course (CS/IB/IA/CN/CT): ";
                cin >> course;

                for (int i = 0; i < strlen(course); i++) {
                    course[i] = toupper(course[i]);
                }

            }

            if (FindPotentialFirstClass(list1, &list2, course)) {
                PrintList(list2, 1);
            }
            else {
                cout << "\033[1;31mThere is no student in " << course << " that has potential to get first class.\033[0m" << endl;
            }
        }
        else if (choice == 9) {
            break;
        }
        cout << "\n\n\033[1;35mPress 'ENTER' to back to the main menu.\033[0m" << endl;
        cin.ignore();
        cin.get();
        system("cls");
    } while (choice != 9);

    system("cls");
    cout << endl;
    cout << "        \033[36m========================================================================================================\033[0m" << endl;
    cout << "        \033[35m|| / \\__                                    ****   *   *  ****                                        ||\033[0m" << endl;
    cout << "        \033[35m||(    @\\__                                 *      **  *  *   *                                       ||\033[0m " << endl;
    cout << "        \033[35m|| /        o                               ****   * * *  *   *                                       ||\033[0m" << endl;
    cout << "        \033[35m||/    (/                                   *      *  **  *   *                                       ||\033[0m" << endl;
    cout << "        \033[35m||/_/  U                                    ****   *   *  ****                                        ||\033[0m" << endl;
    cout << "        \033[35m||                                                                                                    ||\033[0m" << endl;
    cout << "        \033[35m||                     *****  *   *  *****  *   *  *   *     *   *  *****  *   *                      ||\033[0m" << endl;
    cout << "        \033[35m||                       *    *   *  *   *  **  *  *  *       * *   *   *  *   *                      ||\033[0m" << endl;
    cout << "        \033[35m||                       *    *****  *****  * * *  ***         *    *   *  *   *                      ||\033[0m" << endl;
    cout << "        \033[35m||                       *    *   *  *   *  *  **  *  *        *    *   *  *   *                      ||\033[0m" << endl;
    cout << "        \033[35m||                       *    *   *  *   *  *   *  *   *       *    *****  *****                      ||\033[0m" << endl;
    cout << "        \033[36m========================================================================================================\033[0m" << endl;
    return 0;
}


bool CreateStuList(const char* filename, List* list) {

    char actid[12];
    int count = 0;
    ifstream infile(filename); 
    if (!infile) {
        cout << "\n\033[1;31mInput file cannot be found\033[0m" << endl;
        cout << "\033[1;31mError opening file: " << filename << "\033[0m"<< endl;
        return false; 
    }

    char buffer[1000];

    while (infile.getline(buffer, 100)) { 
        Student* stu = new Student;
        //use strncmp because we want to compare the number of first n character that we want to compare
        if (strncmp(buffer, "Student Id = ", 13) == 0) {
            strcpy(stu->id, buffer + 13); // Extract ID (skip "Student Id = ") since from S until = include 13 character

            infile.getline(buffer, 100);
            if (strncmp(buffer, "Name = ", 7) == 0) {
                strcpy(stu->name, buffer + 7);
            }

            infile.getline(buffer, 100);
            if (strncmp(buffer, "course = ", 9) == 0) {
                strcpy(stu->course, buffer + 9);
            }

            infile.getline(buffer, 100);
            if (strncmp(buffer, "Phone Number = ", 15) == 0) {
                strcpy(stu->phone_no, buffer + 15);
            }

            // Check for duplicate student
            Node* cur = list->head;
            bool exists = false;
            while (cur != nullptr) {
                if (cur->item.id[0] == 'B') {
                    // Extract the actual student id although it already updated
                    strcpy(actid, cur->item.id + 3); 
                    if (strcmp(actid, stu->id) == 0) {
                        exists = true;
                        break;
                    }
                }
                else if (cur->item.compareID(*stu)) {
                    exists = true;
                    break;
                }
                cur = cur->next;
            }
            if (!exists) {
                list->insert(*stu);
            }
            else {
                cout << "\n\033[1;33mDuplicate student found. Skipping: " << stu->id <<"\033[0m"<< endl;
            }
            delete stu;
        }
    }

    infile.close();

    return true;
}

bool DeleteStudent(List* list, char* id) {

    char actid[13];
    if (list->empty()) {
        return false;
    }

    Node* cur, * pre;

    //use cur=list->head but not cur=list.head because  
    //the list is not an object but it is a pointer
    cur = list->head;
    pre = nullptr;
    Student tempStudent;
    strcpy(tempStudent.id, id);


    while (cur != nullptr) {
        if (cur->item.id[0] == 'B') {
            strcpy(actid, cur->item.id + 3);
        }
        if (cur->item.compareID(tempStudent)||strcmp(actid,tempStudent.id)==0) { 
            if (pre == nullptr) {
                // Deleting the head node
                list->head = cur->next;
            }
            else {
                pre->next = cur->next;
            }

            free(cur); 
            list->count--;
            return true;
        }
        pre = cur;
        cur = cur->next;
    }
    return false; 
}

bool PrintList(List list, int source) {
    if (list.empty())
    {
        cout << "\n\033[1;31mEmpty list!\033[0m\n\n";
        return false;
    }

    Node* cur;
    Student tmp;
    cur = list.head;
    ofstream outfile;

    int k = 0;

    if (source == 1) {
        while (cur != nullptr) {
            cout << "\n***************************************************** STUDENT " << k + 1 << " *****************************************************";
            cur->item.print(cout);
            if (cur->item.exam_cnt == 0) {
                cout << "\n\033[1;33mTHIS STUDENT HAVEN'T TAKEN ANY EXAM YET\033[0m\n\n";
            }
            else {
                cout << "\n--------------------------------------------------PAST EXAM RESULT:--------------------------------------------------";
                for (int i = 0; i < cur->item.exam_cnt; i++) {
                    cur->item.exam[i].print(cout);
                }
            }
            cout << "\n***************************************************** STUDENT " << k + 1 << " *****************************************************\n\n";
            cur = cur->next;
            k += 1;
        }
    }
    else if (source == 2) {
        outfile.open("student_result.txt");
        while (cur != nullptr) {
            outfile << "\n***************************************************** STUDENT " << k + 1 << " *****************************************************";
            cur->item.print(outfile);
            if (cur->item.exam_cnt == 0) {
                outfile << "\nTHIS STUDENT HAVEN'T TAKEN ANY EXAM YET\n\n";
            }
            else {
                outfile << "\n--------------------------------------------------PAST EXAM RESULT:--------------------------------------------------";
                for (int i = 0; i < cur->item.exam_cnt; i++) {
                    cur->item.exam[i].print(outfile);
                }
            }
            outfile << "\n***************************************************** STUDENT " << k + 1 << " *****************************************************\n\n";
            cur = cur->next;
            k += 1;
        }
        outfile.close();
    }
    return true;
}

bool InsertExamResult(const char* filename, List* list) {
    ifstream infile(filename);
    if (!infile) {
        cout << "\n\033[1;31mInput file cannot be found.\033[0m" << endl;
        cout << "\033[1;31mError: Could not open file " << filename <<"\033[0m"<< endl;
        return false;
    }

    if (list->empty()) {
        cout << "\033[1;31mUnable to insert the exam result.\033[0m" << endl;
    }

    Node* cur;
    Exam tmpexam;
    Student stu1;
    string lines;
    char actid[13];

    while (getline(infile, lines)) {
        infile >> stu1.id >> tmpexam.trimester >> tmpexam.year >> tmpexam.numOfSubjects;

        for (int i = 0; i < tmpexam.numOfSubjects; i++) {
            infile >> tmpexam.sub[i].subject_code;
            infile.ignore();
            infile >> tmpexam.sub[i].subject_name;
            infile.ignore();
            infile >> tmpexam.sub[i].credit_hours;
            infile >> tmpexam.sub[i].marks;
        }

        if (tmpexam.numOfSubjects == 0) {
            cout << "\033[1;31mError: No valid subjects for Student ID: " << stu1.id << ". Skipping this exam.\033[0m\n";
            continue;
        }

        cur = list->head;
        while (cur != nullptr) {
            if (cur->item.id[0] == 'B') {
                strcpy(actid, cur->item.id + 3);
            }

            if (strcmp(cur->item.id, stu1.id) == 0 || strcmp(actid,stu1.id)==0) {
                bool isDuplicate = false;

                //Check for duplicate exam based on trimester and subject code
                for (int i = 0; i < cur->item.exam_cnt; i++) {
                    if (cur->item.exam[i].trimester == tmpexam.trimester && cur->item.exam[i].year == tmpexam.year) {
                        for (int j = 0; j < cur->item.exam[i].numOfSubjects; j++) {
                            for (int k = 0; k < tmpexam.numOfSubjects; k++) {
                                if (strcmp(cur->item.exam[i].sub[j].subject_code, tmpexam.sub[k].subject_code) == 0) {
                                    isDuplicate = true;
                                    cout << "\n\033[1;33mDuplicate exam detected (Student ID: " << stu1.id
                                        << ", Trimester: " << tmpexam.trimester
                                        << ", Subject: " << tmpexam.sub[k].subject_code << "). Skipping.\033[0m\n";
                                    break;
                                }
                            }
                            if (isDuplicate)
                                break;
                        }
                    }
                    if (isDuplicate)
                        break;
                }
                if (isDuplicate)
                    break;

                //proceed to insert if there is no duplicate
                if (cur->item.exam_cnt < 10) {
                    cur->item.exam[cur->item.exam_cnt] = tmpexam;
                    cur->item.exam_cnt++;
                    cout << "\n\033[1;32mExam added for Student ID: " << stu1.id <<"\033[0m "<<"\n";

                    if (!cur->item.exam[cur->item.exam_cnt - 1].calculateGPA()) {
                        cout << "\033[1;31mError: Failed to calculate GPA for Student ID: " << stu1.id <<"\033[0m"<< ".\n";
                        break;
                    }
                    cout << "\033[1;32mGPA calculated.\033[0m " << "\n";

                    if (!cur->item.calculateCurrentCGPA()) {
                        cout << "\033[1;31mError: Failed to update CGPA for Student ID: " << stu1.id <<"\033[0m"<< ".\n";
                        break;
                    }
                    cout << "\033[1;32mCGPA updated.\033[0m " << "\n";
                    cout << "\033[1;32mExam results insert successfully!\033[0m\n";

                }
                else {
                    cout << "\033[1;33mExam limit reached for Student ID: " << stu1.id << ". Skipping...\033[0m\n";
                }
                break;
            }
            cur = cur->next;
        }
    }
    infile.close();
    return true;
}

bool PrintStatistic(List list) {
    if (list.empty()) {
        cout << "\n\033[1;31mThe student list is empty. No statistics to display.\033[0m\n";
        return false;
    }

    // initialization only
    int totalStudents = 0;
    int csCount = 0, iaCount = 0, ibCount = 0, cnCount = 0, ctCount = 0;
    double totalCGPA = 0.0;
    int totalSubjects = 0;
    int totalSemesters = 0;
    int totalCreditHours = 0;
    double avgSubjectsPerSemester=0;
    double avgCreditHoursPerSemester=0;
    double avgCGPA;

    Node* cur = list.head;
    while (cur != nullptr) {
        totalStudents++; 

        if (strcmp(cur->item.course, "CS") == 0)
            csCount++;
        else if (strcmp(cur->item.course, "IA") == 0)
            iaCount++;
        else if (strcmp(cur->item.course, "IB") == 0)
            ibCount++;
        else if (strcmp(cur->item.course, "CN") == 0)
            cnCount++;
        else if (strcmp(cur->item.course, "CT") == 0)
            ctCount++;

        // Add CGPA for each of the student in the list
        totalCGPA += cur->item.current_cgpa;

        for (int i = 0; i < cur->item.exam_cnt; i++) {
            totalSubjects += cur->item.exam[i].numOfSubjects; 
            totalSemesters++;                              
            for (int j = 0; j < cur->item.exam[i].numOfSubjects; j++) {
                totalCreditHours += cur->item.exam[i].sub[j].credit_hours; 
            }
        }

        cur = cur->next; 
    }

    if (totalStudents > 0) {
        avgCGPA = totalCGPA / totalStudents;
    }
    if (totalSemesters > 0) {
        //due to the totalSubjects and totalSemesters in in integer type but we want to calculate for the average which can have decimal place
        avgSubjectsPerSemester = static_cast<double>(totalSubjects) / totalSemesters;
        avgCreditHoursPerSemester = static_cast<double>(totalCreditHours) / totalSemesters;
    }

    cout << "\n========== STUDENT STATISTICS ==========\n";
    cout << "Total Students: " << totalStudents << endl;
    cout << "    CS Students: " << csCount << endl;
    cout << "    IA Students: " << iaCount << endl;
    cout << "    IB Students: " << ibCount << endl;
    cout << "    CN Students: " << cnCount << endl;
    cout << "    CT Students: " << ctCount << endl;
    cout << "\nAverage CGPA: " << avgCGPA << endl;
    cout << "Average Subjects Taken Per Semester: " <<fixed<<setprecision(2)<< avgSubjectsPerSemester << endl;
    cout << "Average Credits Earned Per Semester: " << avgCreditHoursPerSemester << endl;
    cout << "=========================================\n\n";

    return true;
}

bool FilterStudent(List list1, List* list2, char* course, int year, int totalcredit) {
    // Check if list1 is empty
    if (list1.empty()) {
        cout << "\n\033[1;31mList1 is empty. No students to filter.\033[0m\n";
        return false;
    }

    if (!list2->empty()) {
        cout << "\033[1;31mList2 is not empty.\033[0m" << endl;
        return false;
    }

    Node* cur = list1.head;
    while (cur != nullptr) {
        string yearString(cur->item.id);

        //if the student id start from 'B' which means it already been updated before this,we want to ignore the updated one but extract the original for comparison usage
        if (yearString.substr(0, 1) == "B") {
            yearString = yearString.substr(3, 2);
        }
        else {
            yearString = yearString.substr(0, 2);
        }
        int enrollmentYear = 2000 + stoi(yearString);

        //standardize the case for the course
        for (int i = 0; course[i]; i++) {
            course[i] = toupper(course[i]);
        }
        for (int i = 0; cur->item.course[i]; i++) {
            cur->item.course[i] = toupper(cur->item.course[i]);
        }
        // Check if the student fulfills all 3 conditions or not
        if (strcmp(cur->item.course, course) == 0 && enrollmentYear == year &&cur->item.totalCreditsEarned >= totalcredit) {
            list2->insert(cur->item);

        }
        cur = cur->next;
    }
    return true;
}

bool UpdateIDandPhone(List* list) {
    string updatedID;
    if (list->empty()) {
        cout << "\033[1;31mThe student list is empty!\033[0m" << endl;
        return false;
    }
    Node* cur = list->head;
    Student stu1;
    while (cur != nullptr) {
        if (strlen(cur->item.id)!=10) {
            updatedID = "B" + string(cur->item.course) + string(cur->item.id);
            strcpy(cur->item.id, updatedID.c_str());

            //update the phone number
            //extract the first 3 and last 4 digit in the phone_no 
            //because we dont want the - t be appear in the updated phone number
            string first3(cur->item.phone_no, 3);

            //extracting the last 4 digit of the phone number
            string last4(cur->item.phone_no, 4, 4);
            string firstdigit(cur->item.phone_no, 1);

            //convert the first digit to int because want to identify whether it is even number or odd number for the first digit in the phone number
            int digit = stoi(firstdigit);
            string newPhone;
            if (digit % 2 != 0) {
                newPhone = "01" + first3 + last4;
                strcpy(cur->item.phone_no, newPhone.c_str());
            }
            else {
                newPhone = "02" + first3 + last4;
                strcpy(cur->item.phone_no, newPhone.c_str());
            }
        }

        else {
            cout << "\033[1;33mThe id and phone already updated previously.\033[0m" << endl;
        }
        cur = cur->next;
    }
    return true;
}

bool FindPotentialFirstClass(List list1, List* list2, char* course) {
    if (list1.empty()) {
        cout << "\n\033[1;31mList1 is empty. No students to filter.\033[0m\n";
        return false;
    }

    if (!list2->empty()) {
        cout << "\n\033[1;31mList2 is not empty.\033[0m" << endl;
        return false;
    }

    for (int i = 0; course[i]; i++) {
        course[i] = toupper(course[i]);
    }

    bool found = false;
    Node* cur = list1.head;

    while (cur != nullptr) {
        // Convert student's course to uppercase only when cur is valid
        for (int i = 0; cur->item.course[i]; i++) {
            cur->item.course[i] = toupper(cur->item.course[i]);
        }

        if (strcmp(cur->item.course, course) == 0) {
            if (cur->item.exam_cnt >= 3) {
                int countHighGPA = 0;
                bool fulfill = true;

                for (int i = 0; i < cur->item.exam_cnt; i++) {
                    double gpa = cur->item.exam[i].gpa;
                    int creditHours = 0;

                    for (int j = 0; j < cur->item.exam[i].numOfSubjects; j++) {
                        creditHours += cur->item.exam[i].sub[j].credit_hours;
                    }

                    if (gpa >= 3.75 && creditHours >= 12) {
                        countHighGPA++;
                    }
                    else if (gpa < 3.5) {
                        fulfill = false;
                        break;
                    }
                }
                //check whether fullfill those criteria or not
                if (fulfill && countHighGPA >= 3) {
                    list2->insert(cur->item);
                    found = true;
                }
            }
        }

        cur = cur->next;
    }

    if (!found) {
        cout << "\033[1;33mThere is no student in " << course << " that has potential to get first class.\033[0m\n";
    }
    else {
        cout << "\033[1;32mSuccessfully to find the potential first class student.\033[0m" << endl;
    }

    return true;
}

int menu()
{
    string input;
    int  choice = 0;
    do {
        cout << "\033[1;36m"; 
        cout << "\t __  __ _____ _   _ _    _ \n";
        cout << "\t|  \\/  | ____| \\ | | |  | |\n";
        cout << "\t| |\\/| |  _| |  \\| | |  | |\n";
        cout << "\t| |  | | |___| |\\  | |__| |\n";
        cout << "\t|_|  |_|_____|_| \\_|\\____/ \n";
        cout << "\033[0m"; 
        cout << "\n========== STUDENT MANAGEMENT SYSTEM ===========" << endl;
        cout << "1. Create Student List" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Print List" << endl;
        cout << "4. Insert Exam Result" << endl;
        cout << "5. Print Exam Statistic" << endl;
        cout << "6. Filter Student" << endl;
        cout << "7. Update ID and Phone" << endl;
        cout << "8. Find Potential First Class Student" << endl;
        cout << "9. Exit" << endl;
        cout << "================================================" << endl;
        cout << "\nPlease select your choice (1-9): ";
        cin >> input;

        if (input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7" || input == "8" || input == "9") {
            choice = stoi(input);
            return choice;
        }
        else {
            cout << "\033[1;31mInvalid input.Please key in the choice within 1-9 only again.\033[0m\n\n" << endl;
        }
    } while (choice != 9);
}