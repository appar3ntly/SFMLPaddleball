//
// Created by Kenneth on 4/23/2015.
//

#ifndef SFMLPADDLEBALL_BALL_HPP
#define SFMLPADDLEBALL_BALL_HPP

#include <SFML/Graphics.hpp>
#include "SFMLPaddleball/paddle.hpp"

///////////////////////////////////////////////////////////
/// \brief Ball object for use in SFML Paddleball game.
///
///////////////////////////////////////////////////////////
class Ball
{
public:
    ///////////////////////////////////////////////////////////
    /// \brief Construct a new Ball.
    ///
    /// Constructs a Ball object with the parameters specified.
    /// Parameters start_hspeed and start_vspeed are used to
    /// set Ball state at the start of each round.
    ///
    /// \param radius        The radius of the ball.
    /// \param start_hspeed  The horizontal speed of the ball
    ///                      at the start of every round.
    /// \param start_vspeed  The vertical speed of the ball
    ///                      at the start of every round.
    ///
    ///////////////////////////////////////////////////////////
    Ball(float radius, float start_hspeed, float start_vspeed);
    ~Ball();

    ///////////////////////////////////////////////////////////
    /// \brief Update ball state.
    ///
    /// \param delta_t  Time elapsed since last update call.
    ///
    ///////////////////////////////////////////////////////////
    void update(float delta_t);

    ///////////////////////////////////////////////////////////
    /// \brief Draw the ball to an SFML RenderWindow.
    ///
    /// \param window  Reference to the RenderWindow to be
    ///                drawn to.
    ///
    ///////////////////////////////////////////////////////////
    void draw(sf::RenderWindow& window);

    ///////////////////////////////////////////////////////////
    /// \brief Process bouncing on contact with a Paddle.
    ///
    /// \param paddle  The Paddle the current Ball collided with
    ///
    ///////////////////////////////////////////////////////////
    void bouncePaddle(const Paddle& paddle);

    ///////////////////////////////////////////////////////////
    /// \brief Process bouncing on contact with "walls".
    ///
    /// Enacts bounce behavior for contact with top and
    /// bottom edges of the game window.
    ///
    ///////////////////////////////////////////////////////////
    void bounceWall();

    ///////////////////////////////////////////////////////////
    /// \brief Reset Ball state for new round.
    ///
    /// Resets Ball horizontal speed, vertical speed, and position.
    ///
    ///////////////////////////////////////////////////////////
    void resetMovement();

    ///////////////////////////////////////////////////////////
    /// \brief Get the current position of the Ball.
    ///
    /// \return The position of the Ball.
    ///
    ///////////////////////////////////////////////////////////
    sf::Vector2f getPosition() const;

    ///////////////////////////////////////////////////////////
    /// \brief Set the current position of the Ball.
    ///
    /// \param position  The new position of the Ball.
    ///
    ///////////////////////////////////////////////////////////
    void setPosition(const sf::Vector2f& position);

    ///////////////////////////////////////////////////////////
    /// \brief Get the radius of the Ball.
    ///
    /// \return The radius of the Ball.
    ///
    ///////////////////////////////////////////////////////////
    float getRadius() const;

    ///////////////////////////////////////////////////////////
    /// \brief Get the diameter of the Ball.
    ///
    /// Convenience method, simply returns 2 * radius.
    ///
    /// \return The diameter of the Ball.
    ///
    ///////////////////////////////////////////////////////////
    float getDiameter() const;

    ///////////////////////////////////////////////////////////
    /// \brief Get a bounding box containing the Ball.
    ///
    /// \return An SFML Rect bounding the Ball.
    ///
    ///////////////////////////////////////////////////////////
    sf::Rect<float> getBoundingBox() const;

    ///////////////////////////////////////////////////////////
    /// \brief Get the horizontal speed of the Ball.
    ///
    /// \return The horizontal speed of the Ball.
    ///
    ///////////////////////////////////////////////////////////
    float getHSpeed() const;

private:
    sf::CircleShape ball_shape_;
    float start_hspeed_;
    float start_vspeed_;
    float hspeed_;
    float vspeed_;
    sf::Vector2f previous_position_;
    int lastPaddleHit_;

    void move(float delta_t);
};
#endif //SFMLPADDLEBALL_BALL_HPP
