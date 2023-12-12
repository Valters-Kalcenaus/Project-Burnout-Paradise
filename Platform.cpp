#include "Platform.h"

Platform::Platform(float x, float y, float width, float height, sf::Color color) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
}

void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}

float Platform::getTopPosition() const {
    return shape.getPosition().y;
}


const sf::RectangleShape& Platform::getShape() const {
    return shape;
}
