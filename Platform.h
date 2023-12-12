#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

class Platform : public sf::Drawable {
public:
    Platform(float x, float y, float width, float height, sf::Color color);

    float getTopPosition() const;
    const sf::RectangleShape& getShape() const;


private:
    sf::RectangleShape shape;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // PLATFORM_H

