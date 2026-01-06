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

    this->window->setFramerateLimit(100);

}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(.5f, .5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

// Constructors / Destructors
Game::Game()
{
    this->initVariable();
    this->initWindow();
    this->initEnemies();
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

    // update mouse position
    // Relative to the screen
    // std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";

    // Relative to the window
    std::cout << "Mouse pos: " 
    << sf::Mouse::getPosition(*this->window).x << " " 
    << sf::Mouse::getPosition(*this->window).y << "\n";

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

    this->window->clear();

    // Draw game objects

    this->window->draw(this->enemy);

    this->window->display();

}


