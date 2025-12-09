#include <SFML/Graphics.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Game One", sf::Style::Titlebar | sf::Style::Close);    
    sf::Event ev;

    // Game loop

    while (window.isOpen())
    {
        // Event polling
        while (window.pollEvent(ev)) // whenever we are getting events from window we gonna save them into 'ev' variable
        {
            switch (ev.type) // each event has type (klick, press etc.)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (ev.key.code == sf::Keyboard::Escape)
                        window.close();
                        break;
            }
        }
        
        // Update (frame)

        // Render

        window.clear(sf::Color::Blue); // clear old frame
        // ----------------------------------------
        // Draw your game





        // ----------------------------------------
        window.display(); // Tell up that window is done drawing

    }
    
    // End of application

    return 0;
}