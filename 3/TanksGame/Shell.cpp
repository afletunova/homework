#include <cmath>
#include <math.h>

#include "vendor/easylogging++.h"
#include "Game.h"
#include "Tank.h"

void Shell::draw(sf::RenderWindow &window)
{
    window.draw(shape, getSprite()->getTransform());
    if (bang)
    {
        window.draw(bangShape);
        bang = false;
    }
}

void Shell::update(float elapsedTime)
{
    time = time + elapsedTime;
    float x = speed * cos(angle * M_PI / 180.0f) * time;
    float y = speed * sin(angle * M_PI / 180.0f) * time + gravity * time * time / 2;
    setPosition(startX + x, startY + y);

    if ((this->getPositionX() < 0 || this->getPositionX() > Game::width
            || this->getPositionY() > getWorld()->getTerrain()->getHeightAt((int) this->getPositionX())) && active)
    {
        active = false;
        bang = true;
        bangShape.setPosition(this->getPositionX(), this->getPositionY());
        bangShape.setFillColor(sf::Color::Black);
        bangShape.setRadius(this->getDamageRadius());
    }

    bool collide = this->isCollide(getWorld()->getOpponent());

    if (collide)
    {
        active = false;
        Command command;
        command.name = "gameOver";
        command.argumentsCount = 0;
        command.arguments = new int[command.argumentsCount];
        getWorld()->getNetworkManager()->send(command);
        getWorld()->getGame()->over(true);
    }
}

Shell::~Shell()
{}

Shell *Shell::clone() const
{
    return new Shell(*this);
}

void Shell::setAngle(float angle)
{
    this->angle = angle;
}

float Shell::getSpeed() const
{
    return speed;
}

void Shell::setPosition(const float x, const float y)
{
    Entity::setPosition(x, y);
    startX = x;
    startY = y;
}

Shell::Shell(GameWorld *world, float speed, unsigned int radius, float damageRadius) : Entity(world),
                                                                   speed(speed),
                                                                   radius(radius),
                                                                   shape(radius), damageRadius(damageRadius)
{
    shape.setFillColor(sf::Color::Black);
    shape.setOrigin(radius / 2, radius / 2);
}

Shell::Shell(const Shell &shell) : Shell(shell.getWorld(), shell.getSpeed(), shell.getRadius(), shell.getDamageRadius())
{}

unsigned int Shell::getRadius() const
{
    return radius;
}

bool Shell::isActive() const
{
    return active;
}

bool Shell::isCollide(Tank *player)
{
    if (!isActive())
        return false;

    int deltaX = (int) (this->getPositionX() - player->getPositionX());
    int deltaY = (int) (this->getPositionY() - (player->getPositionY() - player->getSpriteRadius()));
    int delta = (int) (player->getSpriteRadius() + getDamageRadius());

    return deltaX * deltaX + deltaY * deltaY < delta * delta;
}

float Shell::getDamageRadius() const
{
    return damageRadius;
}
