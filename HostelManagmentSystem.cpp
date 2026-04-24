#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// ================= ROOM CLASS =================
class Room {
public:
    int roomNo;
    int floor;
    string category;
    bool occupied;

    Room(int r, int f, string c) {
        roomNo = r;
        floor = f;
        category = c;
        occupied = false;
    }
};

// ================= STUDENT CLASS =================
class Student {
public:
    int id;
    string name;
    int roomNo;

    Student(int i, string n, int r) {
        id = i;
        name = n;
        roomNo = r;
    }
};

// ================= HOSTEL CLASS =================
class Hostel {
private:
    vector<Room> rooms;
    vector<Student> students;
    int studentCounter = 1;

public:

    // ================= ROOM FUNCTIONS =================
    void addRoom() {
        int r, f;
        string c;

        cout << "Enter Room Number: ";
        cin >> r;

        // check duplicate
        for (auto &room : rooms) {
            if (room.roomNo == r) {
                cout << "Room already exists!\n";
                return;
            }
        }

        cout << "Enter Floor: ";
        cin >> f;

        cout << "Enter Category (Single/Double): ";
        cin >> c;

        rooms.push_back(Room(r, f, c));
        cout << "Room added successfully!\n";
    }

    void displayRooms() {
        cout << "\n--- Room List ---\n";
        cout << setw(10) << "Room"
             << setw(10) << "Floor"
             << setw(15) << "Category"
             << setw(15) << "Status\n";

        for (auto &room : rooms) {
            cout << setw(10) << room.roomNo
                 << setw(10) << room.floor
                 << setw(15) << room.category
                 << setw(15) << (room.occupied ? "Occupied" : "Available") << endl;
        }
    }

    // ================= STUDENT FUNCTIONS =================
    void addStudent() {
        string name;
        int roomNo;

        cout << "Enter Student Name: ";
        cin >> name;

        cout << "Enter Room Number: ";
        cin >> roomNo;

        for (auto &room : rooms) {
            if (room.roomNo == roomNo && !room.occupied) {
                room.occupied = true;
                students.push_back(Student(studentCounter++, name, roomNo));
                cout << "Student added successfully!\n";
                return;
            }
        }

        cout << "Room not available!\n";
    }

    void displayStudents() {
        cout << "\n--- Student List ---\n";
        cout << setw(10) << "ID"
             << setw(15) << "Name"
             << setw(10) << "Room\n";

        for (auto &s : students) {
            cout << setw(10) << s.id
                 << setw(15) << s.name
                 << setw(10) << s.roomNo << endl;
        }
    }

    void searchStudent() {
        int id;
        cout << "Enter Student ID: ";
        cin >> id;

        for (auto &s : students) {
            if (s.id == id) {
                cout << "Found: " << s.name << " in Room " << s.roomNo << endl;
                return;
            }
        }

        cout << "Student not found!\n";
    }

    void deleteStudent() {
        int id;
        cout << "Enter Student ID: ";
        cin >> id;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].id == id) {

                // free room
                for (auto &room : rooms) {
                    if (room.roomNo == students[i].roomNo) {
                        room.occupied = false;
                    }
                }

                students.erase(students.begin() + i);
                cout << "Student deleted!\n";
                return;
            }
        }

        cout << "Student not found!\n";
    }

    // ================= REPORT =================
    void availableRooms() {
        cout << "\n--- Available Rooms ---\n";

        for (auto &room : rooms) {
            if (!room.occupied) {
                cout << "Room " << room.roomNo << " (Floor " << room.floor << ")\n";
            }
        }
    }

    // ================= MENU =================
    void menu() {
        int choice;

        do {
            cout << "\n===== HOSTEL MANAGEMENT =====\n";
            cout << "1. Add Room\n";
            cout << "2. Display Rooms\n";
            cout << "3. Add Student\n";
            cout << "4. Display Students\n";
            cout << "5. Search Student\n";
            cout << "6. Delete Student\n";
            cout << "7. Available Rooms\n";
            cout << "0. Exit\n";

            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addRoom(); break;
                case 2: displayRooms(); break;
                case 3: addStudent(); break;
                case 4: displayStudents(); break;
                case 5: searchStudent(); break;
                case 6: deleteStudent(); break;
                case 7: availableRooms(); break;
                case 0: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice!\n";
            }

        } while (choice != 0);
    }
};

// ================= MAIN =================
int main() {
    Hostel h;
    h.menu();
    return 0;
}