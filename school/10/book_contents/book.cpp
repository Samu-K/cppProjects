/*# Dev notes:                                                              #
#       Dev: Samu Kaarlela                                                  #
#        Studnum: 150974219                                                 #
#        email: samu.kaarlela@tuni.fi                                       #
#############################################################################
*/

#include "book.hh"
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

// operators for chapter
bool Chapter::operator<(const Chapter& rhs) const {
    return (subchapters_.size() < rhs.subchapters_.size());
}

bool Chapter::operator==(const Chapter& rhs) const {
    return (id_ == rhs.id_);
}

Book::Book() {
}

// make sure we delete all used memory
Book::~Book() {
    for (auto& chap : chapters_) {
        delete chap;
    }
}

// adds a new chapter to our book
void Book::addNewChapter(const std::string &id, const std::string &fullName, int length)
{
    // reserve space for new chapter
    Chapter* new_chap = new Chapter;

    // fill with given info
    new_chap->id_ = id;
    new_chap->fullName_ = fullName;
    new_chap->length_ = length;

    // add to vector of chapters
    chapters_.push_back(new_chap);

}

// links a chapter to it's child and/or parent
void Book::addRelation(const std::string &subchapter, const std::string &parentChapter)
{
    // init vars for parent and child
    Chapter* prnt_chap = nullptr;
    Chapter* sub_chap = nullptr;


    // get the parent and sub chapter based on id
    for (Chapter* chap : chapters_) {
        if (chap->id_ == parentChapter) {
             prnt_chap = chap;
        }
        if (chap->id_ == subchapter) {
             sub_chap = chap;
        }
    }

    // add to parents subchapters
    if ((sub_chap != nullptr) && (prnt_chap != nullptr)) {
        prnt_chap->subchapters_.push_back(sub_chap);
    }

    // set sub chapters parent
    if (prnt_chap != nullptr) {
        sub_chap->parentChapter_ = prnt_chap;
    }
}

// comparison function to sort chapters alphabetically
bool cmp (Chapter* a, Chapter* b) {
    return a->fullName_ < b->fullName_;
}

// print all chapters in book
void Book::printIds(Params params) const
{
    // gets rid of unused parameter warning
    (void)params;

    // print the total amount of chapters
    cout << "Book has " << chapters_.size() << " chapters:" << endl;

    // sort chapters alphabetically
    std::vector<Chapter *> ordered_chapters = chapters_;
    std::sort(ordered_chapters.begin(),ordered_chapters.end(),cmp);

    // print chapters out
    for (const auto& chap : ordered_chapters) {
        cout << chap->fullName_ << " --- " << chap->id_ << endl;
    }
}

// print chapters in "TOC" style
void Book::printContents(Params params) const
{
    // gets rid of unused parameter warning
    (void)params;

    // order chapters
    std::vector<Chapter *> ordered_chapters = chapters_;
    std::sort(ordered_chapters.begin(),ordered_chapters.end());

    // we use this to keep track of printed chapters
    // this way we avoid printing double
    std::vector<Chapter *> printed;

    // using recursion
    // also use n to keep track of indentation
    int n=0;
    recursive_print(ordered_chapters,n, printed);

}

// recursive print to print out all hiearchys of the book
void Book::recursive_print(std::vector<Chapter *>& chaps, int& n, std::vector<Chapter *>& printed) const {
    // keeps track of chapter numbers
    int num=0;

    // string for indents
    std::string indent(n*2,' ');

    // go through all chapters
    for (const auto& chap : chaps) {
        num++;

        // don't show chapters that are hidden
        // or already printed
        if (!(chap->show)) {
            num--;
            continue;
        } else if (std::find(printed.begin(),printed.end(),chap) != printed.end()) {
            num--;
            continue;
        }

        // print formatting depends on if chapter is open
        if (chap->open) {
            // print and add to printed
            cout << "- " << indent
                 << num << ". "
                 << chap->fullName_ << " ( "
                 << chap->length_ << " )"
                 << endl;
            printed.push_back(chap);
            // increase indentation and go one layer "deeper"
            n++;
            recursive_print(chap->subchapters_,n,printed);

        } else {
            // print and add to printed
            cout << "+ " << indent
                 << num << ". "
                 << chap->fullName_ << " ( "
                 << chap->length_ << " )"
                 << endl;
            printed.push_back(chap);
            // we don't want to print hidden subchapters
            for (auto& schap : chap->subchapters_) {
                printed.push_back(schap);
            }
        }
    }
    // decrease indent when one hierarchy is finished
    n--;
}

// closes a chapters hierarchy from id down
void Book::close(Params params) const
{
    // get pointer to chapter
    std::string id = params[0];
    Chapter* state_chap = fetch_chapter(id);

    // give error if no match
    if (state_chap == nullptr) {
        cout << "Error: Not found: " << id << endl;
        return;
    }

    // close the top level chapter
    state_chap->open = false;
    // recursively close all lower chapters
    recursive_state_switch(state_chap->subchapters_,false);

}

