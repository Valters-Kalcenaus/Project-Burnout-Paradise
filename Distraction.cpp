#include "Distraction.h"
#include <iostream>

sf::Texture Distraction::texture;

Distraction::Distraction(float x, float y) {
    if (texture.getSize().x == 0) { // Load texture only once
        if (!texture.loadFromFile("Woman.png")) {
            std::cout << "Failed to load Woman.png" << std::endl;
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
    sprite.setPosition(x, y);
}

void Distraction::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Distraction::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

const sf::Sprite& Distraction::getSprite() const {
    return sprite;
}
