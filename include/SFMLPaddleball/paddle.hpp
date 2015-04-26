//
// Created by Kenneth on 4/23/2015.
//

#ifndef SFMLPADDLEBALL_PADDLE_HPP
#define SFMLPADDLEBALL_PADDLE_HPP

#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////
/// \brief Paddle object for use in SFML Paddleball game.
///
///////////////////////////////////////////////////////////
class Paddle
{
public:
    ///////////////////////////////////////////////////////////
    /// \brief Possible movement states for a Paddle.
    ///
    ///////////////////////////////////////////////////////////
    enum PADDLE_DIRECTION
    {
        UP,    ///< Paddle moving towards top of window.
        DOWN,  ///< Paddle moving towards bottom of window.
        NONE   ///< Paddle idle.
    };

    ///////////////////////////////////////////////////////////
    /// \brief Construct a new Paddle.
    ///
    /// \param width      The width of the paddle in pixels.
    /// \param height     The height of the paddle in pixels.
    /// \param move_speed The movement speed of the paddle in
    ///                   approximate pixels per second.
    ///
    ///////////////////////////////////////////////////////////
    Paddle(float width, float height, float move_speed);

    ~Paddle();

    ///////////////////////////////////////////////////////////
    /// \brief Update Paddle state.
    ///
    /// \param delta_t  Time elapsed since last update.
    ///
    ///////////////////////////////////////////////////////////
    void update(float delta_t);

    ///////////////////////////////////////////////////////////
    /// \brief Draw the Paddle to an SFML RenderWindow.
    ///
    /// \param window  The RenderWindow to draw to.
    ///
    ///////////////////////////////////////////////////////////
    void draw(sf::RenderWindow& window) const;

    ///////////////////////////////////////////////////////////
    /// \brief Get current position of the Paddle.
    ///
    /// \return The current position of the Paddle.
    ///
    ///////////////////////////////////////////////////////////
    sf::Vector2f getPosition() const;

    ///////////////////////////////////////////////////////////
    /// \brief Set the position of the Paddle.
    ///
    /// \param position  The new Paddle position.
    ///
    ///////////////////////////////////////////////////////////
    void setPosition(const sf::Vector2f& position);

    ///////////////////////////////////////////////////////////
    /// \brief Get the current PADDLE_DIRECTION of the Paddle.
    ///
    /// \return The PADDLE_DIRECTION of the Paddle.
    ///
    ///////////////////////////////////////////////////////////
    PADDLE_DIRECTION getMovement() const;

    ///////////////////////////////////////////////////////////
    /// \brief Set the current PADDLE_DIRECTION of the Paddle.
    ///
    /// \param direction  The new Paddle PADDLE_DIRECTION.
    ///
    ///////////////////////////////////////////////////////////
    void setMovement(PADDLE_DIRECTION direction);

    ///////////////////////////////////////////////////////////
    /// \brief Get a bounding box containing the Paddle.
    ///
    /// \return An SFML Rect bounding the Paddle.
    ///
    ///////////////////////////////////////////////////////////
    sf::Rect<float> getBoundingBox() const;

private:
    float move_speed_;
    float vspeed_;
    sf::RectangleShape paddle_shape_;

    void move(float delta_t);
};

#endif //SFMLPADDLEBALL_PADDLE_HPP
