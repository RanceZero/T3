#ifndef NODE
#define NODE
#include "monster.hpp"

class node{
	public:
		node(){};

		monster* info;
		node *next;
};
#endif