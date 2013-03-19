/*
Jim Counts - CS421
Program.h
*/
#ifndef PROGRAM_H
#define PROGRAM_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "PushdownAutomata.h"

using namespace std;

// Provides a method to parse a file in the local directory called "sequence.txt".
// This class can also check the command line arguments to see if a test run was requested.
class Program
{
public:
    // Get an instance of the PDA which parses C++ if-else statements.
    PushdownAutomata GetProgramPDA()
    {
        vector<int> states;
        states.push_back( 0 );
        states.push_back( 1 );
        states.push_back( 2 );

        vector<char> inputAlphabet;
        inputAlphabet.push_back( 'i' );
        inputAlphabet.push_back( 'f' );
        inputAlphabet.push_back( 'e' );
        inputAlphabet.push_back( 'l' );
        inputAlphabet.push_back( 's' );

        vector<char> stackAlphabet;
        stackAlphabet.push_back( 'S' );
        stackAlphabet.push_back( 'A' );
        stackAlphabet.push_back( 'B' );
        stackAlphabet.push_back( 'C' );
        stackAlphabet.push_back( 'D' );
        stackAlphabet.push_back( 'E' );

        vector<TransitionRule> transitionRules;
        transitionRules.push_back( TransitionRule( 0, 'i', 'S', TransitionResult( 0, "AS" ) ) );
        transitionRules.push_back( TransitionRule( 0, 'f', 'A', TransitionResult( 1, "B" ) ) );
        transitionRules.push_back( TransitionRule( 1, 'i', 'S', TransitionResult( 1, "AS" ) ) );
        transitionRules.push_back( TransitionRule( 1, 'i', 'B', TransitionResult( 1, "AB" ) ) );
        transitionRules.push_back( TransitionRule( 1, 'f', 'A', TransitionResult( 1, "B" ) ) );
        transitionRules.push_back( TransitionRule( 1, 'e', 'B', TransitionResult( 2, "CDE" ) ) );
        transitionRules.push_back( TransitionRule( 2, 'l', 'C', TransitionResult( 2, "\0" ) ) );
        transitionRules.push_back( TransitionRule( 2, 's', 'D', TransitionResult( 2, "\0" ) ) );
        transitionRules.push_back( TransitionRule( 2, 'e', 'E', TransitionResult( 1, "\0" ) ) );

        int startState = 0;
        char initialStackSymbol = 'S';

        vector<int> acceptingStates;
        acceptingStates.push_back( 1 );

        return PushdownAutomata(
                   states,
                   inputAlphabet,
                   stackAlphabet,
                   transitionRules,
                   startState,
                   initialStackSymbol,
                   acceptingStates );
    }

    // Parse the file called "sequence.txt" in the local directory.
    void Run()
    {
        PushdownAutomata p = GetProgramPDA();
        p.ReadAllInput( Slurp( "sequence.txt" ) );

        if ( p.HasAcceptedInput() )
        {
            cout << "Correct sequence" << endl;
        }
        else
        {
            cout << "Sequence is syntactically incorrect" << endl;
        }
    }

    // Gets a value indicating whether the user requested tests from the command line.
    bool ShouldRunTests( int argc, char *argv[] )
    {
        string expected( "TEST" );

        if ( 1 < argc )
        {
            string actual( argv[1] );
            return expected.compare( actual ) == 0;
        }

        return false;
    }

    // Read all the contents of a text file into a string.
    string Slurp( string file )
    {
        ifstream in;
        in.open( file.c_str() );

        stringstream sstr;
        sstr << in.rdbuf();

        return sstr.str();
    }
};
#endif
