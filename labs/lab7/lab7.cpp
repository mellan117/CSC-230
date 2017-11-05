/* Adam Mellan */
/* CSC 230     */
/* Lab 7       */

#include <iostream>
#include <fstream>

using namespace std;

// Declare a structure containing personal info
struct Person{
    string ssn;
    string fullName;
};

// Declare a node structure
struct Node{
    Person person;
    Node *next;
};

void display(Node *&head) {
    Node *currNode = head;
    while (currNode != NULL) {
        cout << currNode->person.fullName << endl;
    }
}

void insert(Node *&head, Person p) {
    // Init new node with new data
    Node *newNode = new Node;
    newNode->person = p;
    newNode->next = NULL;
    
    int index = 0;
    
    if (head == NULL) { // If list is empty then new node becomes head
        head = newNode;
    } else {
        // Iterate through list
        Node *currNode = head;
        while (currNode != NULL) {
            if (currNode->person.ssn != newNode->person.ssn) { // Check if ssn is already in list
                
                if (currNode->person.ssn < newNode->person.ssn && currNode->next != NULL) { // Node should be inserted later in list
                    currNode = currNode->next;
                } else {
                    // Node should be inserted at this index
                    //
                    if (currNode->next == NULL && currNode->person.ssn < newNode->person.ssn) { // Insert at end of list
                        currNode->next = newNode;
                        
                        break;
                    } else if (index == 0) { // Insert at beginning of list
                        newNode->next = currNode;
                        head = newNode;
                        
                    } else { // Insert in middle of list
                        newNode->next = currNode;
                    }
                }
            }
            index++;
        }
    }
}

void append(Node *&head, Person p) {
    // Init new node with new data
    Node *newNode = new Node;
    newNode->person = p;
    newNode->next = NULL;
    
    if (head == NULL) { // Check if linked list is empty
        head = newNode; // If empty make new node the head
    } else {
        // Create temp node
        Node *temp = head;
        // Iterate through linked list
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode; // Append the new node to the end of the linked list
    }
}

int search(Node *&head, string ssnX) {
    // Declare variables
    Node *temp = head;
    string ssn;
    int index;
    
    // Iterate though the linked list
    while (temp != NULL) {
        if (ssnX == temp->person.ssn) { // Check if the node is in the linked list
            return index; // Return the found node's index
        }
        temp = temp->next;
        index++;
    }
    
    return -1; // Node not found
}

int main(int argc, char *argv[]) {
    // Declare variables
    Node *headNode = NULL;
    string ssnX;
    
    // Create input stream from file
    fstream input(argv[1]);
    while (!input.eof()) {
        // Declare temp entry
        struct Person tempPerson;
        string option;
        string firstName, lastName;
        
        // Init temp entry
        input >> option >> tempPerson.ssn >> firstName >> lastName;
        tempPerson.fullName = firstName + " " + lastName;
        
        // Append entry to the end of the linked list
        append(headNode, tempPerson);
    }
    input.close();
    
    display(headNode);
    
    // Prompt user for a ssn
    /*cout << "Input a SSN: ";
    cin >> ssnX;
    
    // Print index of entry with ssnX
    cout << "Found at location " << search(headNode, ssnX) << endl;*/
    
    return 0;
}