//-----------------------------------------------------------------------
// <copyright file="StateMachineFactory.h" company="Jim Counts and Michael Nguyen">
//     Copyright (c) Jim Counts and Michael Nguyen 2011. All rights reserved.
// </copyright>
//-----------------------------------------------------------------------
#ifndef _STATEMACHINEFACTORY_H
#define _STATEMACHINEFACTORY_H

#include "TransitionRule.h"
#include "Machine.h"
#include <string>
#include <vector>

using namespace std;

/// <summary>
/// Generates deterministic finite automata which accept any document containing a single string.
/// </summary>
class StateMachineFactory
{
public:
    /// <summary>
    /// Creates a machine.
    /// </summary>
    /// <param name="value">The accepted value.</param>
    /// <returns>A DFA which accepts <paramref name="value"/></returns>
    static Machine CreateMachine( string value )
    {
        vector<TransitionRule> rules = GenerateRules( value );
        vector<int> finalStates;
        finalStates.push_back( value.size() - 1 );
        return Machine( 0, rules, finalStates );
    }

    /// <summary>
    /// Generates the rules.
    /// </summary>
    /// <param name="inputs">The inputs.</param>
    /// <returns>The collection of transition rules, which taken together form the transition function.</returns>
    static vector<TransitionRule> GenerateRules( string inputs )
    {
        vector<TransitionRule> rules;

        for ( int i = 0; i < ( int )inputs.size(); i++ )
        {
            TransitionRule acceptRule;
            acceptRule.InitialState = i;
            acceptRule.Input = inputs[i];
            acceptRule.ResultState = i + 1 == ( int )inputs.size() ? i : i + 1;
            rules.push_back( acceptRule );

            if ( i + 1 != ( int )inputs.size() )
            {
                // Implement default rule - return to state 0.
                TransitionRule rejectRule;
                rejectRule.InitialState = i;
                rejectRule.Input = ( char )0;
                rejectRule.ResultState = 0;
                rules.push_back( rejectRule );
            }
            else
            {
                // Implement trap state - stay in i
                TransitionRule trapRule;
                trapRule.InitialState = i;
                trapRule.Input = ( char )0;
                trapRule.ResultState = i;
                rules.push_back( trapRule );
            }
        }

        return rules;
    }
};
#endif