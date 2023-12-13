#include "Hazard.h"

Hazard::Hazard(float y) {
    shape.setPosition(0, y);
    shape.setSize(sf::Vector2f(800, 800));
    shape.setFillColor(sf::Color::Yellow);
}

void Hazard::update(sf::Time deltaTime) {
    float speed = 100.f;
    shape.move(0, -speed * deltaTime.asSeconds()); // Move the hazard upwards.

}

// Reset position.
void Hazard::reset() {
    shape.setPosition(0, 600);
}

void Hazard::chaseCorrect(float playerPos) {
    shape.setPosition(0, playerPos + 1000); // Set the hazard's position to a fixed distance below the player.

}

void Hazard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}

const sf::RectangleShape& Hazard::getShape() const {
    return shape;
}