// recursively switch the open/closed status of chapters
void Book::recursive_state_switch(std::vector<Chapter *>& chaps, bool state) const{
    // go trough all subschapters
    for (auto& chap : chaps) {
        // if we're opening chapters,
        // we need to make sure only top level is opened
        if (state) {
            // exception is if the chapter has no children
            if (chap->subchapters_.size() == 0) {
                // then we set it to open
                chap->open = state;
            }
        } else{
            // if we are closing
            // we can just close all chapters
            chap->open = state;
        }

        // set chapter to show / hide
        chap->show = state;
        // if chapter has subschapters then switch them too
        if (chap->subchapters_.size() != 0) {
            recursive_state_switch(chap->subchapters_,state);
        }
    }
}

// gets the pointer for a given id
Chapter *Book::fetch_chapter(std::string id) const
{
    for (Chapter* chap : chapters_) {
        if (chap->id_ == id) {
            return chap;
        }
    }

    return nullptr;
}

// opens chapters from given id down
void Book::open(Params params) const
{
    // get pointer
    std::string id = params[0];
    Chapter* state_chap = fetch_chapter(id);

    // error on no match
    if (state_chap == nullptr) {
        cout << "Error: Not found: " << id << endl;
        return;
    }
    // same as closing
    state_chap->open = true;
    recursive_state_switch(state_chap->subchapters_,true);
}

// open all chapters
void Book::openAll(Params params) const
{
    // gets rid of unused parameter warning
    (void)params;

    // go through all chapters and open them
    for (auto& chap : chapters_) {
        chap->open = true;
        chap->show = true;
    }
}

// print out all chapters with same parent
void Book::printSiblingChapters(Params params) const
{
    // get pointer
    std::string id = params[0];
    Chapter* child = fetch_chapter(id);

    // if child not found, give error
    if (child == nullptr) {
        cout << "Error: Not found: " << id << endl;
        return;
    }

    Chapter* parent = child->parentChapter_;

    // get list to store siblings
    std::vector<Chapter *> siblings;

    // if chap has the given parent, add it to list
    for (auto& chap : chapters_) {
        if(chap->parentChapter_ == parent) {
            siblings.push_back(chap);
        }
    }

    // if list only has given id
    // then chapter has no siblings
    if (siblings.size() == 1) {
        cout << id << " has no sibling chapters." << endl;
        return;
    }

    // print out siblings and amount
    cout << id << " has " << siblings.size()-1 << " sibling chapters: " << endl;
    for (auto& chap : siblings) {
        if (chap->id_ != id) {
            cout << chap->id_ << endl;
        }
    }
}

// recursively count the total len
void count_len(std::vector<Chapter *>& chaps, int& n) {
    // go through subschapters
    for (auto& chap : chaps) {
        // add len to n
        n += chap->length_;
        // if subschapters, then go thourgh those
        if (chap->subchapters_.size() != 0) {
            count_len(chap->subchapters_,n);
        }
    }
}

// prints the total length from id and all children
void Book::printTotalLength(Params params) const
{
    // get pointer
    std::string id = params[0];
    Chapter* count = fetch_chapter(id);

    // if no match, give error
    if (count == nullptr) {
        cout << "Error: Not found: " << id << endl;
        return;
    }

    // n counts length
    int n=0;
    // add top level to n
    n += count->length_;
    // go through all children
    count_len(count->subchapters_,n);
    // print out the final sum
    cout << "Total length of " << id << " is " << n << "." << endl;
}

// recursively find the longest chapter in chapters given
void longest(std::vector<Chapter *>& chaps, int& len,std::string& top_id) {
    // go thorough all subchapters
    for (auto& chap : chaps) {
        // if chapter len is higher than previous record
        // then set new length, and mark id of longest chapter
        if (chap->length_ > len) {
            len = chap->length_;
            top_id = chap->id_;
        }

        // if chapter has children, go through them
        if (chap->subchapters_.size() != 0) {
            longest(chap->subchapters_,len,top_id);
        }
    }
}

// prints out the longest chapter in id or it's children
void Book::printLongestInHierarchy(Params params) const
{
    // get pointer
    std::string id = params[0];
    Chapter* top = fetch_chapter(id);

    // if no match, give error
    if (top == nullptr) {
        cout << "Error: Not found: " << id << endl;
        return;
    }

    // track longest chapter
    int len = 0;
    std::string top_id;
    longest(top->subchapters_,len,top_id);

    // if given id was longest print is different
    if (len <= top->length_) {
        cout << "With the length of " << top->length_ << ", " << id << " is the longest chapter in their hierarchy." << endl;
    } else {
        cout << "With the length of " << len << ", " << top_id << " is the longest chapter in " << id << "'s hierarchy." << endl;
    }
}
