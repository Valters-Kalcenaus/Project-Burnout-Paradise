#include "Energy.h"
#include <iostream>

sf::Texture Energy::texture;

//same application as Distraction.cpp and Money.cpp

Energy::Energy(float x, float y) {
    if (texture.getSize().x == 0) {
        if (!texture.loadFromFile("Energy.png")) {
            std::cerr << "Failed to load Energy.png" << std::endl;
        }
    }

    sprite.setTexture(texture);

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

void Energy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

float Energy::getTopPosition() const {
    return sprite.getPosition().y;
}

void Energy::move(float y) {
    sprite.move(0, y);
}

void Energy::setPos(float x, float y) {
    sprite.setPosition(x, y);
}

const sf::Sprite& Energy::getSprite() const {
    return sprite;
}
