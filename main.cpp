#include <iostream>
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

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
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

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
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
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}