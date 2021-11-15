#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Hero.h"
#include "Background.h"
#include "Diamonds.h"
#include "Totem.h"
#include "Skeleton.h"

class Game
{
    sf::RenderWindow window;
    void window_initialize();

    sf::Event event;

    Hero *hero;
    void hero_initialize();

    Background *background;
    void background_initialize();

    std::vector<std::shared_ptr<Diamonds>> diam_vec;
    void diamonds_initialize();

    Totem *totem;
    void totem_initialize();

    std::vector<std::shared_ptr<Skeleton>> skel_vec;
    void skeletons_initialize();

    sf::Sprite sprite_win;
    sf::Texture texture_win;

    sf::Sprite sprite_defeat;
    sf::Texture texture_defeat;

    void texture_initialize();
    void sprite_initialize();

public:
    Game();
    virtual ~Game();

    const sf::RenderWindow& get_window() const;

    void update();
    void render();

    void update_hero();
    void update_diamonds();
    void update_totem();
    void update_skeletons();

    void render_hero();
    void render_background();
    void render_diamonds();
    void render_totem();
    void render_skeletons();
    void render_vicotry();
    void render_defeat();

    void end_game();
};

#endif // GAME_H
