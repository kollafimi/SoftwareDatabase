#ifndef APP_H
#define APP_H

#include "Database.h"
#include "UIManager.h"
#include <SFML/Graphics.hpp>

class App 
{
public:
    App();
    void run();

private:
    sf::RenderWindow window;
    Database database;
    UIManager uiManager;
};

#endif
