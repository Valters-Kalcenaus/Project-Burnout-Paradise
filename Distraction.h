#ifndef DISTRACTION_H
#define DISTRACTION_H

#include <SFML/Graphics.hpp>

class Distraction : public sf::Drawable {
public:
    Distraction(float x, float y);

    void setPosition(float x, float y);
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite sprite;
    static sf::Texture texture;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // DISTRACTION_H
