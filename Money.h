#ifndef MONEY_H
#define MONEY_H

#include <SFML/Graphics.hpp>

// Money class definition
class Money : public sf::Drawable {
public:
    Money(float x, float y);

    float getTopPosition() const;

    const sf::Sprite& getSprite() const;

    // Moves the Money sprite vertically by a specified amount
    void move(float y);

    void setPos(float x, float y);

private:
    sf::Sprite sprite;

    // Static texture shared by all Money objects
    static sf::Texture texture;

    //draws the object
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif 
