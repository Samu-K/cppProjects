#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

using std::cout;
using std::endl;

Queue::Queue(unsigned int cycle) {
    cycle_ = cycle;
}

Queue::~Queue() {
    Vehicle* current = first_;
    while (current != nullptr) {
       Vehicle* temp = current;
       current = current->next;
       delete temp;
    }
}

void Queue::enqueue(string const& reg) {
    if (!is_green_) {
        Vehicle* newVehicle = new Vehicle;
        newVehicle->reg_num = reg;
        newVehicle->next = nullptr;

        // if empty we just add
        if (first_ == nullptr) {
            first_ = newVehicle;
        } else {
            Vehicle* temp = first_;
            // get to end of list and add
            while(temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newVehicle;
        }
    } else {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
    }
}

void Queue::switch_light() {

    if (is_green_) {
        is_green_ = false;
        if (first_ == nullptr) {
            cout << "RED: No vehicles waiting in traffic lights" << endl;
            return;
        }
    } else {
        is_green_ = true;
        if (first_ == nullptr) {
            cout << "GREEN: No vehicles waiting in traffic lights" << endl;
            return;
        }

        cout << "GREEN: Vehicle(s) ";
        unsigned long int n = 0;
        while (first_ != nullptr) {
            n++;
            if (n>cycle_) {
                break;
            }
            cout << first_->reg_num << " ";
            dequeue();
        }
        cout << "can go on" << endl;
        is_green_ = false;

    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

void Queue::print() const {
    Vehicle* first_c = first_;
    if (is_green_) {
        cout << "GREEN: ";
    } else {
        cout << "RED: ";
    }
    if (first_c == nullptr) {
        cout << "No vehicles waiting in traffic lights" << endl;
        return;
    }
    cout << "Vehicle(s) ";
    while (first_c != nullptr) {
        cout << first_c->reg_num << " ";
        first_c = first_c->next;
    }
    cout << "waiting in traffic lights" << endl;
}

void Queue::dequeue() {
    Vehicle* temp = first_;
    first_ = first_->next;
    delete temp;
}
