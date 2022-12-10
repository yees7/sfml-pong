#include <SFML/Graphics.hpp>

#pragma once

class Button {
    public:
        sf::Vector2f pos, size;
        sf::RectangleShape button;
        sf::Text text;
        bool isClick = false;

        sf::Color button_color, button_color_hover, button_color_click;

        Button(sf::Vector2f pos_, sf::Vector2f size_, std::string text_, sf::Font& font, float font_size, sf::Color button_color_, sf::Color button_color_hover_, sf::Color button_color_click_, sf::Color text_color, float outline, sf::Color outline_color);
        void draw(sf::RenderWindow& window);
        bool checkClick(sf::RenderWindow& window);
};