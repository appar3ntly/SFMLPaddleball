//
// Created by Kenneth on 4/23/2015.
//

#ifndef SFMLPADDLEBALL_GAME_HPP
#define SFMLPADDLEBALL_GAME_HPP

#include <SFML/Graphics.hpp>
#include "SFMLPaddleball/paddle.hpp"
#include "SFMLPaddleball/ball.hpp"

///////////////////////////////////////////////////////////
/// \brief SFML Paddleball Game main class.
///
/// Starts and controls the SFML Paddleball game.
///
///////////////////////////////////////////////////////////
class Game
{
public:
    ///////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// Sets up a new Game including SFML RenderWindow and
    /// SFML Clock.
    ///
    ///////////////////////////////////////////////////////////
    Game();

    ~Game();

    ///////////////////////////////////////////////////////////
    /// \brief Start game execution.
    ///
    /// Start main Game loop.  Blocks until game exit.
    ///
    ///////////////////////////////////////////////////////////
    void start();

private:
    enum STATE
    {
        GAME_START,
        ROUND_START,
        PLAYING,
        PAUSED,
        ROUND_END,
        GAME_END
    };

    sf::RenderWindow render_window_;
    sf::Clock game_clock_;
    Game::STATE game_state_;

    Paddle paddle1_;
    Paddle paddle2_;

    Ball ball_;

    int p1_score_;
    int p2_score_;

    sf::Font score_font_;
    sf::Text p1_score_text_;
    sf::Text p2_score_text_;
    sf::Text pause_text_;

    void update(float delta_t);
    void draw();
    void setup();
    void collisionChecks();
    void processPaddleMovements();
};

#endif //SFMLPADDLEBALL_GAME_HPP
