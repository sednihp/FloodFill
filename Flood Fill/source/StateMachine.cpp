#include "StateMachine.h"
#include "Engine.h"

StateMachine::StateMachine(Engine* owner) :	mOwner(owner),
											mCurrentState(nullptr)
{
}

StateMachine::~StateMachine()
{
	
}

//if we try to change to the same state, return immediately
//call the exit fxn, assign newState to currentState and call enter fxn
void StateMachine::changeState(std::shared_ptr<State> newState)
{
	if(typeid(*mCurrentState) == typeid(*newState))
	{
		return;
	}

	mCurrentState->exit(mOwner);

	mCurrentState = std::shared_ptr<State>(newState);

	mCurrentState->enter(mOwner);
}