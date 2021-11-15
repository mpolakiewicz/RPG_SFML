#include "Diamonds.h"


void Diamonds::texture_initialize()
{
    this->texture.loadFromFile("diamonds.png");
}

void Diamonds::sprite_initialize()
{
    this->sprite.setTexture(this->texture);
    this->animation_frame = sf::IntRect(0,11,32,77);
    this->sprite.setTextureRect(animation_frame);
    this->sprite.setPosition(rand() % 1888,rand() % 900);
    this->sprite.setScale(0.8, 0.8);
}

void Diamonds::animation_initialize()
{

}

void Diamonds::variables_initialize()
{
    up_down_move = 1.0;
}

Diamonds::Diamonds()
{
    this->texture_initialize();
    this->sprite_initialize();
    this->animation_initialize();
    this->variables_initialize();
}

Diamonds::~Diamonds()
{

}

void Diamonds::update()
{
    this->animation_update();
}

void Diamonds::animation_update()
{
    if(this->clock.getElapsedTime().asSeconds() >= 1.0)
    {
        up_down_move *= -1.0;
        clock.restart();
    }
    this->sprite.move(0.0, up_down_move * 0.1);
}

void Diamonds::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}

sf::FloatRect Diamonds::get_bounds()
{
    return this->sprite.getGlobalBounds();
}
