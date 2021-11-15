#include "Skeleton.h"
#include "Totem.h"


void Skeleton::texture_initialize()
{
    this->texture_walk.loadFromFile("skeleton_walk.png");
    this->texture_idle.loadFromFile("skeleton_idle.png");
    this->texture_dead.loadFromFile("skeleton_death.png");
    this->texture_attack.loadFromFile("skeleton_attack.png");
}

void Skeleton::sprite_initialize()
{
    this->sprite.setTexture(this->texture_idle);
    this->animation_frame_idle = sf::IntRect(0,0,24,32);
    this->animation_frame_walk = sf::IntRect(0,0,22,33);
    this->animation_frame_death = sf::IntRect(0,0,33,32);
    this->animation_frame_attack = sf::IntRect(0,0,43,37);
    this->sprite.setTextureRect(animation_frame_idle);
    this->sprite.setPosition(rand() % 1888,rand() % 850);
    this->sprite.setScale(2.0,2.0);
}

void Skeleton::animation_initialize()
{
    this->clock1.restart();
    this->clock2.restart();
}

void Skeleton::variables_initialize()
{
    this->state = Movement_states::idle;
    this->health = 1;
    this->counter_death = 0;
    this->counter_attack = 0;
}

void Skeleton::sound_initialize()
{
    this->buffer_skeleton_attack.loadFromFile("skeleton_attack.wav");
    this->skeleton_attack.setBuffer(buffer_skeleton_attack);
    this->buffer_skeleton_death.loadFromFile("skeleton_death.wav");
    this->skeleton_death.setBuffer(buffer_skeleton_death);
}

Skeleton::Skeleton()
{
    this->texture_initialize();
    this->sprite_initialize();
    this->variables_initialize();
    this->animation_initialize();
    this->sound_initialize();
}

Skeleton::~Skeleton()
{

}

void Skeleton::update(Hero *hero, Totem *totem)
{
    this->intersection_update(hero, totem);
    this->health_update();
    this->move_update(hero);
    this->animation_update(hero);
}

void Skeleton::move_update(Hero *hero)
{
    if(this->state != Movement_states::dead && this->state != Movement_states::attack)
    {
        this->state = Movement_states::idle;
        //Left
        if((hero->get_bounds().left + hero->get_bounds().width/2) < this->sprite.getGlobalBounds().left)
        {
            this->sprite.move(-0.2, 0.0);
            this->state = Movement_states::left;
        }
        //Right
        if((hero->get_bounds().left + hero->get_bounds().width/2) > this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width)
        {
            this->sprite.move(0.2, 0.0);
            this->state = Movement_states::right;
        }
        //Up
        if((hero->get_bounds().top + hero->get_bounds().height/2) < this->sprite.getGlobalBounds().top)
        {
            this->sprite.move(0.0, -0.2);
            this->state = Movement_states::up;
        }
        //Down
        if((hero->get_bounds().top + hero->get_bounds().height/2) > this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height)
        {
            this->sprite.move(0.0, 0.2);
            this->state = Movement_states::down;
        }
    }
}

