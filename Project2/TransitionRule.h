/*
Jim Counts - CS 421
TransitionRule.h
*/
#include "TransitionResult.h"

#ifndef TRANSITIONRULE_H
#define TRANSITIONRULE_H

// Provides a relationship between the input read, the machine's current state, and result states the machine
// should move to.
class TransitionRule
{
    // The machine's current state.
    int initialState;

    // The character read from the input.
    char inputCharacter;

    // The character removed from the stack.
    char stackInputCharacter;

    // The state changes the machine should make when state, input, and stack, match the values defined in this
    // instance.
    TransitionResult result;

public:
    // Initializes a new instance of the TransitionRule class.
    // state: The machine's current state.
    // input: The character read from the input.
    // stackInput: The character removed from the stack.
    TransitionRule( int state, char input, char stackInput ) :
        initialState( state ),
        inputCharacter( input ),
        stackInputCharacter( stackInput )
    {
    }

    // Initializes a new instance of the TransitionRule class.
    // state: The machine's current state.
    // input: The character read from the input.
    // stackInput: The character removed from the stack.
    // ruleResult: The state changes the machine should make when this rule is
    // matched.
    TransitionRule( int state,
                    char input,
                    char stackInput,
                    TransitionResult ruleResult ) :
        initialState( state ),
        inputCharacter( input ),
        stackInputCharacter( stackInput ),
        result( ruleResult )
    {
    }

    // Gets a value indicating whether this instance and param represent the same data.
    // param: The instance to compare this to.
    // Returns true if this instance and param represent the same data; otherwise false.
    bool operator==( const TransitionRule &param )
    {
        return this == &param || ( initialState == param.initialState &&	inputCharacter == param.inputCharacter && stackInputCharacter == param.stackInputCharacter && result == param.result );
    }

    // Gets a value indicating whether this instance and param represent different data.
    // param: The instance to compare this to.
    // Returns true if this instance and param represent different data; otherwise false.
    bool operator!=( const TransitionRule &param )
    {
        return !( *this == param );
    }

    // Adds or changes the state changes which the machine should make if this rule is matched.
    // state: the state the machine should assume.
    // pushList: the symbols the machine should push onto the stack.
    void AddResult( int state, string pushList )
    {
        result = TransitionResult( state, pushList );
    }

    // Gets the state the machine should be in for this rule to match.
    int GetState()
    {
        return initialState;
    }

    // Gets the input character the machine should have read for this rule to match.
    char GetInputChar()
    {
        return inputCharacter;
    }

    // Gets the character the machine should have removed from the stack for this rule to match.
    char GetStackInputChar()
    {
        return stackInputCharacter;
    }

    // Gets the state changes the machine should make when this rule is matched.
    TransitionResult GetResult()
    {
        return result;
    }
};
#endif
