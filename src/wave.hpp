#ifndef WAVE
#define WAVE
#include "monster_list.hpp"

class wave{
	public:
		wave();
		void summon(int WINDOW_WIDTH,int WINDOW_HEIGHT, monster_list* esquerda, monster_list* direita);

		int speed_of_wave;
		int monsters_summoned;
		int monsters_in_wave;
		int dead_monsters;

		static int number_of_wave;
};
#endif