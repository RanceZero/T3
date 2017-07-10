#ifndef CAT
#define CAT
#include <SFML/Graphics.hpp>
#include "global.hpp"

class cat{

	public:
		
		cat(int WINDOW_WIDTH, int WINDOW_HEIGHT);
				
		sf::Texture texture_Cat;
		sf::Texture texture_dead;
		sf::Sprite dead_sprite;
		sf::Sprite cat_sprite;
		bool punching_right,punching_left;
		int src;
		bool turned;
};
#endif
