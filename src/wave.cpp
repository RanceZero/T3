#include "wave.hpp"
#include "global.hpp"
#include <math.h>
#include <stdlib.h>

int wave::number_of_wave = 0;

wave::wave(){
	number_of_wave++;
	speed_of_wave = number_of_wave;
	const double euler = exp(1.0);
	monsters_in_wave = 10+pow(number_of_wave,euler/1.5);
	monsters_summoned = 0;
	dead_monsters=0;
}

void wave::summon(int WINDOW_WIDTH, int WINDOW_HEIGHT, monster_list* esquerda, monster_list* direita){
	
	int x = rand()%2;
	monster *monstro = new monster(x, WINDOW_WIDTH , WINDOW_HEIGHT, speed_of_wave);
	if(x==RIGHT){
		esquerda->adiciona_monstro(monstro);
	}
	else{ // andando pra esquerda
		direita->adiciona_monstro(monstro);
	}
	monsters_summoned++;    
}