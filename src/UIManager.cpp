#include "UIManager.h"
#include <iostream>
#include <codecvt>

UIManager::UIManager(sf::RenderWindow& win, Database& db) : window(win), database(db) 
{
    loadFont();
    title.setFont(font);
    title.setString("List of agents");
    title.setCharacterSize(30);
    title.setPosition(50, 50);

    addButton.setSize(sf::Vector2f(200, 50));
    addButton.setPosition(300, 50);
    addButton.setFillColor(sf::Color::Green);
    addButtonText.setFont(font);
    addButtonText.setString("add agent");
    addButtonText.setCharacterSize(24);
    addButtonText.setPosition(315, 60);

    deleteButton.setSize(sf::Vector2f(200, 50));
    deleteButton.setPosition(500, 50);
    deleteButton.setFillColor(sf::Color::Red);
    deleteButtonText.setFont(font);
    deleteButtonText.setString("delete agent");
    deleteButtonText.setCharacterSize(24);
    deleteButtonText.setPosition(515, 60);

    saveButton.setSize(sf::Vector2f(200, 50));
    saveButton.setPosition(900, 50);
    saveButton.setFillColor(sf::Color::White);
    saveButtonText.setFont(font);
    saveButtonText.setString("save");
    saveButtonText.setCharacterSize(24);
    saveButtonText.setFillColor(sf::Color::Black);
    saveButtonText.setPosition(915, 60);

    editButton.setSize(sf::Vector2f(200, 50));
    editButton.setPosition(700, 50);
    editButton.setFillColor(sf::Color::White);
    editButtonText.setFont(font);
    editButtonText.setString("edit");
    editButtonText.setCharacterSize(24);
    editButtonText.setFillColor(sf::Color::Black);
    editButtonText.setPosition(715, 60);

    inputBoxName.setSize(sf::Vector2f(300, 40));
    inputBoxName.setPosition(50, 550);
    inputBoxName.setFillColor(sf::Color::White);
    inputName.setFont(font);
    inputName.setString("Enter name");
    inputName.setCharacterSize(24);
    inputName.setFillColor(sf::Color::Black);
    inputName.setPosition(55, 555);

    inputBoxContract.setSize(sf::Vector2f(300, 40));
    inputBoxContract.setPosition(50, 600);
    inputBoxContract.setFillColor(sf::Color::White);
    inputContract.setFont(font);
    inputContract.setString("Enter number");
    inputContract.setCharacterSize(24);
    inputContract.setFillColor(sf::Color::Black);
    inputContract.setPosition(55, 605);

    inputBoxDate.setSize(sf::Vector2f(300, 40));
    inputBoxDate.setPosition(50, 650);
    inputBoxDate.setFillColor(sf::Color::White);
    inputDate.setFont(font);
    inputDate.setString("Enter date");
    inputDate.setCharacterSize(24);
    inputDate.setFillColor(sf::Color::Black);
    inputDate.setPosition(55, 655);

    updateAgentList();
}

void UIManager::loadFont() 
{
    if (!font.loadFromFile("D:/C++/проектБД/assets/arial.ttf")) 
    {
        std::cerr << "error (font)" << std::endl;
    }
}

void UIManager::updateAgentList() 
{
    agentList.clear();
    auto agents = database.fetchAgents();
    float yOffset = 100;
    for (const auto& agent : agents) 
    {
        sf::Text agentText;
        agentText.setFont(font);
        
        //agentText.setString("ID: " + agent.id + " | " + agent.name + " | " + agent.contract_number + " | " + agent.date);
        
        agentText.setString(
            L"ID: " + std::to_wstring(agent.id) + L" | " +
            sf::String::fromUtf8(agent.name.begin(), agent.name.end()) + L" | " +
            sf::String::fromUtf8(agent.contract_number.begin(), agent.contract_number.end()) + L" | " +
            sf::String::fromUtf8(agent.date.begin(), agent.date.end())
        );

        agentText.setCharacterSize(20);
        agentText.setPosition(50, yOffset);
        yOffset += 40;
        agentList.push_back({agent.id, agentText});
    }
}

void UIManager::drawButton()
{
    window.draw(addButton);
    window.draw(addButtonText);
}

void UIManager::drawDeleteButton()
{
    window.draw(deleteButton);
    window.draw(deleteButtonText);
}

void UIManager::drawEditInterface() 
{
    if (editingMode) 
    {
        window.draw(inputBoxName);
        window.draw(inputBoxContract);
        window.draw(inputBoxDate);
        window.draw(inputName);
        window.draw(inputContract);
        window.draw(inputDate);
    }
}

bool UIManager::isMouseOverButton(sf::Vector2f mousePos, sf::RectangleShape& button)
{
    return button.getGlobalBounds().contains(mousePos);
}

void UIManager::addAgent()
{
    database.execute("insert into agents (name, contract_number, date) values ('new agent', '00000', '2025-01-01');");
    updateAgentList();
    std::cout << "added agent!" << std::endl;
}

