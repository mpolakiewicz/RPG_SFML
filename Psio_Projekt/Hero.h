#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Diamonds.h"
#include "Totem.h"

enum Movement_states {idle = 0, left, right, up, down, attack, dead};

class Hero
{
    sf::Sprite sprite;
    sf::Texture texture_run;
    sf::Texture texture_idle;
    sf::Texture texture_dead;
    sf::Texture texture_attack;
    sf::IntRect animation_frame_idle;
    sf::IntRect animation_frame_run;
    sf::IntRect animation_frame_death;
    sf::IntRect animation_frame_end;
    sf::IntRect animation_frame_attack;
    sf::IntRect still_frame;
    sf::Clock clock;
    Movement_states state;

    int health;
    int counter_death;
    int counter_attack;

    sf::SoundBuffer buffer_collect;
    sf::Sound collect;
    sf::SoundBuffer buffer_sword;
    sf::Sound sword;
    sf::SoundBuffer buffer_death;
    sf::Sound death;

    sf::RectangleShape hp_bar;
    void hp_bar_initialize();

    void texture_initialize();
    void sprite_initialize();
    void animation_initialize();
    void variables_initialize();
    void sound_initialize();
public:
    Hero();
    virtual ~Hero();

    void update(std::vector<std::shared_ptr<Diamonds>> &diam_vec, sf::Event &event, Totem *totem, sf::RenderWindow &window);
    void move_update(sf::RenderWindow &window, Totem *totem);
    void animation_update();
    void intersection_update(std::vector<std::shared_ptr<Diamonds>> &diam_vec, Totem *totem);
    void health_update();
    void hp_bar_update();
    void on_mouse_click(sf::Event &event);
    void render(sf::RenderTarget& target);
    sf::FloatRect get_bounds();
    int get_counter_attack();
    int get_counter_death();
    Movement_states get_state();
    void damage();
};

#endif // HERO_H
