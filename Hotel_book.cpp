
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Booking {
    int bookingID;
    string customerName;
    int roomNumber;
    int days;
    double pricePerDay;

    double totalBill() const {
        return days * pricePerDay;
    }
};

int main() {
    map<int, Booking> bookings;
    set<int> availableRooms;
    int nextBookingID = 1001;
    int choice;

    // Initialize 15 hotel rooms
    for (int room = 101; room <= 115; room++) {
        availableRooms.insert(room);
    }

    do {
        cout << "\n===== HOTEL MANAGEMENT SYSTEM =====\n";
        cout << "1. Book Room\n";
        cout << "2. Cancel Booking\n";
        cout << "3. Display All Bookings\n";
        cout << "4. Search Booking\n";
        cout << "5. Display Available Rooms\n";
        cout << "6. Calculate Total Revenue\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (availableRooms.empty()) {
                cout << "No rooms available!\n";
                continue;
            }

            Booking b;

            cout << "Enter Customer Name: ";
            cin.ignore();
            getline(cin, b.customerName);

            cout << "\nAvailable Rooms: ";
            for (int room : availableRooms) {
                cout << room << " ";
            }

            cout << "\nEnter Room Number: ";
            cin >> b.roomNumber;

            auto it = availableRooms.find(b.roomNumber);

            if (it == availableRooms.end()) {
                cout << "Room unavailable or invalid!\n";
                continue;
            }

            cout << "Enter Number of Days: ";
            cin >> b.days;

            cout << "Enter Price Per Day: ";
            cin >> b.pricePerDay;

            if (b.days <= 0 || b.pricePerDay <= 0) {
                cout << "Invalid booking details!\n";
                continue;
            }

            b.bookingID = nextBookingID++;

            bookings[b.bookingID] = b;
            availableRooms.erase(it);

            cout << "\nRoom booked successfully!\n";
            cout << "Booking ID: " << b.bookingID << "\n";
            cout << "Customer: " << b.customerName << "\n";
            cout << "Room Number: " << b.roomNumber << "\n";
            cout << fixed << setprecision(2);
            cout << "Total Bill: Rs. " << b.totalBill() << "\n";
        }
        else if (choice == 2) {
            int id;

            cout << "Enter Booking ID to cancel: ";
            cin >> id;

            auto it = bookings.find(id);

            if (it == bookings.end()) {
                cout << "Booking not found!\n";
            } else {
                availableRooms.insert(it->second.roomNumber);
                bookings.erase(it);
                cout << "Booking cancelled successfully!\n";
            }
        }
        else if (choice == 3) {
            if (bookings.empty()) {
                cout << "No active bookings.\n";
            }

            for (const auto &item : bookings) {
                const Booking &b = item.second;

                cout << "\nBooking ID: " << b.bookingID
                     << "\nCustomer: " << b.customerName
                     << "\nRoom: " << b.roomNumber
                     << "\nDays: " << b.days
                     << "\nTotal Bill: Rs. "
                     << fixed << setprecision(2)
                     << b.totalBill() << "\n";
            }
        }
        else if (choice == 4) {
            int id;

            cout << "Enter Booking ID: ";
            cin >> id;

            auto it = bookings.find(id);

            if (it != bookings.end()) {
                const Booking &b = it->second;

                cout << "\nBooking Found!\n";
                cout << "Customer: " << b.customerName << "\n";
                cout << "Room: " << b.roomNumber << "\n";
                cout << "Days: " << b.days << "\n";
                cout << "Total Bill: Rs. "
                     << fixed << setprecision(2)
                     << b.totalBill() << "\n";
            } else {
                cout << "Booking not found!\n";
            }
        }
        else if (choice == 5) {
            cout << "\nAvailable Rooms: ";

            if (availableRooms.empty()) {
                cout << "No rooms available.";
            } else {
                for (int room : availableRooms) {
                    cout << room << " ";
                }
            }

            cout << "\nTotal Available Rooms: "
                 << availableRooms.size() << "\n";
        }
        else if (choice == 6) {
            double revenue = 0;

            for (const auto &item : bookings) {
                revenue += item.second.totalBill();
            }

            cout << fixed << setprecision(2);
            cout << "Total Revenue from Active Bookings: Rs. "
                 << revenue << "\n";
        }
        else if (choice == 7) {
            cout << "Thank you for using the Hotel Management System!\n";
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
