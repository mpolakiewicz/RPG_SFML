#ifndef SKELETON_H
#define SKELETON_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Hero.h"


class Skeleton
{
    sf::Sprite sprite;
    sf::Texture texture_walk;
    sf::Texture texture_idle;
    sf::Texture texture_dead;
    sf::Texture texture_attack;
    sf::IntRect animation_frame_idle;
    sf::IntRect animation_frame_walk;
    sf::IntRect animation_frame_death;
    //sf::IntRect animation_frame_end;
    sf::IntRect animation_frame_attack;
    sf::IntRect still_frame;
    sf::Clock clock1;
    sf::Clock clock2;
    Movement_states state;

    int health;
    int counter_death;
    int counter_attack;

    sf::SoundBuffer buffer_skeleton_attack;
    sf::Sound skeleton_attack;

    sf::SoundBuffer buffer_skeleton_death;
    sf::Sound skeleton_death;

    void texture_initialize();
    void sprite_initialize();
    void animation_initialize();
    void variables_initialize();
    void sound_initialize();

public:
    Skeleton();
    virtual ~Skeleton();

    void update(Hero *hero, Totem *totem);
    void move_update(Hero *hero);
    void animation_update(Hero *hero);
    void intersection_update(Hero *hero, Totem *totem);
    void health_update();
    void render(sf::RenderTarget& target);
    sf::FloatRect get_bounds();
    void damage();
    Movement_states get_state();
    int get_counter_death();

};

#endif // SKELETON_H
