#include "Game.h"
#include <iostream>

// Constants for platform generation
const float maxJumpHeight = 200.0f; 
const float platformWidth = 100.0f;
const float platformHeight = 20.0f;
float topMostPos = 0;

Game::Game() : window(sf::VideoMode(600, 800), "Burnout Paradise"), currentState(MENU), highestPlatformY(800.f - 50.f), hazard(600.f), distraction(0.f, 0.f), distractionActive(false) {
    if (!font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf")) {
    }
    // Set properties for enrgy, money, and so on...

    energyText.setFont(font);
    energyText.setCharacterSize(24);
    energyText.setFillColor(sf::Color::White);
    energyText.setPosition(10, 10);
    moneyText.setFont(font);
    moneyText.setCharacterSize(24);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(10, 30);
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 50);

    // Configure the view to follow the player
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    window.setView(view);

    // Initialize energy drink and money objects
    energyDrink = Energy((rand() % 580), (rand() % 100 - 200));
    money = Money((rand() % 580), (rand() % 100 - 200));
    // Starting platform <- this stays the same every time the game is launched
    float lastPlatformY = 350.f; // Starting Y position for the first platform

    platforms.push_back(Platform(300.f - platformWidth / 2, lastPlatformY, platformWidth, platformHeight, sf::Color::Red));

    // Generate additional platforms
    for (int i = 0; i < 5; ++i) {
        float x = static_cast<float>(rand() % static_cast<int>(600 - platformWidth));
        float yGap = static_cast<float>((rand() % static_cast<int>(maxJumpHeight / 2)) + maxJumpHeight / 2); // logic ensuring the platforms are reachable for the player
        float y = lastPlatformY - yGap; // Ensure platforms don't go off-screen
        platforms.push_back(Platform(x, y, platformWidth, platformHeight, sf::Color::Red));
        lastPlatformY = y;
    }
}


void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed:
            if (currentState == MENU && event.key.code == sf::Keyboard::Enter) {
                currentState = PLAYING;
            } else if (currentState == GAME_OVER && event.key.code == sf::Keyboard::Enter) {
                restartGame();
            }
            else {
                handlePlayerInput(event.key.code, true);
            }
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            window.close();
            break;
        }
    }
}

void Game::restartGame() {
    // Reset game state and player position
    currentState = PLAYING;
    player.reset();
    hazard.reset();
    platforms.clear();
    float lastPlatformY = 350.f; // Starting Y position for the first platform

    platforms.push_back(Platform(300.f - platformWidth / 2, lastPlatformY, platformWidth, platformHeight, sf::Color::Red));

    // Generate additional platforms
    for (int i = 0; i < 5; ++i) {
        float x = static_cast<float>(rand() % 600 - platformWidth); //static cast means that the expression is set to float.
        float yGap = static_cast<float>((rand() % static_cast<int>(maxJumpHeight / 2)) + maxJumpHeight / 2);
        float y = lastPlatformY - yGap; // Ensure platforms don't go off-screen
        platforms.push_back(Platform(x, y, platformWidth, platformHeight, sf::Color::Red));
        lastPlatformY = y;
    }
    topMostPos = 0.f;
    highestPlatformY = 350.f;
}

void Game::spawnDistraction() {
    if (!platforms.empty() && !distractionActive) {
        int platformIndex = rand() % platforms.size();
        auto platformPos = platforms[platformIndex].getShape().getPosition(); 
        distraction.setPosition(platformPos.x + platforms[platformIndex].getShape().getSize().x / 2 - distraction.getSprite().getGlobalBounds().width / 2, platformPos.y - distraction.getSprite().getGlobalBounds().height);
        distractionActive = true;
    }
}

