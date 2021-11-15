#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Background
{
    sf::Sprite sprite;
    sf::Texture texture;
    void texture_initialize();
    void sprite_initialize();
public:
    Background();
    virtual ~Background();

    void render(sf::RenderTarget& target);
};

#endif // BACKGROUND_H
