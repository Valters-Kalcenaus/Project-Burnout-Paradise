#ifndef ENERGY_H
#define ENERGY_H

#include <SFML/Graphics.hpp>

class Energy : public sf::Drawable {
public:
    Energy(float x, float y);

    float getTopPosition() const;
    void move(float y);
    void setPos(float x, float y);
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite sprite;
    static sf::Texture texture;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif 
