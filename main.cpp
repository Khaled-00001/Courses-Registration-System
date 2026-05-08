#include "System.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void loading() {
    cout << "\nLoading";
    for (int i = 0; i < 5; i++) {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    cout << "\n\n";
}
void welcomeScreen() {

    cout << "=====================================\n";
    cout << "     COURSE REGISTRATION SYSTEM      \n";
    cout << "=====================================\n";
    cout << "        Team Elf7ool        \n";
    cout << "-------------------------------------\n";
    cout << "   1. Start System\n";
    cout << "   2. Exit\n";
    cout << "=====================================\n";
    cout << "Choose: ";
}

int main() {

    welcomeScreen();
    loading();
    int choice;
    cin >> choice;

    if (choice == 2) {
        cout << "Goodbye!\n";
        return 0;
    }

    System system;
    system.run();

    return 0;
}