#include "Hazard.h"

Hazard::Hazard(float y) {
    shape.setPosition(0, y);
    shape.setSize(sf::Vector2f(800, 800)); // Adjust size as needed
    shape.setFillColor(sf::Color::Yellow); // Color for visibility
}

void Hazard::update(sf::Time deltaTime) {
    // Move the hazard up constantly
    float speed = 100.f; // Adjust speed as needed
    shape.move(0, -speed * deltaTime.asSeconds());
}

void Hazard::reset() {
    shape.setPosition(0, 600);
}

void Hazard::chaseCorrect(float playerPos) {
    shape.setPosition(0, playerPos + 1000);
}

void Hazard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}

const sf::RectangleShape& Hazard::getShape() const {
    return shape;
}
