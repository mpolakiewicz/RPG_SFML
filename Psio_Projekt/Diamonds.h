#ifndef DIAMONDS_H
#define DIAMONDS_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <memory>

class Diamonds
{
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect animation_frame;
    sf::Clock clock;
    int up_down_move;


    void texture_initialize();
    void sprite_initialize();
    void animation_initialize();
    void variables_initialize();
public:
    Diamonds();
    virtual ~Diamonds();

    void update();
    void animation_update();
    void render(sf::RenderTarget& target);
    sf::FloatRect get_bounds();
};

#endif // DIAMONDS_H
