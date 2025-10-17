// COMSC-210 | Midterm 1 | Jasmine Suarez
// IDE used: VS Code

#include <iostream>
#include <cstdlib> // srand(), rand()
#include <ctime>   // time()
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// defines class DoublyLinkedList, represents a doubly-linked list
class DoublyLinkedList {
private:
    // a struct named Node
    struct Node {
        int data;       // stores the value in the node
        Node* prev;     // pointer to previous node in list
        Node* next;     // pointer to next node in list
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;     // pointer to head (first) node in list
    Node* tail;     // pointer to tail (last) node in list

public:
    // default constructor, which initializes head and tail to nullptr (empty)
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // a function which inserts a new node with a value and after a certain position
    void insert_after(int value, int position) {
        // checks to make sure position is valid
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        // creates new node with given value
        Node* newNode = new Node(value);
        if (!head) {                    // this means if the list is empty
            head = tail = newNode;      // the new node value is both head and tail
            return;
        }

        // starts at the head (front)
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)  // for-loop goes through however
            temp = temp->next;                      // many position steps forward

        // if position out of bounds,
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;     // deletes new node
            return;
        }

        // links the new node into list
        newNode->next = temp->next;     // new node points forward to temps next node
        newNode->prev = temp;           // new node points backwards to temp
        if (temp->next)                 // if temp has a node after it,
            temp->next->prev = newNode; // next node's previous pointer will now point to new node
        else                            // if temp was the last node (tail),
            tail = newNode;             // the tail is now the new node
        temp->next = newNode;           // temps next points to new node
    }

    // function which deletes a node, given a specific value
    void delete_val(int value) {
        if (!head) return; // if the list is empty, return

        Node* temp = head; // temp is assigned to head, start at the head
        
        while (temp && temp->data != value) // traverses until value is found or end of list
            temp = temp->next;

        if (!temp) return; // returns if value not found

        if (temp->prev)                     // if temp isn't the first node
            temp->prev->next = temp->next;  // skip temp and go to next node
        else
            head = temp->next;              // else if temp is head, move head to next node

        if (temp->next)                     // if temp isn't the last node
            temp->next->prev = temp->prev;  // skip temp and go the previous node
        else
            tail = temp->prev;              // else if temp is tail, move tail to prev node

        delete temp;                        // frees memory
    }

    // function that deletes node at a specific position
    void delete_pos(int pos) {
        if (!head) {    // if list empty
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {     // removes first node
            pop_front();
            return;
        }
    
        Node* temp = head;  // start from head
    
        // for-loop moves until hits position
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {    // if position exceeds list length
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        // removes last node
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    // function which add a value to end of list
    void push_back(int v) {
        Node* newNode = new Node(v);    // creates new node
        if (!tail)                      // if list empty
            head = tail = newNode;      // new node is equal to head and tail
        else {
            tail->next = newNode;       // current tail points to new node
            newNode->prev = tail;       // new node points to old tail
            tail = newNode;             // updates tail to new node
        }
    }
    
    // function which adds a value to front of list
    void push_front(int v) {
        Node* newNode = new Node(v);    // creates new node
        if (!head)                      // if list empty
            head = tail = newNode;      // new node is equal to head and tail
        else {
            newNode->next = head;       // new node points next to old head
            head->prev = newNode;       // old head points previously to new node
            head = newNode;             // updates head to new node
        }
    }
    
    // removes first node of the list
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    // removes last node of the list
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    // destructor
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // prints list from head to tail
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // prints list from tail to head
    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // prints every other element
    void every_other_element() {
        Node* current = head;       // start at head
        if (!current) {             // returns if list is empty
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " "; // prints the value of the current node
            if (current->next)  // if there is another node after current
                current = current->next->next; // set current equal to the next, next node
            else
                return;     // returns if there isn't a next node
        }
        cout << endl;
    }
};

int main() {
    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS; // randomizes size of list

    for (int i = 0; i < size; ++i) // adds random values into the list of randomized size
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List every other element: ";
    list.every_other_element();
    
    return 0;
}