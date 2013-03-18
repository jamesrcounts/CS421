//-----------------------------------------------------------------------
// <copyright file="Union.h" company="Jim Counts and Michael Nguyen">
//     Copyright (c) Jim Counts and Michael Nguyen 2011. All rights reserved.
// </copyright>
//-----------------------------------------------------------------------
#ifndef _UNION_H
#define _UNION_H

#include "Machine.h"

/// <summary>
/// The union machine is an NFA which executes two <see cref="IFiniteStateMachine"/> instances in parallel and
/// accepts the input if either machine accepts the input.
/// </summary>
class Union : public IFiniteStateMachine
{
private:

    /// <summary>
    /// The m1 machine.
    /// </summary>
    Machine M1;

    /// <summary>
    /// The m2 machine.
    /// </summary>
    Machine M2;

public:
    /// <summary>
    /// Initializes a new instance of the <see cref="Union"/> class.
    /// </summary>
    /// <param name="firstMachine">The first machine.</param>
    /// <param name="secondMachine">The second machine.</param>
    Union( Machine firstMachine, Machine secondMachine )
        : M1( firstMachine ), M2( secondMachine )
    {
    }

    /// <summary>
    /// Performs cleanup on this instance of the <see cref="Union"/> class.
    /// <summary>
    virtual ~Union()
    {
    }

    /// Gets a value indicating whether the machine accepted the input.
    /// </summary>
    /// <value>
    ///   <c>true</c> if the machine accepted the input; otherwise, <c>false</c>.
    /// </value>
    virtual bool AcceptedInput()
    {
        return M1.AcceptedInput() || M2.AcceptedInput();
    }

    /// <summary>
    /// Reads the input.
    /// </summary>
    /// <param name="input">The input.</param>
    virtual void ReadInput( char input )
    {
        M1.ReadInput( input );
        M2.ReadInput( input );
    }

    /// <summary>
    /// Reads all input.
    /// </summary>
    /// <param name="document">The document.</param>
    virtual void ReadAllInput( string document )
    {
        for ( int i = 0; i < ( int )document.size(); i++ )
        {
            char input = document[i];
            ReadInput( input );
        }
    }

    /// <summary>
    /// Returns a <see cref="System.String"/> that represents this instance.
    /// </summary>
    /// <returns>
    /// A <see cref="System.String"/> that represents this instance.
    /// </returns>
    virtual string ToString()
    {
        string sb;
        sb.append( M1.ToString() );
        sb.append( "\n" );
        sb.append( "[Union]\n" );
        sb.append( M2.ToString() );
        sb.append( "\n" );
        return sb;
    }
};
#endif