#include "Engine.h"
#include "Title.h"

Engine::Engine() :	running(true),
					deltaTime(SDL_GetTicks()),
					mediaCache()
{
	stateMachine = std::unique_ptr<StateMachine>(new StateMachine(this));
	stateMachine->setCurrentState(std::make_shared<Title>(mediaCache));
}

Engine::~Engine()
{
}

void Engine::run()
{
	handleEvents();

	update();

	render();
}

//handle any events that happen (keyboard, mouse etc) locally first, then pass them down to the currentState
void Engine::handleEvents()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
		{
			running = false;
		}
		//the esc key takes us back to the title screen
		else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
		{
			changeState(std::make_shared<Title>(mediaCache));
		}

		stateMachine->currentState()->handleEvents(e, this);
	}
}

void Engine::update()
{
	stateMachine->currentState()->update((SDL_GetTicks() - deltaTime) / 1000.f, this);
	deltaTime = SDL_GetTicks();
}

//clear the screen, render the currentState then update the screen
void Engine::render()
{
	mediaCache.clearScreen();

	stateMachine->currentState()->render();

	mediaCache.updateScreen();
}

void Engine::changeState(std::shared_ptr<State> newState)
{
	stateMachine->changeState(newState);
}