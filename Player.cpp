#include "Player.h"
#include "data/DataCenter.h"
// fixed settings
namespace PlayerSetting {
	constexpr double init_HP = 1000;
	constexpr int init_coin = 100;
	constexpr int coin_freq = 60;
	constexpr int coin_increase = 5;
};

Player::Player() : HP(PlayerSetting::init_HP), coin(PlayerSetting::init_coin),full_HP(PlayerSetting::init_HP) {
	this->coin_freq = PlayerSetting::coin_freq;
	this->coin_increase = PlayerSetting::coin_increase;
	coin_counter = PlayerSetting::coin_freq;
	score = 0;
	super = false;
}

void
Player::update() {
	if(coin_counter) --coin_counter;
	else {
		coin += coin_increase;
		coin_counter = coin_freq;
	}
    DataCenter *DC = DataCenter::get_instance();
	
	if(DC->key_state[ALLEGRO_KEY_S] && !DC->player->super) DC->player->super = true;
	else if(DC->key_state[ALLEGRO_KEY_W] && DC->player->super) DC->player->super = false;
}
