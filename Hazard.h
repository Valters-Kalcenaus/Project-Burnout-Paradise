#ifndef HAZARD_H
#define HAZARD_H

#include <SFML/Graphics.hpp>

class Hazard : public sf::Drawable {
public:
    Hazard(float y);

    void update(sf::Time deltaTime);
    void reset();
    void chaseCorrect(float playerPos);
    const sf::RectangleShape& getShape() const;

private:
    sf::RectangleShape shape;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
