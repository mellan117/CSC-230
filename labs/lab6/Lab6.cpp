/* Adam Mellan */
/* CSC 230     */
/* Lab 6       */

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

    // Prompt user for a ssn
    cout << "Input a SSN: ";
    cin >> ssnX;

    // Print index of entry with ssnX
    cout << "Found at location " << search(headNode, ssnX) << endl;

    return 0;
}