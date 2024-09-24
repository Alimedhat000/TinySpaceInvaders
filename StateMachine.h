#pragma once
#include "Global.h"

class StateMachine
{
public:
    // Constructor
    StateMachine();

    // Get the current state
    int GetCurState() const;

    // Set the current state
    void SetCurState(int newState);

private:
    // Enum class for better type safety
    enum class State {
        MainMenu,
        Playing,
        Dead
    };

    // Holds the current state
    State CurState;
};
