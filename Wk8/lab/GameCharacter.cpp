#include <iostream>
using namespace std;
#include "GameCharacter.h"

namespace sict
{


	bool operator>(const GameCharacter& g, const GameCharacter& g2)
	{
		return g.energy() > g2.energy();
	}

	bool operator<(const GameCharacter& g, const GameCharacter& g2)
	{
		return g.energy() < g2.energy();
	}

	std::ostream& operator<<(std::ostream& os, const GameCharacter& g)
	{
		return g.display(os);
	}
}