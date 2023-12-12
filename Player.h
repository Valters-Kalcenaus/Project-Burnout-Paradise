#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {
public:
    Player();

    void update(sf::Time deltaTime);
    void handleInput();
    void reset();

    // Movement methods
    void jump(float velocity);
    void setVelocityX(float vx);
    void startFalling();

    // Energy methods
    void consumeEnergy(float amount);
    void addEnergy(float amount);
    float getEnergy() const;

    // Money methods
    void consumeMoney(float amount);
    void addMoney(float amount);
    float getMoney() const;

    // Score methods
    void addScore(float amount);
    float getScore() const;

    // Collision and position methods
    bool isJumping;
    bool isFalling() const;
    void land(float y);
    const sf::Sprite& getSprite() const;

    void sleep(sf::Time deltaTime);
    void call(sf::Time deltaTime);
    void deadBeat(sf::Time deltaTime);
    void wakeUp();
    void stopCalling();


private:
    sf::Sprite sprite;
    static sf::Texture texture;
    sf::Vector2f velocity;
    float jumpVelocity;
    float energy;
    float money;
    int score;
    int jumpCount;
    bool isSleeping;
    bool callingParents;
    sf::Clock sleepTimer;
    sf::Clock callTimer;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // PLAYER_H