// update game state
void Game::update(sf::Time deltaTime) {
    if (currentState == PLAYING) {
        player.handleInput();
        player.update(deltaTime);

        // Update the view to follow the player
        view.setCenter(window.getSize().x / 2, player.getSprite().getPosition().y);
        window.setView(view);

        hazard.update(deltaTime);
 
        if (hazard.getShape().getPosition().y - player.getSprite().getPosition().y > 1000) {
            hazard.chaseCorrect(player.getSprite().getPosition().y);
        }

        // Spawn distraction if not already active
        if (!distractionActive) {
            spawnDistraction();
        }

        // Collision detection with distraction
        if (distractionActive && player.getSprite().getGlobalBounds().intersects(distraction.getSprite().getGlobalBounds())) {
            player.consumeEnergy(player.getEnergy() / 2);
            player.consumeMoney(player.getMoney() / 2);
            distractionActive = false;
        }

        // Check if player has moved past the distraction
        if (distractionActive && player.getSprite().getPosition().y + 700< distraction.getSprite().getPosition().y) {
            distractionActive = false; // Deactivate or move the distraction off-screen
        }

        // Determine the top of the current view
        float viewTop = view.getCenter().y - view.getSize().y / 2;

        // Generate new platforms above the view
        if (highestPlatformY > viewTop) {
            float x = static_cast<float>(rand() % (600 - 100));
            float verticalGap = 80.0f; // Adjust this value as needed
            float y = highestPlatformY - verticalGap;
            platforms.push_back(Platform(x, y, platformWidth, platformHeight, sf::Color::Red));
            highestPlatformY = y;
        }

        bool isPlayerOnPlatform = false;

        // Collision detection
        for (auto& platform : platforms) {
            if (player.getSprite().getGlobalBounds().intersects(platform.getShape().getGlobalBounds())) {
                float playerBottom = player.getSprite().getPosition().y + player.getSprite().getGlobalBounds().height;
                float platformTop = platform.getTopPosition();

                // Check if the player is falling and the bottom of the player is just above the platform
                if (player.isFalling() && playerBottom < platformTop + 5) {
                    player.land(platformTop);
                    isPlayerOnPlatform = true;
                    break; // Exit the loop once a landing platform is found
                }
            }
        }

        //Check for energy drink collision
        if (player.getSprite().getGlobalBounds().intersects(energyDrink.getSprite().getGlobalBounds())) {
            player.addEnergy(40.f);
            energyDrink.move(rand() % 100 - 550);
            player.consumeMoney(5);
        }

        if (energyDrink.getTopPosition() > view.getCenter().y + window.getSize().y / 2) {
            energyDrink.move(rand() % 100 - 920);
        } else if(energyDrink.getTopPosition() < view.getCenter().y - window.getSize().y / 2 - 1000) {
            energyDrink.setPos(rand() % 580, view.getCenter().y - window.getSize().y / 2 - 100);
        }

        //Check for money collision
        if (player.getSprite().getGlobalBounds().intersects(money.getSprite().getGlobalBounds())) {
            player.addMoney(rand() % 60 + 10);

            money.move(rand() % 100 - 550);
        }

        if (money.getTopPosition() > view.getCenter().y + window.getSize().y / 2) {
            money.move(rand() % 100 - 920);
        } else if (money.getTopPosition() < view.getCenter().y - window.getSize().y / 2 - 1000) {
            money.setPos(rand() % 580, view.getCenter().y - window.getSize().y / 2 - 100);
        }

        //Hazard collision
        if (player.getSprite().getGlobalBounds().intersects(hazard.getShape().getGlobalBounds())) {
            currentState = GAME_OVER;
        }

        // If the player is not on any platform and not already jumping, they should start falling
        if (!isPlayerOnPlatform && !player.isJumping) {
            player.startFalling();
        }

        if (player.getSprite().getPosition().y < highestPlatformY - 100) {
            // Generates a random x-coordinate 
            float x = static_cast<float>(rand() % (800 - 100));
            //generates new highest platf
            float y = highestPlatformY - (100 + rand() % 150);

            //adds vector
            platforms.push_back(Platform(x, y, platformWidth, platformHeight, sf::Color::Red));
            highestPlatformY = y;
        }

        // Remove platforms no longer visible
        platforms.erase(std::remove_if(platforms.begin(), platforms.end(),
            [this](const Platform& platform) {
                return platform.getTopPosition() > view.getCenter().y + window.getSize().y / 2 + 200;
            }), platforms.end());

        //updates the highest position
        if (player.getSprite().getPosition().y < topMostPos) {
            topMostPos = player.getSprite().getPosition().y;
        }

        if (player.getMoney() < -500) {
            currentState = GAME_OVER;
        }

        if (player.getSprite().getPosition().y > topMostPos + 1000) {
            currentState = GAME_OVER;
        }

    }
}

void Game::render() {
    window.clear();

    if (currentState == MENU) {
        // Render the menu
        sf::Text menuText("Press Enter to Start", font, 30);
        menuText.setFillColor(sf::Color::White);
        menuText.setPosition(200, 400);
        window.draw(menuText);
    }
    else if (currentState == PLAYING) {
        // Set the game view for rendering game world elements
        window.setView(view);
        window.draw(player);
        for (const auto& platform : platforms) {
            window.draw(platform);
        }
        window.draw(energyDrink);
        window.draw(money);
        window.draw(hazard);

        if (distractionActive) {
            window.draw(distraction);
        }

        // Set the default view for rendering UI elements
        window.setView(window.getDefaultView());
        energyText.setString("Energy: " + std::to_string(static_cast<int>(player.getEnergy())));
        moneyText.setString("Money: " + std::to_string(static_cast<int>(player.getMoney())));
        scoreText.setString("Score: " + std::to_string(static_cast<int>(player.getScore())));
        window.draw(energyText);
        window.draw(moneyText);
        window.draw(scoreText);
    } else if (currentState == GAME_OVER) {
        // Render the game over screen
        window.setView(window.getDefaultView());
        sf::Text gameOverText("Score: " + std::to_string(static_cast<int>(player.getScore())) + "\nGame Over\nPress Enter to Restart", font, 30);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getLocalBounds().width / 2,
            window.getSize().y / 2 - gameOverText.getLocalBounds().height / 2);
        window.draw(gameOverText);
    }

    window.display();
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
}
