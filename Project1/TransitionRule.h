//-----------------------------------------------------------------------
// <copyright file="TransitionRule.h" company="Jim Counts and Michael Nguyen">
//     Copyright (c) Jim Counts and Michael Nguyen 2011. All rights reserved.
// </copyright>
//-----------------------------------------------------------------------
#ifndef _TRANSITIONRULE_H
#define _TRANSITIONRULE_H

#include <string>
#include <sstream>

/// <summary>
/// Describes one part of a transition function.
/// </summary>
struct TransitionRule
{
    /// <summary>
    /// Gets or sets the input.
    /// </summary>
    /// <value>
    /// The input.
    /// </value>
    char Input;

    /// <summary>
    /// Gets or sets the machine result state.
    /// </summary>
    /// <value>
    /// The machine result state.
    /// </value>
    int ResultState;

    /// <summary>
    /// Gets or sets the machine initial state.
    /// </summary>
    /// <value>
    /// The machine initial state.
    /// </value>
    int InitialState;

    /// <summary>
    /// Implements the operator ==.
    /// </summary>
    /// <param name="left">The left.</param>
    /// <param name="right">The right.</param>
    /// <returns>
    /// The result of the operator.
    /// </returns>
    bool operator ==( TransitionRule right )
    {
        return Equals( right );
    }

    /// <summary>
    /// Implements the operator !=.
    /// </summary>
    /// <param name="left">The left.</param>
    /// <param name="right">The right.</param>
    /// <returns>
    /// The result of the operator.
    /// </returns>
    bool operator !=( TransitionRule right )
    {
        return !Equals( right );
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

        format.append( "InitialState = " );
        stringstream istate;
        istate << InitialState;
        format.append( istate.str() );

        format.append( "; Input = '" );

        if ( Input == ( char )0 )
        {
            format.append( "Any" );
        }
        else
        {
            format.push_back( Input );
        }

        format.append( "'; ResultState = " );
        stringstream ostate;
        ostate << ResultState;
        format.append( ostate.str() );
        format.append( ";" );
        return format;
    }

    /// <summary>
    /// Returns <c>true</c> if this instance represents the same data as <paramref name="other"/>
    /// </summary>
    /// <param name="other">The other <see cref="TransitionRule"/>.</param>
    /// <returns><c>true</c> if this instance represents the same data as <paramref name="other"/>; otherwise <c>false</c>.</returns>
    bool Equals( TransitionRule other )
    {
        return Input == other.Input &&
               ResultState == other.ResultState &&
               InitialState == other.InitialState;
    }

    /// <summary>
    /// Returns a hash code for this instance.
    /// </summary>
    /// <returns>
    /// A hash code for this instance, suitable for use in hashing algorithms and data structures like a hash table.
    /// </returns>
    int GetHashCode()
    {
        int hash = 13;
        hash = ( hash * 7 ) + InitialState;
        hash = ( hash * 7 ) + ( int )Input;
        hash = ( hash * 7 ) + ResultState;
        return hash;
    }
};
#endif