/*
Jim Counts - CS 421
PushdownAutomata.h
*/
#ifndef PUSHDOWNAUTOMATA_H
#define PUSHDOWNAUTOMATA_H

#include <vector>
#include <stack>
#include "TransitionRule.h"

using namespace std;

// Provides a simulation of a pushdown automata.
class PushdownAutomata
{
    // A collection of states the machine can assume.
    vector<int> machineStates;

    // A collection of characters in the language accepted by the machine.
    vector<char> machineInputAlphabet;

    // A collection of characters used on the machine stack.
    vector<char> machineStackAlphabet;

    // A collection of transition rules used by the control unit to determine the next
    // machine state.
    vector<TransitionRule> machineTransitionRules;

    // The machine starting state.
    int machineStartState;

    // The current machine state.
    int currentState;

    // The symbol at the bottom of the machine stack.
    char machineInitialStackSymbol;

    // When the machine halts in a state contained in this collection; the machine has accepted the input.
    vector<int> machineAcceptingStates;

    // The machine storage stack.
    stack<char> machineStack;

    // Attempt to match a rule against the input character and the stack character.
    // If a match is made, then make changes to the machine state indicated by the rule's result.
    // inputCharacter: the character read from the input
    // stackCharacter: the character removed from the top of the stack
    // rule: the rule to match.
    // Returns true if the rule was matched and processed; otherwise false.
    bool RuleMatchAndProcess( char inputCharacter, char stackCharacter, TransitionRule rule )
    {
        if ( currentState != rule.GetState() )
        {
            return false;
        }

        if ( inputCharacter != rule.GetInputChar() )
        {
            return false;
        }

        if ( stackCharacter != rule.GetStackInputChar() )
        {
            return false;
        }

        TransitionResult result = rule.GetResult();

        currentState = result.GetState();

        string pushList = result.GetPushList();
        string::reverse_iterator rit;

        for ( rit = pushList.rbegin() ; rit < pushList.rend(); ++rit )
        {
            machineStack.push( *rit );
        }

        return true;
    }

public:
    // Initializes a new instance of the PushdownAutomata class.
    // states: The states which the machine can assume.
    // inputAlphabet: The characters in the language accepted by the machine.
    // stackAlphabet: The characters used by the machine to manage state on the internal stack mechanism.
    // rules: The tranistion rules which control state changes within the machine.
    // startState: The first state assumed by the machine.
    // initialStackSymbol: The symbol on the bottom of the machine stack.
    // machineAcceptingStates: The machine states which indicate the input is in the language.
    PushdownAutomata( vector<int> states, vector<char> inputAlphabet, vector<char> stackAlphabet, vector<TransitionRule> rules, int startState, char initialStackSymbol, vector<int> acceptingStates )
    {
        machineStates = states;
        machineInputAlphabet = inputAlphabet;
        machineStackAlphabet = stackAlphabet;
        machineTransitionRules = rules;
        machineStartState = startState;
        currentState = startState;
        machineInitialStackSymbol = initialStackSymbol;
        machineStack.push( machineInitialStackSymbol );
        machineAcceptingStates = acceptingStates;
    }

    // Gets a collection of states which the machine can assume.
    vector<int> GetStates()
    {
        return machineStates;
    }

    // Gets a collection of characters in the language accepted by the machine.
    vector<char> GetInputAlphabet()
    {
        return machineInputAlphabet;
    }

    // Gets a collection of characters used by the machine to manage state on the internal stack.
    vector<char> GetStackAlphabet()
    {
        return machineStackAlphabet;
    }

    // Gets a collection of rules describing moves the machine can make in repsonse to input.
    vector<TransitionRule> GetTransitionRules()
    {
        return machineTransitionRules;
    }

    // Gets the current machine state.
    int GetState()
    {
        return currentState;
    }

    // Gets the initial machine state.
    int GetStartState()
    {
        return machineStartState;
    }

    // Gets the symbol on the bottom of the machine stack.
    char GetInitialStackSymbol()
    {
        return machineInitialStackSymbol;
    }

    // Gets the states which indicate the input is accepted by the machine.
    vector<int> GetAcceptingStates()
    {
        return machineAcceptingStates;
    }

    // Gets a copy of the machine's internal stack.
    stack<char> GetStack()
    {
        return machineStack;
    }

    // Gets a value indicating whether the machine has accepted the input.
    bool HasAcceptedInput()
    {
        for ( int i = 0; i < ( int )machineAcceptingStates.size(); i++ )
        {
            if ( machineAcceptingStates[i] == currentState )
            {
                return true;
            }
        }

        return false;
    }

    // Read a single character from the input and change state if appropriate.
    // inputCharacter: The character read from the input.
    void ReadInput( char inputCharacter )
    {
        // Short circuit when configuration is dead.
        if ( currentState == -1 )
        {
            return;
        }

        int i = 0;
        char s = machineStack.top();
        machineStack.pop();

        for ( ; i < ( int )machineTransitionRules.size(); i++ )
        {
            if ( RuleMatchAndProcess( inputCharacter, s, machineTransitionRules[i] ) )
            {
                break;
            }
        }

        if ( i == ( int )machineTransitionRules.size() )
        {
            // Dead configuration
            currentState = -1;
        }
    }

    // Iterate over each character in the input string and process it using the ReadInput method.
    // w: the input string.
    void ReadAllInput( string w )
    {
        string::iterator it;

        for ( it = w.begin() ; it < w.end(); ++it )
        {
            ReadInput( *it );
        }
    }
};
#endif
