#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>
#include "Database.h"

#include <sstream>  
#include <vector>   


class UIManager 
{
public:
    UIManager(sf::RenderWindow& window, Database& db);
    void run();
    void render();
    void updateAgentList();
    void handleInput();
    void handleEvent(sf::Event& event);

private:
    sf::RenderWindow& window;
    Database& database;
    sf::Font font;
    sf::Text title;

    sf::RectangleShape addButton;
    sf::Text addButtonText;

    sf::RectangleShape deleteButton;
    sf::Text deleteButtonText;
    int selectedAgentId;

    sf::RectangleShape editButton;
    sf::Text editButtonText;
    sf::Text inputName, inputContract, inputDate;
    sf::RectangleShape inputBoxName, inputBoxContract, inputBoxDate;
    bool editingMode = false;

    sf::RectangleShape saveButton;
    sf::Text saveButtonText;

    int activeInputField = 0;

    std::vector<std::pair<int, sf::Text>> agentList;
    
    void loadFont();

    void drawButton();
    void drawDeleteButton();
    void drawEditInterface();

    bool isMouseOverButton(sf::Vector2f mousePos, sf::RectangleShape& button);

    void addAgent();
    void deleteAgent();
    void editAgent();
    
    void fillInputFields();
    void handleTextInput(sf::Event& event);
};

#endif
