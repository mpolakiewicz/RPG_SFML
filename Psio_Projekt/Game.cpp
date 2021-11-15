#include "Game.h"

void Game::window_initialize()
{
    this->window.create(sf::VideoMode(1920, 1080), "2D Game", sf::Style::Close | sf::Style::Titlebar);
    this->window.setFramerateLimit(144);
}

void Game::hero_initialize()
{
    this->hero = new Hero();
}

void Game::background_initialize()
{
    this->background = new Background();
}

void Game::diamonds_initialize()
{
    for(int i = 0; i < 7; i++)
    {
        diam_vec.emplace_back(std::make_shared<Diamonds>());
    }
}

void Game::totem_initialize()
{
    this->totem = new Totem();
}

void Game::skeletons_initialize()
{
    for(int i = 0; i < 15; i++)
    {
        skel_vec.emplace_back(std::make_shared<Skeleton>());
    }
}

void Game::texture_initialize()
{
    this->texture_win.loadFromFile("victory.png");
    this->texture_defeat.loadFromFile("game_over.png");
}

void Game::sprite_initialize()
{
    this->sprite_win.setTexture(this->texture_win);
    this->sprite_win.setScale(0.3, 0.3);
    this->sprite_win.setPosition(800.0, 360.0);

    this->sprite_defeat.setTexture(this->texture_defeat);
    this->sprite_defeat.setScale(1.0,1.0);
    this->sprite_defeat.setPosition(this->window.getSize().x/2 - this->sprite_defeat.getGlobalBounds().width/2, this->window.getSize().y/2 - this->sprite_defeat.getGlobalBounds().height/2);
}


Game::Game()
{
    this->window_initialize();
    this->background_initialize();
    this->hero_initialize();
    this->diamonds_initialize();
    this->totem_initialize();
    this->skeletons_initialize();
    this->texture_initialize();
    this->sprite_initialize();
}

Game::~Game()
{
    delete this->hero;
}

const sf::RenderWindow &Game::get_window() const
{
    return this->window;
}

void Game::update()
{
    while (this->window.pollEvent(this->event))
        {
            if (this->event.type == sf::Event::Closed)
                this->window.close();
            if (this->event.type == sf::Event::KeyPressed)
            {
                if(this->event.key.code == sf::Keyboard::Escape)
                this->window.close();
            }
        }
    this->update_hero();
    this->update_diamonds();
    this->update_totem();
    this->update_skeletons();
}

void Game::render()
{
    this->window.clear();

    this->render_background();
    this->render_diamonds();
    this->render_totem();
    this->render_hero();
    this->render_skeletons();
    this->end_game();

    this->window.display();
}

void Game::update_hero()
{
    this->hero->update(this->diam_vec, this->event, this->totem, this->window);
}

void Game::update_diamonds()
{
    for(size_t i = 0; i < diam_vec.size(); i++)
    {
        this->diam_vec[i]->update();
    }
}

void Game::update_totem()
{
    this->totem->update();
}

void Game::update_skeletons()
{
    for(size_t i = 0; i < skel_vec.size(); i++)
    {
        if(skel_vec[i]->get_state() == Movement_states::dead && skel_vec[i]->get_counter_death() == 14)
        {
            skel_vec.erase(skel_vec.begin() + i);
            skel_vec.emplace_back(std::make_shared<Skeleton>());
        }
        this->skel_vec[i]->update(hero, totem);
    }
}

void Game::render_hero()
{
    this->hero->render(this->window);
}

void Game::render_background()
{
    this->background->render(this->window);
}

void Game::render_diamonds()
{
    for(size_t i = 0; i < diam_vec.size(); i++)
    {
        this->diam_vec[i]->render(this->window);
    }
}

void Game::render_totem()
{
    this->totem->render(this->window);
}

void Game::render_skeletons()
{
    for(size_t i = 0; i < skel_vec.size(); i++)
    {
        this->skel_vec[i]->render(this->window);
    }
}

void Game::render_vicotry()
{
    this->window.draw(this->sprite_win);
}

void Game::render_defeat()
{
    this->window.draw(this->sprite_defeat);
}

void Game::end_game()
{
    if(this->hero->get_counter_death() == 15)
    {
       this->render_defeat();
    }
    if(this->totem->get_health() == 0)
    {
        this->render_vicotry();
    }
}
