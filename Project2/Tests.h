/*
Jim Counts - CS 421
Tests.h
*/
#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <vector>
#include <stack>
#include <string.h>
#include <strings.h>
#include <sstream>
#include "Program.h"
#include "TransitionResult.h"
#include "TransitionRule.h"
#include "PushdownAutomata.h"

using namespace std;

// Provides a unit test harness and test methods for the types used in the PDA simulation.
class Tests
{
public:
    // Converts an integer into a string.
    string ToString( int i )
    {
        stringstream ss;
        string s;
        ss << i;
        s = ss.str();
        return s;
    }

    // Gets a message to note a single item in a sequence.
    string GetItemMessage( string message, int i )
    {
        message += " [";
        message += ToString( i );
        message += "]";
        return message;
    }

    // Gets a message to note the size of a sequence.
    string GetSizeMessage( string message )
    {
        return message += " SIZE";
    }

    // Prints PASS when the parameter is true, otherwise, false.
    void EQUALS( bool equals )
    {
        if ( equals )
        {
            cout << "PASS ";
        }
        else
        {
            cout << "FAIL ";
        }
    }

    // Prints pass/fail with a message.
    void BOOL_TRUE( bool value, string message )
    {
        EQUALS( value );
        cout << message << endl;
    }

    // Prints pass/fail with a message based on whether two characters are the same.
    void CHAR_EQUALS( char expected, char actual, string message )
    {
        EQUALS( expected == actual );
        cout << message << " Expected: [" << expected << "] Actual: [" << actual << "]" << endl;
    }

    // Prints pass/fail with a message based on whether two strings are the same.
    void STRING_EQUALS( string expected, string actual, string message )
    {
        EQUALS( expected.compare( actual ) == 0 );
        cout << message << " Expected: [" << expected << "] Actual: [" << actual << "]" << endl;
    }

    // Prints pass/fail with a message based on whether to integers are the same.
    void INT_EQUALS( int expected, int actual, string message )
    {
        EQUALS( expected == actual );
        cout << message << " Expected: [" << expected << "] Actual: [" << actual << "]" << endl;
    }

    // Evaluates two integer sequences and prints messages based on whether they are the same.
    void INT_SEQUENCE_EQUALS( vector<int> expected, vector<int> actual, string message )
    {
        INT_EQUALS( expected.size(), actual.size(), GetSizeMessage( message ) );

        if ( expected.size() == actual.size() )
        {
            for ( unsigned int i = 0; i < expected.size(); i++ )
            {
                INT_EQUALS( expected[i], actual[i], GetItemMessage( message, i ) );
            }
        }
    }

    // Evaluates two character sequences and prints messages based on whether they are the same.
    void CHAR_SEQUENCE_EQUALS( vector<char> expected, vector<char> actual, string message )
    {
        INT_EQUALS( expected.size(), actual.size(), GetSizeMessage( message ) );

        if ( expected.size() == actual.size() )
        {
            for ( unsigned int i = 0; i < expected.size(); i++ )
            {
                CHAR_EQUALS( expected[i], actual[i], GetItemMessage( message, i ) );
            }
        }
    }

    // Evaluates two TransitionRule sequences and prints messages based on whether they are the same.
    void TRANSITIONRULE_SEQUENCE_EQUALS( vector<TransitionRule> expected, vector<TransitionRule> actual, string message )
    {
        INT_EQUALS( expected.size(), actual.size(), GetSizeMessage( message ) );

        if ( expected.size() == actual.size() )
        {
            for ( unsigned int i = 0; i < expected.size(); i++ )
            {
                BOOL_TRUE( expected[i] == actual[i], GetItemMessage( message, i ) );
            }
        }
    }

    // Evaluates two character stacks and prints messages based on whether they are the same.
    void CHAR_STACK_EQUALS( stack<char> expected, stack<char> actual, string message )
    {
        INT_EQUALS( expected.size(), actual.size(), GetSizeMessage( message ) );

        if ( expected.size() == actual.size() )
        {
            int i = 0;

            while ( !expected.empty() )
            {
                CHAR_EQUALS( expected.top(), actual.top(), GetItemMessage( message, i++ ) );
                expected.pop();
                actual.pop();
            }
        }
    }

    // ShouldRunTests should return true when "TEST" is passed on the command line.
    void GetTestParameter()
    {
        Program p;
        int argc = 2;

        string program( "Program" );
        char prg[program.size() + 1];
        bzero( prg, program.size() + 1 );
        memcpy( prg, program.c_str(), program.size() );

        string test( "TEST" );
        char t[test.size() + 1];
        bzero( t, test.size() + 1 );
        memcpy( t, test.c_str(), test.size() );

        char *argv[] = { prg, t };

        BOOL_TRUE( p.ShouldRunTests( argc, argv ), "GetTestParameter" );
    }

