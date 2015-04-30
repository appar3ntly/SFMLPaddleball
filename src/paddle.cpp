//
// Created by Kenneth on 4/23/2015.
//

#include "SFMLPaddleball/paddle.hpp"

Paddle::Paddle(float width, float height) :
        paddle_shape_(sf::Vector2f(width, height))
{
    paddle_shape_.setFillColor(sf::Color::Red);
}

Paddle::~Paddle()
{

}

void Paddle::update(float delta_t)
{
    move(delta_t);
}

void Paddle::draw(sf::RenderWindow& window) const
{
    window.draw(paddle_shape_);
}

sf::Vector2f Paddle::getPosition() const
{
    return paddle_shape_.getPosition();
}

void Paddle::setPosition(const sf::Vector2f& position)
{
    paddle_shape_.setPosition(position);
}

float Paddle::getVSpeed() const
{
    return vspeed_;
}

void Paddle::setVSpeed(float vspeed)
{
    vspeed_ = vspeed;
}

sf::Rect<float> Paddle::getBoundingBox() const
{
    return sf::Rect<float>(paddle_shape_.getPosition(), paddle_shape_.getSize());
}

void Paddle::move(float delta_t)
{
    paddle_shape_.move(0.0, delta_t * vspeed_);
}
