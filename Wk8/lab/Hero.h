#include <iostream>
#include "GameCharacter.h"

namespace sict
{
	class Hero: public GameCharacter
	{
	protected:		
		int _energy;
		char _name[21];
	public:
		Hero();
		Hero(const char name[], int strength);

		bool isOut()const;
		int energy()const;

		int operator-=(int strength);
		int operator+=(int strength);

		std::ostream& display(std::ostream& os)const;

	};

}

