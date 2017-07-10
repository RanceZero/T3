#ifndef MONSTER
#define MONSTER
#include <SFML/Graphics.hpp>
#include "global.hpp"
class monster{

	public:
		monster(int dir, int WINDOW_WIDTH, int WINDOW_HEIGHT, int given_speed);
			
		
		sf::Sprite monster_sprite;
		int walking_dir;
		int src;
		static sf::Texture *texture_Monster;
		int speed;

};
#endif