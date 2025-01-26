#include "App.h"

App::App() : window(sf::VideoMode(1600, 1300), "Database"), database("database.db"), uiManager(window, database) 
{
    //database.connect();
}

void App::run() 
{
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            uiManager.handleEvent(event);
        }
        uiManager.render();
    }
}
