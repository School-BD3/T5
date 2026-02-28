#include <iostream>
#include <list>
#include <vector>
#include <limits>

using namespace std;

class List {
protected:
    list<int> data;
public:
    virtual void insert(int value) = 0;
    virtual void remove() = 0;
    virtual void display() const {
        if (data.empty()) {
            cout << "Container is empty.\n";
            return;
        }
        for (int x : data)
            cout << x << " ";
        cout << endl;
    }
    virtual ~List() {}
};

class Stack : public List {
public:
    void insert(int value) override {
        data.push_back(value);
    }
    void remove() override {
        if (data.empty()) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "Removed: " << data.back() << endl;
        data.pop_back();
    }
};

class Queue : public List {
public:
    void insert(int value) override {
        data.push_back(value);
    }
    void remove() override {
        if (data.empty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Removed: " << data.front() << endl;
        data.pop_front();
    }
};

int getInt() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: ";
    }
    return value;
}

int main() {
    vector<List*> containers;
    int choice;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Create Stack\n";
        cout << "2. Create Queue\n";
        cout << "3. Insert element\n";
        cout << "4. Remove element\n";
        cout << "5. Display containers\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        if (choice == 1) {
            containers.push_back(new Stack());
            cout << "Stack created.\n";
        }
        else if (choice == 2) {
            containers.push_back(new Queue());
            cout << "Queue created.\n";
        }
        else if (choice == 3) {
            if (containers.empty()) {
                cout << "No containers available.\n";
            }
            else {
                cout << "Select container (1-" << containers.size() << "): ";
                int index = getInt();
                if (index < 1 || index > containers.size()) {
                    cout << "Invalid container number.\n";
                }
                else {
                    cout << "Enter value: ";
                    int value = getInt();
                    containers[index - 1]->insert(value);
                }
            }
        }
        else if (choice == 4) {
            if (containers.empty()) {
                cout << "No containers available.\n";
            }
            else {
                cout << "Select container (1-" << containers.size() << "): ";
                int index = getInt();
                if (index < 1 || index > containers.size()) {
                    cout << "Invalid container number.\n";
                }
                else {
                    containers[index - 1]->remove();
                }
            }
        }
        else if (choice == 5) {
            if (containers.empty()) {
                cout << "No containers available.\n";
            }
            else {
                for (size_t i = 0; i < containers.size(); i++) {
                    cout << "Container " << i + 1 << ": ";
                    containers[i]->display();
                }
            }
        }
        else if (choice == 0) {
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid option.\n";
        }

    } while (choice != 0);

    for (List* ptr : containers)
        delete ptr;

    return 0;
}