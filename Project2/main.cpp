/*
Jim Counts
CS421 Theory of Computing
Project 2 - Due Wednesday April 18
Implement a parser that processes sequences of correctly paird ifs and elses in a C++ program.
There may be ifs without elses, but not elses without ifs.  Your parser must simulate a PDA.
*/
#include <iostream>
#include "Tests.h"
using namespace std;

// The main entry point for the application can be used to execute the parser or run unit tests.
int main( int argc, char *argv[] )
{
    Program p;
    bool runTests = p.ShouldRunTests( argc, argv );

    if ( runTests )
    {
        Tests t;
        t.RunTests();
    }
    else
    {
        p.Run();
    }

    return 0;
}