void UIManager::deleteAgent()
{
    if (selectedAgentId != -1)
    {
        //std::string query = "delete from agents where id = " + std::to_string(selectedAgentId) + ";";
        if (database.deleteAgentById(selectedAgentId))
        {
            std::cout << "agent ID " << selectedAgentId << " deleted!" << std::endl;
            selectedAgentId = -1;
            updateAgentList();
        }
        else
        {
            std::cerr << "Error delete" << std::endl;
        }
    }
    else
    {
        std::cerr << "agent not found" << std::endl;
    }
}

void UIManager::editAgent() 
{
    if (selectedAgentId != -1) 
    {
        std::string name = inputName.getString().toAnsiString();
        std::string contract = inputContract.getString().toAnsiString();
        std::string date = inputDate.getString().toAnsiString();

        if (database.updateAgent(selectedAgentId, name, contract, date)) 
        {
            std::cout << "agent ID " << selectedAgentId << " updated!" << std::endl;
            editingMode = false;
            updateAgentList();
        }
        else 
        {
            std::cerr << "Error update" << std::endl;
        }
    }
    else 
    {
        std::cerr << "agent not found" << std::endl;
    }
}

void UIManager::handleEvent(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

        for (const auto& agent : agentList)
        {
            if (agent.second.getGlobalBounds().contains(mousePos))
            {
                selectedAgentId = agent.first;
                std::cout << "agent ID: " << selectedAgentId << std::endl;
                break;
            }
        }

        if (isMouseOverButton(mousePos, addButton))
        {
            addAgent();
        }
        
        if (isMouseOverButton(mousePos, deleteButton))
        {
            deleteAgent();
        }

        if (isMouseOverButton(mousePos, editButton))
        {
            if (selectedAgentId != -1)
            {
                editingMode = true;
                fillInputFields();
            }
            else
            {
                std::cerr << "Error update" << std::endl;
            }
        }

        if (isMouseOverButton(mousePos, saveButton))
        {
            editAgent();
        }

        if (inputBoxName.getGlobalBounds().contains(mousePos))
            activeInputField = 0;
        else if (inputBoxContract.getGlobalBounds().contains(mousePos))
            activeInputField = 1;
        else if (inputBoxDate.getGlobalBounds().contains(mousePos))
            activeInputField = 2;
        
    }
    else if (event.type == sf::Event::TextEntered && editingMode)
    {
        handleTextInput(event);
    }
}

void UIManager::fillInputFields()
{
    for (const auto& agent : agentList) 
    {
        if (agent.first == selectedAgentId) 
        {
            // Разбиваем строку на поля (допустим, что данные разделены "|")
            std::vector<std::string> fields;
            std::string agentInfo = agent.second.getString();
            std::stringstream ss(agentInfo);
            std::string field;
            while (std::getline(ss, field, '|')) 
            {
                fields.push_back(field);
            }

            // Проверка корректности данных и заполнение полей ввода
            if (fields.size() >= 4) 
            {
                inputName.setString(fields[1]);   // Имя
                inputContract.setString(fields[2]); // Номер контракта
                inputDate.setString(fields[3]);     // Дата
            }
            else 
            {
                std::cerr << "error. not correct" << std::endl;
            }
            break;
        }
    }
}

void UIManager::handleTextInput(sf::Event& event) {
    if (event.text.unicode == 8) {  // Обработка Backspace
        if (activeInputField == 0 && !inputName.getString().isEmpty()) {
            inputName.setString(inputName.getString().substring(0, inputName.getString().getSize() - 1));
        }
        else if (activeInputField == 1 && !inputContract.getString().isEmpty()) {
            inputContract.setString(inputContract.getString().substring(0, inputContract.getString().getSize() - 1));
        }
        else if (activeInputField == 2 && !inputDate.getString().isEmpty()) {
            inputDate.setString(inputDate.getString().substring(0, inputDate.getString().getSize() - 1));
        }
    }
    else if (event.text.unicode < 128) {
        if (activeInputField == 0) {
            inputName.setString(inputName.getString() + static_cast<char>(event.text.unicode));
        }
        else if (activeInputField == 1) {
            inputContract.setString(inputContract.getString() + static_cast<char>(event.text.unicode));
        }
        else if (activeInputField == 2) {
            inputDate.setString(inputDate.getString() + static_cast<char>(event.text.unicode));
        }
    }
}


void UIManager::render() 
{
    window.clear();
    window.draw(title);
    for (auto& agent : agentList) 
    {
        window.draw(agent.second);
    }
    drawButton();
    drawDeleteButton();
    window.draw(editButton);
    window.draw(editButtonText);
    if (editingMode)
    {
        drawEditInterface();
        window.draw(saveButton);
        window.draw(saveButtonText);
    }
    
    window.display();
}
