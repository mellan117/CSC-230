#include <iostream>
#include <queue>
using namespace std;

template <class T>
class MyStack {
    
    // define two instance variables
    // by default, they are private
    queue <T> first;
    queue <T> second;
    
public:
    // return the latest value of MyStack
    T top(){
        // please implement this method
        T val;
        
        if (second.empty()) {
            // Push all elements from 1st queue to 2nd que
            while (!first.empty()) {
                // Temporarily save current element
                val = first.front();
                second.push(val);
                first.pop();
            }
            
            // After the loop the val is the last element
            return val;
        } else if (first.empty()) {
            // Push all elements from 2nd queue to 1st que
            while (!second.empty()) {
                // Temporarily save current element
                val = second.front();
                first.push(val);
                second.pop();
            }
            
            // After the loop the val is the last element
            return val;
        }
        
        return val;
    }
    
    // add value val to MyStack
    void push(T val){
        // please implement this method
        first.push(val);
    }
    
    // remove the oldest value from MyStack
    void pop(){
        // please implement this method
        T val;
        
        if (second.empty()) {
            // Push all elements from 1st queue to 2nd que (except for the last element)
            while (!first.empty()) {
                val = first.front();
                first.pop();
                
                // Only push element to 2nd que if it is NOT the last element (aka 1st que is not empty)
                if (!first.empty()) {
                    second.push(val);
                }
            }
        } else if (first.empty()) {
            // Push all elements from 2nd queue to 1st que (except for the last element)
            while (!second.empty()) {
                val = second.front();
                second.pop();
                
                // Only push element to 1st que if it is NOT the last element (aka 2nd que is not empty)
                if (!second.empty()) {
                    first.push(val);
                }
            }
        }
    }
};
