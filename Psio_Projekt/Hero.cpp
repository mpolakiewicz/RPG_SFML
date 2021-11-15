#include "Hero.h"

void Hero::hp_bar_initialize()
{
    this->hp_bar.setFillColor(sf::Color::Yellow);
    this->hp_bar.setSize(sf::Vector2f((float)this->health * 5.0, 5.0));
    this->hp_bar.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 10.0);
}

void Hero::texture_initialize()
{
    this->texture_run.loadFromFile("hero_run.png");
    this->texture_idle.loadFromFile("hero_idle.png");
    this->texture_dead.loadFromFile("hero_death.png");
    this->texture_attack.loadFromFile("hero_attack.png");
}

void Hero::sprite_initialize()
{
    this->sprite.setTexture(this->texture_idle);
    this->animation_frame_idle = sf::IntRect(21,10,29,38);
    this->animation_frame_run = sf::IntRect(38,12,32,35);
    this->animation_frame_death = sf::IntRect(36,10,30,36);
    this->animation_frame_end = sf::IntRect(1380,12,32,35);
    this->animation_frame_attack = sf::IntRect(41,10,80,36);
    this->sprite.setTextureRect(animation_frame_idle);
    this->sprite.setScale(2.0,2.0);
    this->sprite.setPosition(960.0, 950);
}

void Hero::variables_initialize()
{
    this->state = Movement_states::idle;
    this->health = 5;
    this->counter_death = 0;
    this->counter_attack = 0;
}

void Hero::sound_initialize()
{
    this->buffer_collect.loadFromFile("collect.wav");
    this->collect.setBuffer(buffer_collect);
    this->buffer_sword.loadFromFile("sword.flac");
    this->sword.setBuffer(buffer_sword);
    this->buffer_death.loadFromFile("hero_death.wav");
    this->death.setBuffer(buffer_death);
}

void Hero::animation_initialize()
{
    this->clock.restart();
}

Hero::Hero()
{
    this->texture_initialize();
    this->sprite_initialize();
    this->variables_initialize();
    this->animation_initialize();
    this->sound_initialize();
    this->hp_bar_initialize();
}

Hero::~Hero()
{

}

void Hero::update(std::vector<std::shared_ptr<Diamonds>> &diam_vec, sf::Event &event, Totem *totem, sf::RenderWindow &window)
{
    this->on_mouse_click(event);
    this->health_update();
    this->animation_update();
    this->move_update(window, totem);
    this->intersection_update(diam_vec, totem);
    this->hp_bar_update();

}

