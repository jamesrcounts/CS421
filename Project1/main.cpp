//-----------------------------------------------------------------------
// <copyright file="Main.cpp" company="Jim Counts and Michael Nguyen">
//     Copyright (c) Jim Counts and Michael Nguyen 2011. All rights reserved.
// </copyright>
//-----------------------------------------------------------------------
#include "Union.h"
#include "StateMachineFactory.h"
#include <algorithm>
#include <dirent.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/// <summary>
/// Lists all files in a directory
/// </summary>
/// <param name="directoryPath">The directory path.</param>
/// <returns>A collection of file paths found in the directory.</returns>
vector<string> GetFiles( string directoryPath )
{
    vector<string> paths;
    struct dirent *ent;
    DIR *dir = opendir( directoryPath.c_str() );

    if ( dir != NULL )
    {
        while ( ( ent = readdir( dir ) ) != NULL )
        {
            string fileName( ent->d_name );

            if ( fileName.compare( "." ) != 0 &&  fileName.compare( ".." ) != 0 )
            {
                string filePath( directoryPath );
                filePath.append( "/" );
                filePath.append( fileName );
                paths.push_back( filePath );
            }
        }

        closedir( dir );
    }
    else
    {
        perror( "Invalid directory" );
    }

    return paths;
}

/// <summary>
/// Slurps the specified file.
/// </summary>
/// <param name="file">The file.</param>
/// <returns>The contents of the file.</returns>
string Slurp( string file )
{
    ifstream in;
    in.open( file.c_str() );
    stringstream sstr;
    sstr << in.rdbuf();
    string allText = sstr.str();
    transform( allText.begin(), allText.end(), allText.begin(), ::tolower );
    string punctuation = "'[](){}:,-_.!?\";\\/@#$%^&*+|~`<>";
    string result;

    for ( int i = 0; i < ( int )allText.size(); i++ )
    {
        char p = allText[i];

        if ( punctuation.find_first_of( p ) == string::npos )
        {
            result.push_back( p );
        }
    }

    return result;
}

/// <summary>
/// Creates the union machine.
/// </summary>
/// <returns>A union machine that accepts operating room or operating system.</returns>
Union CreateUnionMachine()
{
    StateMachineFactory factory;

    return Union(
               factory.CreateMachine( "operating room" ),
               factory.CreateMachine( "operating system" ) );
}

/// <summary>
/// The main entry point for the test program.
/// </summary>
int main( int argc, char *argv[] )
{
    vector<string> files = GetFiles( "./TestFiles" );

    for ( int i = 0; i < ( int )files.size(); i++ )
    {
        string readAllText = Slurp( files[i] );
        Union unionMachine = CreateUnionMachine();
        unionMachine.ReadAllInput( readAllText );

        if ( unionMachine.AcceptedInput() )
        {
            cout << "Accepted: " << files[i] << endl;
        }
    }

    return 0;
}