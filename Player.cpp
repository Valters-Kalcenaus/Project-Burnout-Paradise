#include "Player.h"
#include <iostream>

sf::Texture Player::texture;


// sets the initial values every time the game starts.
Player::Player() : isJumping(false), jumpVelocity(-900.f), energy(100.f), money(100.f), score(0.f), jumpCount(0), isSleeping(false), callingParents(false) {
    if (!texture.loadFromFile("Player.png")) {
        std::cout << "Failed to load Player.png" << std::endl;
    }

    sprite.setTexture(texture);

    float desiredWidth = 36.0f;
    float desiredHeight = 60.0f;

    sf::Vector2u textureSize = texture.getSize();
    float originalWidth = static_cast<float>(textureSize.x);
    float originalHeight = static_cast<float>(textureSize.y);

    float scaleX = desiredWidth / originalWidth;
    float scaleY = desiredHeight / originalHeight;

    sprite.setScale(scaleX, scaleY);

    sprite.setPosition(300.f - sprite.getGlobalBounds().width / 2, 600.f - 300.f - sprite.getGlobalBounds().height);
}

void Player::consumeEnergy(float amount) {
    energy -= amount;
    if (energy < 0) energy = 0;
}

void Player::addEnergy(float amount) {
    energy += amount;
    if (energy > 100) energy = 100;
}

float Player::getEnergy() const {
    return energy;
}

void Player::consumeMoney(float amount) {
    money -= amount;
}

void Player::addMoney(float amount) {
    money += amount;
}

float Player::getMoney() const {
    return money;
}

void Player::addScore(float amount) {
    score += amount;
    if (jumpCount % 30 == 0) {
        money -= 200;
    }
}

float Player::getScore() const {
    return score;
}

void Player::update(sf::Time deltaTime) {
    if (isSleeping) {
        sleep(deltaTime);
    }
    if (callingParents) {
        call(deltaTime);
    }
    if (isSleeping || callingParents) {
        deadBeat(deltaTime);
    }

    // Apply gravity and movement regardless of sleeping state
    if (isJumping) {
        velocity.y += 1500.f * deltaTime.asSeconds(); // Gravity effect
    }

    sprite.move(velocity * deltaTime.asSeconds());
}

void Player::reset() {
    sprite.setPosition(300.f - sprite.getGlobalBounds().width / 2, 600.f - 300.f - sprite.getGlobalBounds().height);
    isJumping = false;
    energy = 100.f; 
    money = 100.f;
    score = 0.f;
}

void Player::sleep(sf::Time deltaTime) {
    if (sleepTimer.getElapsedTime().asSeconds() >= 1.0f) {
        addEnergy(10.0f);
        sleepTimer.restart();
    }
    //shape.setFillColor(sf::Color::Blue);
}

void Player::call(sf::Time deltaTime) {
    if (callTimer.getElapsedTime().asSeconds() >= 1.0f) {
        addMoney(5.0f);
        callTimer.restart();
    }
    //shape.setFillColor(sf::Color::Red);
}

void Player::deadBeat(sf::Time deltaTime) {
    if (callTimer.getElapsedTime().asSeconds() >= 2.0f) {
        addScore(-1);
        callTimer.restart();
    }
}

void Player::wakeUp() {
    isSleeping = false;
    //shape.setFillColor(sf::Color::Green); // Change color back to green
    sleepTimer.restart();
}

void Player::stopCalling() {
    callingParents = false;
    // shape.setFillColor(sf::Color::Green); // Change color back to green
    sleepTimer.restart();
}

void Player::jump(float v) {
    if (!isJumping && energy > 0) {
        jumpCount++;
        addScore(1.f);
        isJumping = true;
        velocity.y = v; // Set the upward velocity
        consumeEnergy(10.0f); // Consume energy on jump
    }
}

void Player::setVelocityX(float vx) {
    if (!isSleeping) {
        velocity.x = vx;
    }
}

// controls for player movement
void Player::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        isSleeping = true;
    }
    else if (isSleeping) {
        wakeUp();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        callingParents = true;
    }
    else if (callingParents) {
        stopCalling();
    }

    if (!isSleeping && !callingParents) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            jump(-800.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (sprite.getPosition().x > 0) {
                setVelocityX(-200.f); 
            } else {
                setVelocityX(0.f);
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (sprite.getPosition().x < 600 - sprite.getGlobalBounds().height) {
                setVelocityX(200.f); 
            } else {
                setVelocityX(0.f);
            }
        }
        else {
            setVelocityX(0.f); // Stop horizontal movement
        }
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool Player::isFalling() const {
    return velocity.y > 0;
}
// player is standing on surface
void Player::land(float y) {
    isJumping = false;
    velocity.y = 0;
    if (isSleeping) {
        velocity.x = 0; // Stop horizontal movement if sleeping
    }
    sprite.setPosition(sprite.getPosition().x, y - sprite.getGlobalBounds().height);
}


const sf::Sprite& Player::getSprite() const {
    return sprite;
}

void Player::startFalling() {
    if (!isJumping) {
        isJumping = true;
        velocity.y = 0;
    }
}
