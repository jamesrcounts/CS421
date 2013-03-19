/*
Jim Counts - CS 421
TransitionResult.h
*/
#include <string>

#ifndef TRANSITIONRESULT_H
#define TRANSITIONRESULT_H
using namespace std;

// Provides a description of the state changes a machine can make in response to matching a rule.
class TransitionResult
{
    // The state the machine should move to.
    int resultState;

    // The symbols the machine should push onto the stack.
    string stackPushList;

public:
    // Initializes a new instance of the TransitionResult class.
    TransitionResult()
    {
        resultState = 0;
        stackPushList = "\0";
    }

    // Initalizes a new instance of the TransitionResult class.
    // state: the state the machine should move to.
    // pushList: the symbols the machine should push onto the stack.
    TransitionResult( int state, string pushList )
    {
        resultState = state;
        stackPushList = pushList;
    }

    // Gets a value indicating whether this instance represents the same data as param.
    // param: the TransitionResult to compare this instance to.
    // Returns true if the instances represent the same data; otherwise false.
    bool operator==( const TransitionResult &param )
    {
        return this == &param || ( stackPushList.compare( param.stackPushList ) == 0 && resultState == param.resultState );
    }

    // Gets a value indicating whether this instance does not represent the same data as param.
    // param: the TransitionResult to compare this instance to.
    // Returns true if the instances do not represent the same data; otherwise false.
    bool operator!=( const TransitionResult &param )
    {
        return !( *this == param );
    }

    // Gets the list of symbols the machine should push onto the stack.
    string GetPushList()
    {
        return stackPushList;
    }

    // Gets the state the machine should move to.
    int GetState()
    {
        return resultState;
    }
};
#endif
