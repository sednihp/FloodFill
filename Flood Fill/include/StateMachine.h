#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"
#include <memory>
class Engine;

class StateMachine
{
	private:
		Engine* mOwner;
		std::shared_ptr<State> mCurrentState;

	public:
		StateMachine(Engine* engine);
		virtual ~StateMachine();

		void setCurrentState(std::shared_ptr<State> s) { mCurrentState = std::shared_ptr<State>(s); }

		std::shared_ptr<State> currentState() const { return mCurrentState; }

		void changeState(std::shared_ptr<State> newState);
};

#endif