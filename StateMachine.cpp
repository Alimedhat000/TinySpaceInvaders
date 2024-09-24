#include "StateMachine.h"

StateMachine::StateMachine() : CurState(State::MainMenu) {}

// Getter for current state
int StateMachine::GetCurState() const
{
    return static_cast<int>(CurState); // Return as int for flexibility
}

// Setter for current state
void StateMachine::SetCurState(int newState)
{
    // Ensure the new state is valid
    if (newState >= static_cast<int>(State::MainMenu) && newState <= static_cast<int>(State::Dead))
    {
        CurState = static_cast<State>(newState);
    }
}