    // ShouldRunTests should return false when "TEST" is not passed on the command line.
    void DoNotGetTestParameter()
    {
        Program p;
        int argc = 1;

        string arg( "Program" );
        char a[arg.size() + 1];
        bzero( a, arg.size() + 1 );
        memcpy( a, arg.c_str(), arg.size() );

        char *argv[] = { a };

        BOOL_TRUE( !p.ShouldRunTests( argc, argv ), "DoNotGetTestParameter" );
    }

    // ShouldRunTests should return false when some other value is passed on the command line.
    void NotTestParameter()
    {
        Program p;
        int argc = 2;

        string program( "Program" );
        char prg[program.size() + 1];
        bzero( prg, program.size() + 1 );
        memcpy( prg, program.c_str(), program.size() );

        string test( "FOO" );
        char t[test.size() + 1];
        bzero( t, test.size() + 1 );
        memcpy( t, test.c_str(), test.size() );

        char *argv[] = { prg, t };

        BOOL_TRUE( !p.ShouldRunTests( argc, argv ), "NotTestParameter" );
    }

    // Test that the TransitionResult class initialzies correctly.
    void ApproveTransitionResult()
    {
        string expectedPushList = string( "az" );
        TransitionResult t = TransitionResult( 0, expectedPushList );

        INT_EQUALS( 0, t.GetState(), "TransitionRule.GetState" );
        STRING_EQUALS( expectedPushList, t.GetPushList(), "TransitionResult.PushList" );
    }

    // Test the == operator on TransitionResult.
    void TransitionResultEquality()
    {
        TransitionResult expected = TransitionResult( 0, "az" );
        TransitionResult actual = expected;
        BOOL_TRUE( expected == actual, "TransitionResult==" );
    }

    // Test the != operator on TransitionResult.
    void TransitionResultInequality()
    {
        TransitionResult expected = TransitionResult( 0, "az" );
        TransitionResult actual = TransitionResult( 1, "aa" );
        BOOL_TRUE( expected != actual, "TransitionResult!=" );
    }

    // Test that the TransitionRule class initializes correctly.
    void ApproveTransitionRule()
    {
        TransitionResult result = TransitionResult( 1, "az" );
        TransitionRule r = TransitionRule( 0, 'a', 'z', result );

        INT_EQUALS( 0, r.GetState(), "TransitionRule.GetState" );
        CHAR_EQUALS( 'a', r.GetInputChar(), "TransitionRule.GetInputChar" );
        CHAR_EQUALS( 'z', r.GetStackInputChar(), "TransitionRule.GetStackInputChar" );
        BOOL_TRUE( result == r.GetResult(), "TransitionRule.GetResult" );
    }

    // Test that the TransitionRule class updates its result after initialization.
    void AddTransitionResultToTransitionRule()
    {
        TransitionResult expectedResult = TransitionResult( 1, "az" );
        TransitionRule r = TransitionRule( 0, 'a', 'z' );
        r.AddResult( 1, "az" );

        INT_EQUALS( 0, r.GetState(), "AddToTransitionRule.GetState" );
        CHAR_EQUALS( 'a', r.GetInputChar(), "AddToTransitionRule.GetInputChar" );
        CHAR_EQUALS( 'z', r.GetStackInputChar(), "AddToTransitionRule.GetStackInputChar" );
        BOOL_TRUE( expectedResult == r.GetResult(), "AddToTransitionRule.GetResult" );
    }

    // Returns a TransitionRule instance for testing.
    TransitionRule GetTransitionRule()
    {
        TransitionRule t = TransitionRule( 0, 'a', 'z' );
        t.AddResult( 1, "az" );
        return t;
    }

    // Tests the == operator on TransitionRule.
    void TransitionRuleEquality()
    {
        TransitionRule expected = GetTransitionRule();
        TransitionRule actual = expected;
        BOOL_TRUE( expected == actual, "TransitionRule==" );
    }

    // Tests the != operator on TransitionRule.
    void TransitionRuleInequality()
    {
        TransitionRule expected = GetTransitionRule();
        TransitionRule actual = GetTransitionRule();
        actual.AddResult( 0, "\0" );
        BOOL_TRUE( expected != actual, "TransitionRule!=" );
    }

