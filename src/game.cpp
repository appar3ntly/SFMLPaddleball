//
// Created by Kenneth on 4/23/2015.
//

#include "SFMLPaddleball/game.hpp"
#include <thread>

Game::Game() :
    ball_(10.0, 150.0, 150.0),
    paddle1_(10.0, 60.0),
    paddle2_(10.0, 60.0),
    paddle_speed_(600.0),
    p1_score_(0),
    p2_score_(0)
{
    render_window_.create(sf::VideoMode(800, 600), "SFMLPaddleball");
    score_font_.loadFromFile("assets/fonts/digital-7 (mono).ttf");

    // Configure text for player scores.
    p1_score_text_.setFont(score_font_);
    p2_score_text_.setFont(score_font_);
    p1_score_text_.setPosition(0.25f * render_window_.getSize().x, 60.0);
    p2_score_text_.setPosition(0.75f * render_window_.getSize().x, 60.0);
    p1_score_text_.setCharacterSize(24);
    p2_score_text_.setCharacterSize(24);
    p1_score_text_.setColor(sf::Color::White);
    p2_score_text_.setColor(sf::Color::White);

    // Configure text for PAUSED notification.
    pause_text_.setFont(score_font_);
    pause_text_.setCharacterSize(72);
    pause_text_.setColor(sf::Color::White);
    pause_text_.setString("PAUSED");
    pause_text_.setPosition((render_window_.getSize().x -
                             pause_text_.getLocalBounds().width) / 2, 300.0);
}

Game::~Game()
{

}

void Game::start()
{
    // Start game state management in GAME_START
    game_state_ = Game::STATE::GAME_START;

    // Start drawing thread.
    render_window_.setActive(false);
    std::thread draw_thread(&Game::draw, this);

    while (render_window_.isOpen())
    {
        // Window poll loop.
        sf::Event event;
        while (render_window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                render_window_.close();
                draw_thread.join();
                return;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::Escape)
                {
                    switch (game_state_)
                    {
                        case Game::STATE::PLAYING:
                            game_state_ = Game::STATE::PAUSED;
                            break;
                        case Game::STATE::PAUSED:
                            game_state_ = Game::STATE::PLAYING;
                            break;
                    }
                }
            }

            if (event.type == sf::Event::LostFocus)
            {
                game_state_ = Game::STATE::PAUSED;
            }
        }

        float elapsed_time = game_clock_.restart().asSeconds();

        // Determine next action to take and if we need to change states.
        switch (game_state_)
        {
            case Game::STATE::GAME_START:
                game_clock_.restart();
                game_state_ = Game::STATE::ROUND_START;
                break;
            case Game::STATE::ROUND_START:
                setupNewRound();
                game_state_ = Game::STATE::PLAYING;
                break;
            case Game::STATE::PLAYING:
                // Process paddle movements by players.
                processPaddleMovements();
                // Call update method to update game object positions.
                update(elapsed_time);
                // Check if a player has scored.
                checkForScore();
                // Check collisions.
                collisionChecks();
                break;
            case Game::STATE::PAUSED:
                game_clock_.restart();
                break;
            case Game::STATE::ROUND_END:
                game_state_ = Game::STATE::ROUND_START;
                break;
            case Game::STATE::GAME_END:
                game_state_ = Game::STATE::GAME_START;
                break;
        }
    }
}

void Game::update(float delta_t)
{
    ball_.update(delta_t);
    paddle1_.update(delta_t);
    paddle2_.update(delta_t);
    p1_score_text_.setString(std::to_string(p1_score_));
    p2_score_text_.setString(std::to_string(p2_score_));
}

void Game::draw()
{
    while (render_window_.isOpen())
    {
        render_window_.clear(sf::Color::Black);

        ball_.draw(render_window_);
        paddle1_.draw(render_window_);
        paddle2_.draw(render_window_);

        render_window_.draw(p1_score_text_);
        render_window_.draw(p2_score_text_);

        if (game_state_ == Game::STATE::PAUSED)
            render_window_.draw(pause_text_);

        render_window_.display();
    }
}

void Game::setupNewRound()
{
    // Reset positions and movement characteristics of paddles and ball.
    paddle1_.setPosition(sf::Vector2f(60.0, render_window_.getSize().y / 2));
    paddle2_.setPosition(sf::Vector2f(render_window_.getSize().x - 60.0f,
                                      render_window_.getSize().y / 2));
    ball_.setPosition(sf::Vector2f(render_window_.getSize().x / 2,
                                   render_window_.getSize().y / 2));
    ball_.resetMovement();
}

void Game::checkForScore()
{
    // Check for ball outside of play area.
    sf::Vector2f ball_position = ball_.getPosition();
    float ball_right = ball_position.x + ball_.getDiameter();

    if (ball_position.x < 0 || ball_right > render_window_.getSize().x)
    {
        game_state_ = Game::STATE::ROUND_END;
        if (ball_position.x < 0)
            ++p2_score_;
        else
            ++p1_score_;

        return;
    }
}

void Game::collisionChecks()
{
    // Check for ball colliding with top or bottom of screen.
    sf::Vector2f ball_position = ball_.getPosition();
    if (ball_position.y < 0 || ball_position.y + ball_.getDiameter() > render_window_.getSize().y)
        ball_.bounceWall();

    // Check for ball colliding with paddles.
    sf::Rect<float> ball_rect = ball_.getBoundingBox();
    sf::Rect<float> paddle1_rect = paddle1_.getBoundingBox();
    sf::Rect<float> paddle2_rect = paddle2_.getBoundingBox();

    // Check ball hspeed as well as intersection to make sure we don't collide
    // and trigger bounce actions multiple times per paddle!
    if (ball_rect.intersects(paddle1_rect) && ball_.getHSpeed() < 0)
        ball_.bouncePaddle(paddle1_);
    else if (ball_rect.intersects(paddle2_rect) && ball_.getHSpeed() > 0)
        ball_.bouncePaddle(paddle2_);
}

void Game::processPaddleMovements()
{
    sf::Vector2f paddle1_position = paddle1_.getPosition();
    sf::Vector2f paddle2_position = paddle2_.getPosition();

    // Process input for player one.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        if (paddle1_position.y > 0)
            paddle1_.setVSpeed(-paddle_speed_);
        else
            paddle1_.setVSpeed(0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        if (paddle1_position.y + paddle1_.getBoundingBox().height < render_window_.getSize().y)
            paddle1_.setVSpeed(paddle_speed_);
        else
            paddle1_.setVSpeed(0);
    else
        paddle1_.setVSpeed(0);

    // Process input for player two.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        if (paddle2_position.y > 0)
            paddle2_.setVSpeed(-paddle_speed_);
        else
            paddle2_.setVSpeed(0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        if (paddle2_position.y + paddle2_.getBoundingBox().height < render_window_.getSize().y)
            paddle2_.setVSpeed(paddle_speed_);
        else
            paddle2_.setVSpeed(0);
    else
        paddle2_.setVSpeed(0);
}
