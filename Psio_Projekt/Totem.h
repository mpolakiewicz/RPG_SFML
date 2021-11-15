#ifndef TOTEM_H
#define TOTEM_H
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Totem
{
    sf::Sprite sprite;
    sf::Texture texture_totem;
    sf::Texture texture_treasure;
    int health;
    void texture_initialize();
    void sprite_initialize();
    void animation_initialize();
    void variables_initialize();

    sf::SoundBuffer buffer_win;
    void hp_bar_initialize();

    sf::Sound win;
    void sound_initialize();

    sf::RectangleShape hp_bar;
public:
    Totem();
    virtual ~Totem();

    void update();
    void animation_update();
    void render(sf::RenderTarget& target);
    sf::FloatRect get_bounds();
    int get_health();
    void check_health();
    void damage();
    void hp_bar_update();

};

#endif // TOTEM_H
