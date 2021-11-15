#include "Background.h"


void Background::texture_initialize()
{
    this->texture.loadFromFile("grass1.png");
    this->texture.setRepeated(true);
}

void Background::sprite_initialize()
{
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(0,0,1920, 1080));
    this->sprite.setScale(1.0,1.0);
}

Background::Background()
{
    this->texture_initialize();
    this->sprite_initialize();
}

Background::~Background()
{

}

void Background::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}