    // Gets a collection of states to use when testing.
    vector<int> GetStates()
    {
        vector<int> states;
        states.push_back( 0 );
        states.push_back( 1 );
        return states;
    }

    // Gets an alphabet to use when testing.
    vector<char> GetInputAlphabet()
    {
        vector<char> inputAlphabet;
        inputAlphabet.push_back( 'a' );
        inputAlphabet.push_back( 'b' );
        return inputAlphabet;
    }

    // Gets an alphabet to use on the stack when testing.
    vector<char> GetStackAlphabet()
    {
        vector<char> stackAlphabet;
        stackAlphabet.push_back( 'a' );
        stackAlphabet.push_back( 'b' );
        return stackAlphabet;
    }

    // Gets a collection of TransitionRules to use when testing.
    vector<TransitionRule> GetTransitionRules()
    {
        vector<TransitionRule> rules;
        TransitionRule t1 = TransitionRule( 0, 'a', 'z' );
        t1.AddResult( 1, "az" );
        rules.push_back( t1 );
        TransitionRule t2 = TransitionRule( 0, 'b', 'z' );
        t2.AddResult( 1, "bz" );
        rules.push_back( t2 );
        TransitionRule t3 = TransitionRule( 1, 'a', 'a' );
        t3.AddResult( 0, "\0" );
        rules.push_back( t3 );
        TransitionRule t4 = TransitionRule( 1, 'b', 'b' );
        t4.AddResult( 0, "\0" );
        rules.push_back( t4 );
        return rules;
    }

    // Gets the start state to use when testing.
    int GetStartState()
    {
        return 0;
    }

    // Gets the symbol to place on the bottom of the stack when testing.
    char GetInitialStackSymbol()
    {
        return 'z';
    }

    // Gets the acceptance states to use when testing.
    vector<int> GetAcceptingStates()
    {
        vector<int> acceptingStates;
        acceptingStates.push_back( 0 );
        return acceptingStates;
    }

    // Gets a PDA to use when testing.
    PushdownAutomata GetPushdownAutomata()
    {
        return PushdownAutomata( GetStates(), GetInputAlphabet(), GetStackAlphabet(), GetTransitionRules(), GetStartState(), GetInitialStackSymbol(), GetAcceptingStates() );
    }

    // Approve the structure of the Test PDA.
    void ApprovePushdownAutomata()
    {
        vector<int> states = GetStates();
        vector<char> inputAlphabet = GetInputAlphabet();
        vector<char> stackAlphabet = GetStackAlphabet();
        vector<TransitionRule> rules = GetTransitionRules();
        int startState = GetStartState();
        char initialStackSymbol = GetInitialStackSymbol();
        vector<int> acceptingStates = GetAcceptingStates();

        stack<char> expectedStack;
        expectedStack.push( initialStackSymbol );

        PushdownAutomata p = PushdownAutomata( states, inputAlphabet, stackAlphabet, rules, startState, initialStackSymbol, acceptingStates );
        INT_SEQUENCE_EQUALS( states, p.GetStates(), "PushdownAutomata.GetStates" );
        CHAR_SEQUENCE_EQUALS( inputAlphabet, p.GetInputAlphabet(), "PushdownAutomata.GetInputAlphabet" );
        CHAR_SEQUENCE_EQUALS( stackAlphabet, p.GetStackAlphabet(), "PushdownAutomata.GetStackAlphabet" );
        TRANSITIONRULE_SEQUENCE_EQUALS( rules, p.GetTransitionRules(), "PushdownAutomata.GetTransitionRules" );
        INT_EQUALS( startState, p.GetStartState(), "PushdownAutomata.GetStartState" );
        CHAR_EQUALS( initialStackSymbol, p.GetInitialStackSymbol(), "PushdownAutomata.GetInitialStackSymbol" );
        INT_SEQUENCE_EQUALS( acceptingStates, p.GetAcceptingStates(), "PushdownAutomata.GetAcceptingStates" );
        INT_EQUALS( startState, p.GetState(), "PushdownAutomata.GetState" );
        CHAR_STACK_EQUALS( expectedStack, p.GetStack(), "PushdownAutomata.GetStack" );
        BOOL_TRUE( p.HasAcceptedInput(), "PushdownAutomata.HasAcceptedInput" );
    }

    // Approve the state of the Test PDA after reading one character.
    void ReadInput()
    {
        stack<char> expectedStack;
        expectedStack.push( 'z' );
        expectedStack.push( 'a' );

        PushdownAutomata p = GetPushdownAutomata();
        p.ReadInput( 'a' );

        INT_EQUALS( 1, p.GetState(), "Read 'a' state" );
        CHAR_STACK_EQUALS( expectedStack, p.GetStack(), "Read 'a' stack" );
        BOOL_TRUE( !p.HasAcceptedInput(), "Read 'a' result" );
    }

