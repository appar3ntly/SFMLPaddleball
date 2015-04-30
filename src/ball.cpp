//
// Created by Kenneth on 4/23/2015.
//

#include "SFMLPaddleball/ball.hpp"

Ball::Ball(float radius, float start_hspeed, float start_vspeed) :
        start_hspeed_(start_hspeed),
        start_vspeed_(start_vspeed),
        ball_shape_(radius, 300)
{
    ball_shape_.setFillColor(sf::Color::Blue);
}

Ball::~Ball()
{

}

void Ball::update(float delta_t)
{
    previous_position_ = getPosition();
    move(delta_t);
}

void Ball::draw(sf::RenderWindow& window)
{
    window.draw(ball_shape_);
}

void Ball::bouncePaddle(const Paddle& paddle)
{
    setPosition(previous_position_);

    // Reverse horizontal speed and apply some extra speed on reflection.
    hspeed_ *= -1.05;

    // Impart some of paddle momentum on to ball.
    float paddle_speed = paddle.getVSpeed();

    // Paddle moving down.
    if (paddle_speed > 0)
        vspeed_ += 100.0;
    // Paddle moving up.
    else if (paddle_speed < 0)
        vspeed_ -= 100.0;
    // Paddle stationary.
    else
        hspeed_ *= 1.05;
}

void Ball::bounceWall()
{
    setPosition(previous_position_);

    vspeed_ *= -1;
}

void Ball::resetMovement()
{
    vspeed_ = 0.0;

    // Randomly send the ball left or right.
    int left = std::rand() % 2;
    if (left)
        hspeed_ = -start_hspeed_;
    else
        hspeed_ = start_hspeed_;
}

sf::Vector2f Ball::getPosition() const
{
    return ball_shape_.getPosition();
}

void Ball::setPosition(const sf::Vector2f& position)
{
    ball_shape_.setPosition(position);
}

float Ball::getRadius() const
{
    return ball_shape_.getRadius();
}

float Ball::getDiameter() const
{
    return 2 * getRadius();
}

sf::Rect<float> Ball::getBoundingBox() const
{
    return sf::Rect<float>(ball_shape_.getPosition(),
                           sf::Vector2<float>(getDiameter(), getDiameter()));
}

float Ball::getHSpeed() const
{
    return hspeed_;
}

void Ball::move(float delta_t)
{
    ball_shape_.move(delta_t * hspeed_, delta_t * vspeed_);
}