void Hero::move_update(sf::RenderWindow &window, Totem *totem)
{
        if(this->state != Movement_states::dead && this->state != Movement_states::attack && totem->get_health() != 0)
        {
            this->state = Movement_states::idle;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) //Left
            {
                if(this->sprite.getGlobalBounds().left >= 0)
                {
                    this->sprite.move(-1.0, 0.0);
                    this->state = Movement_states::left;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) //Right
            {
                if(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width <= window.getSize().x)
                {
                    this->sprite.move(1.0, 0.0);
                    this->state = Movement_states::right;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //Up
            {
                if(this->sprite.getGlobalBounds().top >= 0)
                {
                    this->sprite.move(0.0, -1.0);
                    this->state = Movement_states::up;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) //Down
            {
                if(this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height <= window.getSize().y)
                {
                    this->sprite.move(0.0, 1.0);
                    this->state = Movement_states::down;
                }
            }
        }
}

void Hero::animation_update()
{
    if(this->state == Movement_states::dead)
    {
        if(this->counter_death == 1)
        {
            this->death.play();
        }
        if(this->clock.getElapsedTime().asSeconds() >= 0.1)
        {
            if(this->counter_death != 15)
            {
                this->counter_death++;
            }
            this->sprite.setTexture(this->texture_dead);
            if(counter_death != 15)
            {
                this->animation_frame_death.left += 96;
            }
            if(this->animation_frame_death.left >= 1384)
                this->animation_frame_death.left = 36;
            this->sprite.setTextureRect(animation_frame_death);
            this->clock.restart();
        }

    }
    else
    {

        if(this->state == Movement_states::idle)
        {
            if(this->clock.getElapsedTime().asSeconds() >= 0.1)
            {
                this->sprite.setTexture(this->texture_idle);
                this->animation_frame_idle.left += 64;
                if(this->animation_frame_idle.left >= 918)
                    this->animation_frame_idle.left = 21;
                this->sprite.setTextureRect(animation_frame_idle);
                this->clock.restart();
            }
        }
        if(this->state == Movement_states::left)
        {
            if(this->clock.getElapsedTime().asSeconds() >= 0.1)
            {
                this->sprite.setTexture(this->texture_run);
                this->animation_frame_run.left += 96;
                if(this->animation_frame_run.left >= 709)
                    this->animation_frame_run.left = 38;
                this->sprite.setTextureRect(animation_frame_run);

                this->sprite.setOrigin(32.0, 0.0);
                this->sprite.setScale( -2.0, 2.0 );

                this->clock.restart();
            }
        }
        if(this->state == Movement_states::right)
        {
            if(this->clock.getElapsedTime().asSeconds() >= 0.1)
            {
                this->sprite.setTexture(this->texture_run);
                this->animation_frame_run.left += 96;
                if(this->animation_frame_run.left >= 709)
                    this->animation_frame_run.left = 38;
                this->sprite.setTextureRect(animation_frame_run);

                this->sprite.setOrigin(0.0, 0.0);
                this->sprite.setScale( 2.0, 2.0 );

                this->clock.restart();
            }
        }
        if(this->state == Movement_states::up)
        {
            if(this->clock.getElapsedTime().asSeconds() >= 0.1)
            {
                this->sprite.setTexture(this->texture_run);
                this->animation_frame_run.left += 96;
                if(this->animation_frame_run.left >= 709)
                    this->animation_frame_run.left = 38;
                this->sprite.setTextureRect(animation_frame_run);
                this->clock.restart();
            }
        }
        if(this->state == Movement_states::down)
        {
            if(this->clock.getElapsedTime().asSeconds() >= 0.1)
            {
                this->sprite.setTexture(this->texture_run);
                this->animation_frame_run.left += 96;
                if(this->animation_frame_run.left >= 709)
                    this->animation_frame_run.left = 38;
                this->sprite.setTextureRect(animation_frame_run);
                this->clock.restart();
            }
        }
        if(this->state == Movement_states::attack)
        {

            if(this->counter_attack == 23)
            {
                this->state = Movement_states::idle;
                this->counter_attack = 0;
            }
            if(this->counter_attack == 1)
            {
                this->sword.play();
            }
            if(this->clock.getElapsedTime().asSeconds() >= 0.03)
            {
                if(this->counter_attack != 23)
                {
                    this->counter_attack++;
                }
                this->sprite.setTexture(this->texture_attack);
                if(counter_attack != 23)
                {
                    this->animation_frame_attack.left += 144;
                }
                if(this->animation_frame_attack.left >= 3092)
                    this->animation_frame_attack.left = 41;
                this->sprite.setTextureRect(animation_frame_attack);
                this->clock.restart();
            }
        }
    }
}

void Hero::intersection_update(std::vector<std::shared_ptr<Diamonds>> &diam_vec, Totem *totem)
{
    for(size_t i = 0; i < diam_vec.size(); i++)
    {
        if(this->sprite.getGlobalBounds().intersects(diam_vec[i]->get_bounds()))
        {
            if(this->health < 5)
            {
                this->health++;
            }
            diam_vec.erase(diam_vec.begin()+i);
            this->collect.play();
        }
    }

    if(this->sprite.getGlobalBounds().intersects(totem->get_bounds()) && this->counter_attack == 23)
    {
        totem->damage();
        totem->check_health();
    }
}

void Hero::health_update()
{
    if(this->health == 0)
    {
        this->state = Movement_states::dead;
    }
}

void Hero::hp_bar_update()
{
    this->hp_bar.setSize(sf::Vector2f((float)this->health * 10.0, 5.0));
    this->hp_bar.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 10.0);
}

void Hero::on_mouse_click(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
          if(event.mouseButton.button == sf::Mouse::Left)
          {
                this->state = Movement_states::attack;

          }
    }
}

void Hero::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
    target.draw(this->hp_bar);
}

sf::FloatRect Hero::get_bounds()
{
    return this->sprite.getGlobalBounds();
}

int Hero::get_counter_attack()
{
    return this->counter_attack;
}

int Hero::get_counter_death()
{
    return this->counter_death;
}

Movement_states Hero::get_state()
{
    return this->state;
}

void Hero::damage()
{
    if(this->health > 0)
        this->health--;
}
