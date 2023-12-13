#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Energy.h"
#include "Money.h"
#include <vector>
#include "Hazard.h"
#include "Distraction.h"

class Game {
public:
    Game();
    void run();

private:
    enum GameState { MENU, PLAYING, GAME_OVER };
    GameState currentState;
    sf::RenderWindow window;
    Player player;
    std::vector<Platform> platforms;
    Hazard hazard;
    Energy energyDrink = Energy(150.f, -200.f);
    Money money = Money((rand() % (8 - static_cast<int>(20.f))), -200);
    sf::View view;          // View for following the player
    sf::View defaultView;   // Default view for UI elements
    sf::Font font;
    sf::Text energyText;
    sf::Text moneyText;
    sf::Text scoreText;
    sf::Texture texture;

    Distraction distraction;
    bool distractionActive;
    sf::Clock distractionTimer;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void restartGame();
    void spawnDistraction();
    float highestPlatformY;
};

#endif 
