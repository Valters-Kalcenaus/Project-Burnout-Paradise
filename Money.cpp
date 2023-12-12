#include "Money.h"
#include <iostream>

sf::Texture Money::texture;

Money::Money(float x, float y) {
    if (texture.getSize().x == 0) { // Load texture only once
        if (!texture.loadFromFile("Cash.png")) {
            std::cerr << "Failed to load Cash.png" << std::endl;
        }
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    float desiredWidth = 40.0f;
    float desiredHeight = 40.0f;

    sf::Vector2u textureSize = texture.getSize();
    float originalWidth = static_cast<float>(textureSize.x);
    float originalHeight = static_cast<float>(textureSize.y);

    float scaleX = desiredWidth / originalWidth;
    float scaleY = desiredHeight / originalHeight;

    sprite.setScale(scaleX, scaleY);
}

void Money::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

float Money::getTopPosition() const {
    return sprite.getPosition().y;
}

void Money::move(float y) {
    int nextPos = static_cast<int>(std::rand() % 580);
    float xChange = nextPos - sprite.getPosition().x;
    sprite.move(xChange, y);
}

void Money::setPos(float x, float y) {
    sprite.setPosition(x, y);
}

const sf::Sprite& Money::getSprite() const {
    return sprite;
}