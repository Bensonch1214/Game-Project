#ifndef OPERATIONCENTER_H_INCLUDED
#define OPERATIONCENTER_H_INCLUDED

/**
 * @brief Class that defines functions for all object operations.
 * @details Object self-update, draw, and object-to-object interact functions are defined here.
 */
class OperationCenter
{
public:
	static OperationCenter *get_instance()
	{
		static OperationCenter OC;
		return &OC;
	}
	/**
	 * @brief Highest level update function.
	 * @details Calls all other update functions.
	 */
	void update();
	/**
	 * @brief Highest level draw function.
	 * @details Calls all other draw functions.
	 */
	void draw();

private:
	OperationCenter() {}

private:
	void _update_monster();
	void _update_enemy();
	void _update_tower();
	void _update_towerBullet();
	void _update_enemyFire();
	void _update_heroLight();
	void _update_heroBomb();
	void _update_monster_towerBullet();
	void _update_monster_player();
	void _update_enemyFire_hero();
	void _update_enemy_hero();
	void _update_enemy_player();
	/*-----Revise start-----*/
	void _update_monster_hero();
	void _update_enemy_heroLight();
	/*-----Revise end-----*/
private:
	void _draw_monster();
	void _draw_enemy();
	void _draw_tower();
	void _draw_towerBullet();
	void _draw_enemyFire();
	void _draw_heroLight();
	void _draw_heroBomb();
};

#endif