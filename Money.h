#ifndef MONEY_H
#define MONEY_H

#include <SFML/Graphics.hpp>

class Money : public sf::Drawable {
public:
    Money(float x, float y);

    float getTopPosition() const;
    const sf::Sprite& getSprite() const;
    void move(float y);
    void setPos(float x, float y);

private:
    sf::Sprite sprite;
    static sf::Texture texture;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // MONEY_H
