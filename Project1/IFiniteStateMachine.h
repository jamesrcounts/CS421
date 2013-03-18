//-----------------------------------------------------------------------
// <copyright file="IFiniteStateMachine.h" company="Jim Counts and Michael Nguyen">
//     Copyright (c) Jim Counts and Michael Nguyen 2011. All rights reserved.
// </copyright>
//-----------------------------------------------------------------------
#ifndef _IFINITESTATEMACHINE_H
#define _IFINITESTATEMACHINE_H

#include <string>

using namespace std;

/// <summary>
/// Describes a finite state machine.
/// </summary>
class IFiniteStateMachine
{
public:
    virtual ~IFiniteStateMachine() {};

    /// <summary>
    /// Gets a value indicating whether the machine accepted the input.
    /// </summary>
    /// <value>
    ///   <c>true</c> if the machine accepted the input; otherwise, <c>false</c>.
    /// </value>
    virtual bool AcceptedInput() = 0;

    /// <summary>
    /// Reads the input.
    /// </summary>
    /// <param name="input">The input.</param>
    virtual void ReadInput( char input ) = 0;

    /// <summary>
    /// Reads all input.
    /// </summary>
    /// <param name="document">The document.</param>
    virtual void ReadAllInput( string document ) = 0;
};
#endif