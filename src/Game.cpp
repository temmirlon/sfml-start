#include "Game.h"

// Private Functions
void Game::initVariable()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;


    this->window = new sf::RenderWindow(this->videoMode, "Game One", sf::Style::Titlebar | sf::Style::Close);
}

// Constructors / Destructors
Game::Game()
{
    this->initVariable();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

// Accessors
const bool Game::Running() const
{
    return this->window->isOpen();
}

// Functions

void Game::PollEvents()
{
    // Event polling
    while (this->window->pollEvent(this->ev)) // whenever we are getting events from window we gonna save them into 'ev' variable
    {
        switch (this->ev.type) // each event has type (klick, press etc.)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                    break;
        }
    }
}

void Game::Update()
{
   this->PollEvents();
}

void Game::Render()
{

    /*
        @return void
        
        - clear all  frame
        - render objects
        - display frame in window

        Renders the game objects.
    */

    this->window->clear(sf::Color(255, 0, 0, 255));

    // Draw game objects

    this->window->display();

}


