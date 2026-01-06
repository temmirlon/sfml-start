#pragma once

#include<iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
    Class that acts as the game engine.
    Wrapper class.
*/

class Game
{
private:
    // Variables
    // Window
    sf::RenderWindow *window;
    sf::Event ev;
    sf::VideoMode videoMode;

    // Game objects
    sf::RectangleShape enemy;


    // Private Functions
    void initVariable();
    void initWindow();
    void initEnemies();

public:
    // Contructors / Destructors
    Game();
    virtual ~Game();

    //Accessors
    const bool Running() const;

    // Functions
    void PollEvents();
    void Update();
    void Render();

};