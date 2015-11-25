#ifndef SICT_GAMECHARACTER_H__
#define SICT_GAMECHARACTER_H__
#include <iostream>
namespace sict{
class GameCharacter
	{

	public:
		virtual bool isOut()const = 0;
		virtual int energy()const = 0;

		virtual int operator+=(int strength) = 0;
		virtual int operator-=(int strength) = 0;
	  

		virtual std::ostream& display(std::ostream& os)const = 0;
	};
	std::ostream& operator<<(std::ostream&, const GameCharacter&);
	bool operator>(const GameCharacter& g, const GameCharacter& g2);
	bool operator<(const GameCharacter& g, const GameCharacter& g2);
}

#endif