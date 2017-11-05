#include <iostream>
#include <stack>
using namespace std;

template <class T>
class MyQueue {
    // these two stck are instance variables
    // by default, the access is private
    stack<T> first;
    stack<T> second;
    
public:
    
    // return the value of the oldest member
    T front(){
        // please implement this method
        if (second.empty()) {
            // Push all elements from 1st stack to 2nd stack
            while (!first.empty()) {
                second.push(first.top());
                first.pop();
            }
            // After the loop the order of the stack is now reversed
            // aka the last element in the 2nd stack WAS the first element in the 1st stack
        }
        return second.top();
    }
    
    // add value val to MyQueue
    void push(T val){
        // please implement this method
        first.push(val);
    }
    
    
    // remove the oldest member from MyQueue
    void pop(){
        // please implement this method
        second.pop();
    }
};
