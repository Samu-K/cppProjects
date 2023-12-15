#include "cards.hh"

// TODO: Implement the methods here
Cards::Cards() {
    top_ = nullptr;
};

Cards::~Cards() {
    Card_data* current = top_;
    while (current != nullptr) {
       Card_data* temp = current;
       current = current->next;
       delete temp;
    }
}

Card_data* Cards::get_topmost() {
    return top_;
}

void Cards::add(int id) {
    Card_data* newCard = new Card_data;

    newCard->data = id;
    newCard->next = top_;
    top_ = newCard;

}

void Cards::print_from_top_to_bottom(std::ostream& s) {
    int n=1;
    Card_data* top_c = top_;

    if (top_c == nullptr) {
        return;
    }

    while (top_c != nullptr) {
        s << n << ": ";
        s << top_c->data;
        top_c = top_c->next;
        s << std::endl;
        n++;
    }

}

bool Cards::remove(int &id) {
    if (top_ == nullptr) {
        return false;
    }

    Card_data* temp = top_;
    top_ = top_->next;

    id = temp->data;
    delete temp;

    return true;
}

bool Cards::bottom_to_top() {
    if (top_ == nullptr) {
        return false;
    } else if (top_->next == nullptr) {
        return true;
    }

    Card_data* seclast = nullptr;
    Card_data* last = top_;

    while (last->next != nullptr) {
        seclast = last;
        last = last->next;
    }

    seclast->next = nullptr;
    last->next = top_;
    top_ = last;

    return true;
}

bool Cards::top_to_bottom() {
    if (top_ == nullptr) {
        return false;
    } else if (top_->next == nullptr) {
        return true;
    }

    Card_data* first = top_;
    Card_data* last = top_;

    while (last->next != nullptr) {
        last = last->next;
    }

    top_ = first->next;
    first->next = nullptr;
    last->next = first;

    return true;
}

void Cards::recursive_print(Card_data* top, std::ostream& s, int& n) {
    if (top == nullptr) {
        return;
    }

    recursive_print(top->next,s,n);

    s << n << ": ";
    s << top->data << std::endl;
    n++;
}

void Cards::print_from_bottom_to_top(std::ostream& s) {
    int n=1;
    recursive_print(top_,s,n);
}
