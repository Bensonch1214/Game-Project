#include "Hero.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Rectangle.h"
#include <stdio.h>
namespace HeroSetting
{
    static constexpr char gif_root_path[50] = "./assets/gif/Hero";
    static constexpr char gif_postfix[][10] = {
        "left",
        "right",
        "front",
        "back",
    };
}

void Hero::init()
{
    for (size_t type = 0; type < static_cast<size_t>(HeroState::HEROSTATE_MAX); ++type)
    {
        char buffer[50];
        sprintf(
            buffer, "%s/dragonite_%s.gif",
            HeroSetting::gif_root_path,
            HeroSetting::gif_postfix[static_cast<int>(type)]);
        gifPath[static_cast<HeroState>(type)] = std::string{buffer};
    }
    DataCenter *DC = DataCenter::get_instance();
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
    width = gif->width;
    height = gif->height;
    shape.reset(new Rectangle{DC->window_width / 2,
                              DC->window_height / 2,
                              DC->window_width / 2 + width,
                              DC->window_height / 2 + height});
}

void Hero::update()
{
    DataCenter *DC = DataCenter::get_instance();
    if(DC->mouse.x <= DC->game_field_length-width/2) shape->update_center_x(DC->mouse.x);
    shape->update_center_y(DC->mouse.y);
    if (DC->key_state[ALLEGRO_KEY_UP]){
        DC->heroLights.emplace_back(create_light(ALLEGRO_KEY_UP, 0, 0, -500));
    }
    if (DC->key_state[ALLEGRO_KEY_DOWN]){
        DC->heroBombs.emplace_back(create_bomb());
    }
    if(DC->key_state[ALLEGRO_KEY_LEFT]) {
        DC->heroLights.emplace_back(create_light(ALLEGRO_KEY_LEFT, PI, 200, -300));
    }
    if(DC->key_state[ALLEGRO_KEY_RIGHT]) {
        DC->heroLights.emplace_back(create_light(ALLEGRO_KEY_RIGHT, 0, 200, -300));
    }
    // if (DC->key_state[ALLEGRO_KEY_W])
    // {
    //     shape->update_center_y(shape->center_y() - speed);
    //     state = HeroState::BACK;
    // }
    // else if (DC->key_state[ALLEGRO_KEY_A])
    // {
    //     shape->update_center_x(shape->center_x() - speed);
    //     state = HeroState::LEFT;
    // }
    // else if (DC->key_state[ALLEGRO_KEY_S])
    // {
    //     shape->update_center_y(shape->center_y() + speed);
    //     state = HeroState::FRONT;
    // }
    // else if (DC->key_state[ALLEGRO_KEY_D])
    // {
    //     shape->update_center_x(shape->center_x() + speed);
    //     state = HeroState::RIGHT;
    // }
}
void Hero::draw()
{
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
    algif_draw_gif(gif,
                   shape->center_x() - width / 2,
                   shape->center_y() - height / 2,
                   0);
}