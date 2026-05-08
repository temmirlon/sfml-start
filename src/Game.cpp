#include "Game.h"

// Private Functions
void Game::initVariable()
{
    this->window = nullptr;
    
    // Game Logic
    this->endGame = false;
    this->points = 0;
    this->health = 20;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
    
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Game One", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);

}

void Game::initFonts()
{
    if (this->font.loadFromFile("Fonts/MinecraftiaRegular.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";  
    }
    
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(18);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setPosition(0.f, 30.f);
    this->uiText.setString("NONE");
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    // this->enemy.setOutlineColor(sf::Color::Green);
    // this->enemy.setOutlineThickness(1.f);

}

// Constructors / Destructors
Game::Game()
{
    this->initVariable();
    this->initWindow();
    this->initText();
    this->initFonts();
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

const bool Game::getEndGame() const
{
    return this->endGame;
}

// Functions

void Game::spawnEnemy()
{
    /*
        @return void



        Spawns enemies and sets their types and colors. Spawns them at random positions.
        - Sets a random type (diff).
        - Sets a random position.
        - Sets a random color.
        - Adds enemy to the vector.
    */

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    // Randomize enemy type 
    int type = rand() % 5; // from 0 to 4

    switch (type)
    {
    case 0:
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;

    case 1:
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;

    case 2:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;

    case 3:
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        this->enemy.setFillColor(sf::Color::Red);
        break;

    case 4:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Green);
        break;
    default:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Yellow);
        break;
    }

    // Spawn enemy
    this->enemies.push_back(this->enemy);
    
    // TODO
    // Remove Enemies at end of screen
    
}

void Game::pollEvents()
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

void Game::updateMousePositions()
{
    /*
    @ return void

    Updates the mouse positions:
        - Mouse posistion relative to window (Vector2i)
    */

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    std::stringstream ss;
    
    ss << "Points: " << this->points << "\n"
        << "Health: " << this->health << "\n";

    this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{   
    /** 
        @return void

        Updates the enemies spawn time and spawns enemies
        when the total amount of enemies is small than the maximum.
        Moves the enemies downwards. 
        Removes the enemies at the edge of the screen. //TODO

    */


    // Updating the timer for enemy spawning 
    if (this->enemies.size() < this->maxEnemies)
    {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }
    
    // Moving and updating enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;
        
        this->enemies[i].move(0.f, 5.f);

        // if the enemy is past the bottom of the screen
        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health: " << this->health << "\n";
        }
    }

    // Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    
                    // Gain points
                    if(this->enemies[i].getFillColor() == sf::Color::Magenta){
                        this->points += 10.f;    
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue){
                        this->points += 7.f;    
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan){
                        this->points += 5.f;    
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Red){
                        this->points += 3.f;    
                    }
                    else if (this->enemies[i].getFillColor() == sf::Color::Green){
                        this->points += 1.f;    
                    }

                    std::cout << "Points: " << this->points << "\n";

                    // delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
        else
        {
            this->mouseHeld = false;
        }
    }
}

void Game::update()
{
    this->pollEvents();
    
    if (this->endGame == false)
    {
        this->updateMousePositions();

        this->updateText();

        this->updateEnemies();
    }

    // Endgame condition
    if (this->health <= 0)
        this->endGame = true;
    
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    // Rendering all the enemies
    for (auto &e: this->enemies)
    {
        target.draw(e);
    }
}

void Game::render()
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

    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();

}