void Skeleton::animation_update(Hero *hero)
{
    if(this->state == Movement_states::dead)
    {
        if(this->clock1.getElapsedTime().asSeconds() >= 0.1)
        {
            if(this->counter_death != 14)
            {
                this->counter_death++;
            }
            this->sprite.setTexture(this->texture_dead);
            if(counter_death != 14)
            {
                this->animation_frame_death.left += 33;
            }
            if(this->animation_frame_death.left >= 462)
                this->animation_frame_death.left = 0;
            this->sprite.setTextureRect(animation_frame_death);
            this->clock1.restart();
        }

    }
    else
    {

        if(this->state == Movement_states::idle)
        {
            if(this->clock1.getElapsedTime().asSeconds() >= 0.1)
            {
                this->sprite.setTexture(this->texture_idle);
                this->animation_frame_idle.left += 24;
                if(this->animation_frame_idle.left >= 240)
                    this->animation_frame_idle.left = 0;
                this->sprite.setTextureRect(animation_frame_idle);
                this->clock1.restart();
            }
        }
        if(this->state == Movement_states::left)
        {
            if(this->clock1.getElapsedTime().asSeconds() >= 0.1)
            {
                this->sprite.setTexture(this->texture_walk);
                this->animation_frame_walk.left += 22;
                if(this->animation_frame_walk.left >= 253)
                    this->animation_frame_walk.left = 0;
                this->sprite.setTextureRect(animation_frame_walk);

                this->sprite.setOrigin(32.0, 0.0);
                this->sprite.setScale( -2.0, 2.0 );

                this->clock1.restart();
            }
        }
        if(this->state == Movement_states::right)
        {
            if(this->clock1.getElapsedTime().asSeconds() >= 0.1)
            {
                this->sprite.setTexture(this->texture_walk);
                this->animation_frame_walk.left += 22;
                if(this->animation_frame_walk.left >= 253)
                    this->animation_frame_walk.left = 0;
                this->sprite.setTextureRect(animation_frame_walk);

                this->sprite.setOrigin(0.0, 0.0);
                this->sprite.setScale( 2.0, 2.0 );

                this->clock1.restart();
            }
        }
        if(this->state == Movement_states::up)
        {
            if(this->clock1.getElapsedTime().asSeconds() >= 0.1)
            {
                this->sprite.setTexture(this->texture_walk);
                this->animation_frame_walk.left += 22;
                if(this->animation_frame_walk.left >= 253)
                    this->animation_frame_walk.left = 0;
                this->sprite.setTextureRect(animation_frame_walk);
                this->clock1.restart();
            }
        }
        if(this->state == Movement_states::down)
        {
            if(this->clock1.getElapsedTime().asSeconds() >= 0.1)
            {
                this->sprite.setTexture(this->texture_walk);
                this->animation_frame_walk.left += 22;
                if(this->animation_frame_walk.left >= 253)
                    this->animation_frame_walk.left = 0;
                this->sprite.setTextureRect(animation_frame_walk);
                this->clock1.restart();
            }
        }
        if(this->state == Movement_states::attack)
        {

            if(this->counter_attack == 18)
            {
                this->state = Movement_states::idle;
                this->counter_attack = 0;
                hero->damage();
            }
            if(this->counter_attack == 1)
            {
                this->skeleton_attack.play();

            }
            if(this->clock1.getElapsedTime().asSeconds() >= 0.03)
            {
                if(this->counter_attack != 18)
                {
                    this->counter_attack++;
                }
                this->sprite.setTexture(this->texture_attack);
                if(counter_attack != 18)
                {
                    this->animation_frame_attack.left += 43;
                }
                if(this->animation_frame_attack.left >= 731)
                    this->animation_frame_attack.left = 0;
                this->sprite.setTextureRect(animation_frame_attack);
                this->clock1.restart();
            }
        }
    }
}

void Skeleton::intersection_update(Hero *hero, Totem *totem)
{
    if(this->get_bounds().intersects(hero->get_bounds()) && hero->get_state() != Movement_states::dead && totem->get_health() != 0)
    {
        this->state = Movement_states::attack;
        if(hero->get_state() == Movement_states::attack)
        {
            this->damage();
        }
    }
    else if(this->get_bounds().intersects(hero->get_bounds()) && hero->get_state() == Movement_states::dead)
    {
        this->state = Movement_states::idle;
    }
}

void Skeleton::health_update()
{
        if(this->health <= 0)
        {
            this->state = Movement_states::dead;
        }
}

void Skeleton::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}

sf::FloatRect Skeleton::get_bounds()
{
    return this->sprite.getGlobalBounds();
}

void Skeleton::damage()
{
    this->health = 0;
}

Movement_states Skeleton::get_state()
{
    return this->state;
}

int Skeleton::get_counter_death()
{
    return this->counter_death;
}

