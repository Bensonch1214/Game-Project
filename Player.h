#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player
{
public:
	Player();
	void update();
	double HP;
	double full_HP;
	int coin;
	int score;
	bool super;
private:
	int coin_freq;
	int coin_increase;
	int coin_counter;
};

#endif
