e//-----------------------------------------------------------------------
// <copyright file="Machine.cs" company="Jim Counts and Michael Nguyen">
//     Copyright (c) Jim Counts and Michael Nguyen 2011. All rights reserved.
// </copyright>
//-----------------------------------------------------------------------
#ifndef _MACHINE_H
#define _MACHINE_H

#include "IFiniteStateMachine.h"
#include "TransitionRule.h"
#include <vector>
#include <algorithm>
#include <iostream>

/// <summary>
/// A finite automata.
/// </summary>
class Machine : public IFiniteStateMachine
{
private:
    /// <summary>
    /// The transition function.
    /// </summary>
    vector<TransitionRule> TransitionRules;

    /// <summary>
    /// The set of final states.
    /// </summary>
    vector<int> FinalStates;

    /// <summary>
    /// The current machine state.
    /// </summary>
    int currentState;

public:

    Machine()
    {
        currentState = 0;
    }

    /// <summary>
    /// Initializes a new instance of the <see cref="Machine"/> class.
    /// </summary>
    /// <param name="initialState">The initial state.</param>
    /// <param name="transitionRules">The transition rules.</param>
    /// <param name="finalStates">The final states.</param>
    Machine( int initialState, vector<TransitionRule> transitionRules, vector<int> finalStates )
    {
        FinalStates = finalStates;
        TransitionRules = transitionRules;
        currentState = initialState;
    }

    /// <summary>
    /// Cleans up this instance of <see cref="Machine" />
    /// </summary>
    virtual ~Machine()
    {
    }

    /// <summary>
    /// Gets a value indicating whether the machine accepted the input.
    /// </summary>
    /// <value>
    ///   <c>true</c> if the machine accepted the input; otherwise, <c>false</c>.
    /// </value>
    virtual bool AcceptedInput()
    {
        return find( FinalStates.begin(), FinalStates.end(), currentState ) != FinalStates.end();
    }

    /// <summary>
    /// Reads all input.
    /// </summary>
    /// <param name="document">The document.</param>
    virtual void ReadAllInput( string document )
    {
        for ( int i = 0; i < document.size(); i++ )
        {
            char input = document[i];
            ReadInput( input );
        }
    }

    /// <summary>
    /// Reads the input.
    /// </summary>
    /// <param name="input">The input.</param>
    virtual void ReadInput( char input )
    {
        for ( int i = 0; i < TransitionRules.size(); i++ )
        {
            if ( TransitionRules[i].InitialState == currentState )
            {
                if ( TransitionRules[i].Input == input )
                {
                    currentState = TransitionRules[i].ResultState;
                    return;
                }
                else if ( TransitionRules[i].Input == ( char )0 )
                {
                    currentState = TransitionRules[i].ResultState;
                    return;
                }
            }
        }

        throw - 1;
    }

    /// <summary>
    /// Returns a <see cref="System.String"/> that represents this instance.
    /// </summary>
    /// <returns>
    /// A <see cref="System.String"/> that represents this instance.
    /// </returns>
    string ToString()
    {
        string format;
        format.append( "States = { " );

        for ( int i = 0; i < TransitionRules.size(); i += 2 )
        {
            stringstream tstate;
            tstate << TransitionRules[i].InitialState;
            format.append( tstate.str() );
            format.append( ", " );
        }

        format.append( " }" );
        format.append( "\n" );

        format.append( "State = " );
        stringstream istate;
        istate << currentState;
        format.append( istate.str() );

        format.append( "\nFinalStates = {" );

        for ( int i = 0; i < FinalStates.size(); i++ )
        {
            format.append( " " );
            stringstream sstate;
            sstate << FinalStates[i];
            format.append( sstate.str() );
            format.append( "," );
        }

        format.append( " }" );
        format.append( "\n" );

        format.append( "[Rules]\n" );

        for ( int i = 0; i < TransitionRules.size(); i++ )
        {
            format.append( TransitionRules[i].ToString() );
            format.append( "\n" );
        }

        return format;
    }
};
#endif