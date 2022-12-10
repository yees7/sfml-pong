#include <SFML/Graphics.hpp>
#include "paddle.h"

Paddle::Paddle(sf::Vector2f pos_) {
    paddle.setPosition(pos_);
    paddle.setSize(sf::Vector2f(10.f, 100.f));
    pos = pos_;
    originalPos = pos_;
}

void Paddle::move(float pos_x, float pos_y) {
    paddle.move(pos_x, pos_y);
    pos.x += pos_x;
    pos.y += pos_y;
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(paddle);
}

void Paddle::resetPos() {
    paddle.setPosition(originalPos);
    pos = originalPos;
}