    // Approve the Test PDA state after the machine reads input for which no rule matches.
    void DetectDeadConfiguration()
    {
        PushdownAutomata p = GetPushdownAutomata();
        p.ReadInput( 'c' );
        BOOL_TRUE( !p.HasAcceptedInput(), "Dead configuration." );
    }

    // Approve the Test PDA state after the machine reads invalid input followed by valid input.
    void RemainDead()
    {
        PushdownAutomata p = GetPushdownAutomata();
        p.ReadInput( 'c' );
        p.ReadInput( 'a' );
        p.ReadInput( 'a' );
        BOOL_TRUE( !p.HasAcceptedInput(), "Remain Dead." );
    }

    // Approve the Test PDA state after the machine reads valid input.
    void AcceptInput()
    {
        stack<char> expectedStack;
        expectedStack.push( 'z' );

        PushdownAutomata p = GetPushdownAutomata();
        p.ReadInput( 'a' );
        p.ReadInput( 'a' );

        INT_EQUALS( 0, p.GetState(), "Read 'aa' state." );
        CHAR_STACK_EQUALS( expectedStack, p.GetStack(), "Read 'aa' stack" );
        BOOL_TRUE( p.HasAcceptedInput(), "Read 'aa' result." );
    }

    // Test several valid input strings.
    void AcceptPermutations()
    {
        string permutations[] = { "aaaa", "aabb", "bbbb", "bbaa" };

        for ( int i = 0; i < 4; i++ )
        {
            PushdownAutomata pa = GetPushdownAutomata();
            pa.ReadAllInput( permutations[i] );
            BOOL_TRUE( pa.HasAcceptedInput(), permutations[i] );
        }
    }

    // Test several invalid input strings.
    void RejectPermutations()
    {
        string permutations[] = { "a", "b", "ab", "ba", "aaa", "aab", "abb", "bbb", "bba", "baa", "aaab",
                                  "abbb", "bbba", "baaa"
                                };

        for ( int i = 0; i < 14; i++ )
        {
            PushdownAutomata pa = GetPushdownAutomata();
            pa.ReadAllInput( permutations[i] );
            BOOL_TRUE( !pa.HasAcceptedInput(), permutations[i] );
        }
    }

    // Get the PDA for the if-else statement.
    PushdownAutomata GetSelectionPDA()
    {
        Program p;
        return p.GetProgramPDA();
    }

    // Method for ad-hoc excersices with the if-else PDA.
    void SelectionPDA()
    {
        PushdownAutomata pa = GetSelectionPDA();
        BOOL_TRUE( !pa.HasAcceptedInput(), "SelectionPDA" );
    }

    // Test the if-else PDA with several valid and invalid strings.
    void ApproveSelectionPDA()
    {
        string permutations[] = { "if", "ifif", "ififelse", "ififelseif", "ififelseifelse", "ifelse", "ififelseelse",
                                  "ifelseif", "ifelseifelse", "ififelseelseififelseelse"
                                };
        int ps = sizeof( permutations ) / sizeof( string );

        for ( int i = 0; i < ps; i++ )
        {
            PushdownAutomata pa = GetSelectionPDA();
            pa.ReadAllInput( permutations[i] );
            BOOL_TRUE( pa.HasAcceptedInput(), permutations[i] );
        }

        string unacceptable[] = { "\0", "else", "ifelseelse", "ifelseelseif" };
        int us = sizeof( unacceptable ) / sizeof( string );

        for ( int j = 0; j < us; j++ )
        {
            PushdownAutomata pa = GetSelectionPDA();
            pa.ReadAllInput( unacceptable[j] );
            BOOL_TRUE( !pa.HasAcceptedInput(), unacceptable[j] );
        }
    }

    // Run all the tests.
    void RunTests()
    {
        GetTestParameter();
        DoNotGetTestParameter();
        NotTestParameter();
        ApproveTransitionResult();
        TransitionResultEquality();
        TransitionResultInequality();
        ApproveTransitionRule();
        AddTransitionResultToTransitionRule();
        TransitionRuleEquality();
        TransitionRuleInequality();
        ApprovePushdownAutomata();
        ReadInput();
        DetectDeadConfiguration();
        RemainDead();
        AcceptInput();
        AcceptPermutations();
        RejectPermutations();
        SelectionPDA();
        ApproveSelectionPDA();
    }
};
#endif
