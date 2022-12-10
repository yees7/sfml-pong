#include <SFML/Graphics.hpp>

#pragma once

class Paddle {
    public:
        sf::Vector2f originalPos;
        sf::Vector2f pos;
        sf::RectangleShape paddle;

        Paddle(sf::Vector2f pos_);
        void move(float pos_x, float pos_y);
        void draw(sf::RenderWindow& window);
        void resetPos();
};