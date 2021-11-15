#include "Totem.h"

void Totem::texture_initialize()
{
    this->texture_totem.loadFromFile("totem.png");
    this->texture_treasure.loadFromFile("treasure.png");
}

void Totem::sprite_initialize()
{
    this->sprite.setTexture(this->texture_totem);
    this->sprite.setPosition(960.0, 30.0);
    this->sprite.setScale(0.5, 0.5);
}

void Totem::animation_initialize()
{

}

void Totem::variables_initialize()
{
    this->health = 5;
}

void Totem::hp_bar_initialize()
{
    this->hp_bar.setFillColor(sf::Color::Red);
    this->hp_bar.setSize(sf::Vector2f((float)this->health * 5.0, 10.0));
    this->hp_bar.setPosition(960.0, 10.0);
}

void Totem::sound_initialize()
{
    this->buffer_win.loadFromFile("Won!.wav");
    this->win.setBuffer(buffer_win);

}

Totem::Totem()
{
    this->texture_initialize();
    this->sprite_initialize();
    this->variables_initialize();
    this->animation_initialize();
    this->sound_initialize();
    this->hp_bar_initialize();
}

Totem::~Totem()
{

}

void Totem::update()
{
    this->animation_update();
    this->hp_bar_update();
}

void Totem::animation_update()
{
    if(this->health == 0)
    {
        this->sprite.setTexture(this->texture_treasure);
        this->sprite.setScale(1.4, 1.4);
    }
}

void Totem::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
    target.draw(this->hp_bar);
}

sf::FloatRect Totem::get_bounds()
{
    return this->sprite.getGlobalBounds();
}

int Totem::get_health()
{
    return this->health;
}

void Totem::check_health()
{
    if(this->health == 0)
        this->win.play();
}

void Totem::damage()
{
    this->health--;
}

void Totem::hp_bar_update()
{
    this->hp_bar.setSize(sf::Vector2f((float)this->health * 16.0, 10.0));
}
