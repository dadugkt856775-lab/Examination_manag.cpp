
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    string name;
    int score = 0;
};

struct Question {
    string text;
    vector<string> options;
    char answer;
};

int main() {
    vector<Student> students;
    map<int, Student> records;
    set<int> registeredIDs;

    vector<Question> questions = {
        {"Which language is used for STL?",
         {"A. HTML", "B. C++", "C. CSS", "D. SQL"}, 'B'},

        {"Which STL container follows FIFO?",
         {"A. Stack", "B. Set", "C. Queue", "D. Map"}, 'C'},

        {"Which container stores unique sorted keys?",
         {"A. Set", "B. Vector", "C. Queue", "D. List"}, 'A'},

        {"Which algorithm sorts a vector?",
         {"A. find()", "B. sort()", "C. push()", "D. erase()"}, 'B'},

        {"Which container stores key-value pairs?",
         {"A. Map", "B. Stack", "C. Queue", "D. Array"}, 'A'}
    };

    int choice;

    do {
        cout << "\n===== ONLINE EXAMINATION SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. Take Examination\n";
        cout << "3. Display Results\n";
        cout << "4. Search Student Result\n";
        cout << "5. Display Ranking\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Student s;

            cout << "Enter Student ID: ";
            cin >> s.id;

            if (registeredIDs.count(s.id)) {
                cout << "Student ID already registered!\n";
                continue;
            }

            cin.ignore();
            cout << "Enter Student Name: ";
            getline(cin, s.name);

            students.push_back(s);
            records[s.id] = s;
            registeredIDs.insert(s.id);

            cout << "Registration successful!\n";
        }
        else if (choice == 2) {
            int id;

            cout << "Enter Student ID: ";
            cin >> id;

            auto it = records.find(id);

            if (it == records.end()) {
                cout << "Student not registered!\n";
                continue;
            }

            if (it->second.score != -1) {
                cout << "Examination already completed!\n";
                continue;
            }

            int score = 0;
            char answer;

            cout << "\n===== EXAMINATION STARTED =====\n";

            for (size_t i = 0; i < questions.size(); i++) {
                cout << "\nQuestion " << i + 1 << ": "
                     << questions[i].text << "\n";

                for (const string &option : questions[i].options) {
                    cout << option << "\n";
                }

                cout << "Enter answer (A/B/C/D): ";
                cin >> answer;

                answer = toupper(answer);

                if (answer == questions[i].answer) {
                    score++;
                }
            }

            it->second.score = score;

            for (Student &s : students) {
                if (s.id == id) {
                    s.score = score;
                    break;
                }
            }

            cout << "\nExamination completed!\n";
            cout << "Your score: " << score
                 << "/" << questions.size() << "\n";
        }
        else if (choice == 3) {
            if (students.empty()) {
                cout << "No students registered.\n";
            }

            for (const Student &s : students) {
                cout << "\nStudent ID: " << s.id
                     << "\nName: " << s.name
                     << "\nScore: ";

                if (s.score == -1) {
                    cout << "Exam not attempted\n";
                } else {
                    cout << s.score << "/" << questions.size()
                         << "\nPercentage: "
                         << fixed << setprecision(2)
                         << (s.score * 100.0 / questions.size())
                         << "%\n";
                }
            }
        }
        else if (choice == 4) {
            int id;

            cout << "Enter Student ID: ";
            cin >> id;

            auto it = records.find(id);

            if (it == records.end()) {
                cout << "Student not found!\n";
            } else {
                cout << "Name: " << it->second.name << "\n";

                if (it->second.score == -1) {
                    cout << "Exam not attempted yet.\n";
                } else {
                    cout << "Score: " << it->second.score
                         << "/" << questions.size() << "\n";
                }
            }
        }
        else if (choice == 5) {
            vector<Student> ranked;

            for (const Student &s : students) {
                if (s.score >= 0) {
                    ranked.push_back(s);
                }
            }

            sort(ranked.begin(), ranked.end(),
                [](const Student &a, const Student &b) {
                    return a.score > b.score;
                });

            cout << "\n===== STUDENT RANKING =====\n";

            if (ranked.empty()) {
                cout << "No examination results available.\n";
            }

            for (size_t i = 0; i < ranked.size(); i++) {
                cout << "Rank " << i + 1
                     << ": " << ranked[i].name
                     << " - " << ranked[i].score << " marks\n";
            }
        }
        else if (choice == 6) {
            cout << "Exiting Examination System...\n";
        }
        else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
