#include <SFML/Graphics.hpp>
#include "button.h"
#include <iostream>

Button::Button(sf::Vector2f pos_, sf::Vector2f size_, std::string text_, sf::Font& font, float font_size, sf::Color button_color_, sf::Color button_color_hover_, sf::Color button_color_click_, sf::Color text_color, float outline, sf::Color outline_color) {
    button.setPosition(pos_);
    button.setSize(size_);
    button.setFillColor(button_color_);
    button.setOutlineThickness(outline);
    button.setOutlineColor(outline_color);
    text.setFont(font);
    text.setCharacterSize(font_size);
    text.setString(text_);
    text.setFillColor(text_color);
    text.setPosition(pos_.x+(size_.x-text.getGlobalBounds().width)/2, pos_.y+(size_.y-text.getGlobalBounds().height)/2);
    pos = pos_;
    size = size_;
    button_color = button_color_;
    button_color_click = button_color_click_;
    button_color_hover = button_color_hover_;
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

bool Button::checkClick(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (mousePos.x > pos.x
        && mousePos.x < pos.x + size.x
        && mousePos.y > pos.y
        && mousePos.y < pos.y + size.y) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                button.setFillColor(button_color_click);
                isClick = true;
            } else if (isClick == true) {
                isClick = false;
                return true;
            } else {
                button.setFillColor(button_color_hover);
            }
        } else {
            button.setFillColor(button_color);
        }
    return false;
}