#include <SFML/Graphics.hpp>
#include <iostream>
#include "button/button.h"
#include "paddle/paddle.h"

struct gameStatus {bool gameEnded; bool winner; bool singlePlayer;};

void drawGame(Paddle& paddle1, Paddle& paddle2, sf::CircleShape& ball, sf::Vector2f& velocity, sf::Time dt, sf::RenderWindow& window, gameStatus& status);
void drawGameEnded(sf::RenderWindow& window, gameStatus& status, sf::Text& winningText, Button& singlePlayerButton, Button& twoPlayerButton, sf::CircleShape& ball, sf::Vector2f& velocity, Paddle& paddle1, Paddle& paddle2);
void resetGame(sf::RenderWindow& window, gameStatus& status, sf::CircleShape& ball, sf::Vector2f& velocity, Paddle& paddle1, Paddle& paddle2);

const int paddleSpeed = 400.f;
const int aiSpeed = 200.f;
const float velocityModifier = 1.1f;
bool appStart = true;

int main()
{
    srand((unsigned) time(NULL));
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Pong Game");

    ////////////////////////
    //   COLORS & FONTS   //
    ///////////////////////

    sf::Color grey1(80, 80, 80);
    sf::Color grey2(40, 40, 40);
    sf::Color grey3(100, 100, 100);
    sf::Color grey4(110, 110, 110);

    sf::Font droid_sans;
    if (!droid_sans.loadFromFile("data/droid_sans.ttf")) {
        return 0;
    }

    /////////////////////
    //     SHAPES      //
    ////////////////////

    // paddles

    Paddle paddle1(sf::Vector2f(20.f, 350.f));

    Paddle paddle2(sf::Vector2f(1170.f, 350.f));

    // ball

    sf::CircleShape ball(10.f);
    ball.setPosition(595.f, 395.f);
    sf::Vector2f velocity(300.f - (300.f * (rand() % 2 * 2)), rand() % 400 - 200.f);

    // winning text

    sf::Text winningText;
    winningText.setFont(droid_sans);
    winningText.setCharacterSize(100);
    winningText.setFillColor(grey1);
    winningText.setPosition(300.f, 100.f);

    // new game button

    Button singlePlayerButton(sf::Vector2f(100.f, 500.f), sf::Vector2f(400.f, 150.f), "1 Player", droid_sans, 24.f, grey1, grey3, grey4, grey2, 10, grey2);
    Button twoPlayerButton(sf::Vector2f(700.f, 500.f), sf::Vector2f(400.f, 150.f), "2 Players", droid_sans, 24.f, grey1, grey3, grey4, grey2, 10, grey2);

    /////////////////////
    //   MAIN LOOP     //
    ////////////////////

    sf::Clock deltaTime;
    gameStatus status;
    status.gameEnded = true;

    while (window.isOpen())
    {
        sf::Time dt = deltaTime.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!status.gameEnded) {
            drawGame(paddle1, paddle2, ball, velocity, dt, window, status);
            continue;
        }
        drawGameEnded(window, status, winningText, singlePlayerButton, twoPlayerButton, ball, velocity, paddle1, paddle2);

    }

    return 0;
}

void drawGame(Paddle& paddle1, Paddle& paddle2, sf::CircleShape& ball, sf::Vector2f& velocity, sf::Time dt, sf::RenderWindow& window, gameStatus& status) {
    // check movement keys

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle1.pos.y < 700.f) {
        paddle1.move(0.f, paddleSpeed*dt.asSeconds());
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle1.pos.y > 0.f) {
        paddle1.move(0.f, -paddleSpeed*dt.asSeconds());
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle2.pos.y < 700.f) {
        status.singlePlayer ? paddle1.move(0.f, paddleSpeed*dt.asSeconds()) : paddle2.move(0.f, paddleSpeed*dt.asSeconds());
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle2.pos.y > 0.f) {
        status.singlePlayer ? paddle1.move(0.f, -paddleSpeed*dt.asSeconds()) : paddle2.move(0.f, -paddleSpeed*dt.asSeconds());
    }

    // move right paddle if 1 player

    if (status.singlePlayer) {
        if (ball.getPosition().y > paddle2.pos.y + 45.f && paddle2.pos.y + 100.f < 800.f)
            paddle2.move(0.f, aiSpeed*dt.asSeconds());
        else if (ball.getPosition().y < paddle2.pos.y + 45.f && paddle2.pos.y > 0.f)
            paddle2.move(0.f, -aiSpeed*dt.asSeconds());
    }

    // check if ball has hit left paddle

    if (ball.getPosition().x < 30.f
        && ball.getPosition().x > 10.f
        && ball.getPosition().y + 10.f > paddle1.pos.y
        && ball.getPosition().y + 10.f < paddle1.pos.y + 100.f) {

            ball.setPosition(30.f, ball.getPosition().y);
            velocity.x*=-1;
            velocity.x+=20;
            velocity.y*=velocityModifier;
        }

    // check if ball has hit right paddle

    else if (ball.getPosition().x + 20.f > 1170.f
        && ball.getPosition().x + 20.f < 1190.f
        && ball.getPosition().y + 10.f > paddle2.pos.y
        && ball.getPosition().y + 10.f < paddle2.pos.y + 100.f) {

            ball.setPosition(1150.f, ball.getPosition().y);
            velocity.x*=-1;
            velocity.x-=20;
            velocity.y*=velocityModifier;
        }

    // check if ball has reached the left side

    else if (ball.getPosition().x + 20.f < 0.f) {
        status.gameEnded = true;
        status.winner = false;
    }

    // check if ball has reached the right side

    else if (ball.getPosition().x > 1200.f) {
        status.gameEnded = true;
        status.winner = true;
    }

    // check if ball has hit top or bottom boundaries

    if (ball.getPosition().y + 20.f >= 800.f || ball.getPosition().y <= 0.f) {
        velocity.y*=-1;
    }

    // move ball

    ball.move(velocity * dt.asSeconds());

    // draw everything on screen

    window.clear();

    paddle1.draw(window);
    paddle2.draw(window);
    window.draw(ball);

    window.display();
}

void drawGameEnded(sf::RenderWindow& window, gameStatus& status, sf::Text& winningText, Button& singlePlayerButton, Button& twoPlayerButton, sf::CircleShape& ball, sf::Vector2f& velocity, Paddle& paddle1, Paddle& paddle2) {
    // change winning text    

    if (appStart)
        winningText.setString("Pong Game");
    else
        winningText.setString(status.winner ? "Player 1 Wins!" : "Player 2 Wins!");

    // button clicks

    if (singlePlayerButton.checkClick(window)) {
        status.singlePlayer = true;
        if (appStart) appStart = false;
        resetGame(window, status, ball, velocity, paddle1, paddle2);
    }

    if (twoPlayerButton.checkClick(window)) {
        status.singlePlayer = false;
        if (appStart) appStart = false;
        resetGame(window, status, ball, velocity, paddle1, paddle2);
    }

    // draw everything on screen
    
    window.clear();

    window.draw(winningText);
    paddle1.draw(window);
    paddle2.draw(window);
    singlePlayerButton.draw(window);
    twoPlayerButton.draw(window);

    window.display();
}

void resetGame(sf::RenderWindow& window, gameStatus& status, sf::CircleShape& ball, sf::Vector2f& velocity, Paddle& paddle1, Paddle& paddle2) {
    status.gameEnded = false;
    ball.setPosition(595.f, 395.f);
    velocity = sf::Vector2f(300.f - (300.f * (rand() % 2 * 2)), rand() % 400 - 200.f);
    paddle1.resetPos();
    paddle2.resetPos();
}