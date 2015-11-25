#include <cstring>
#include <iostream>
using namespace std;
#include "Hero.h"
namespace sict
{
	Hero::Hero()
	{
		_name[0] = 0;
		_energy = 0;
	}

	Hero::Hero(const char name[], int strength)
	{
		strcpy(_name, name);
		_name[20] = 0;
		if (strength >= 0)
		{
			_energy = strength;
		}
	}

	bool Hero::isOut()const
	{
		return (!(_name[0] && _energy));
	}

	int Hero::energy()const
	{
		if (_energy >= 0)
		{
			return _energy;
		}
		else
		{
			return 0;
		}
		
	}

	int Hero::operator-=(int strength)
	{
		_energy -= strength;
		if (_energy < 0)
		{
			_energy = 0;
		}
		return _energy;
	}

	int Hero::operator+=(int strength)
	{
		_energy += strength;
		return _energy;
	}

	ostream& Hero::display(ostream& os)const
	{
		os << _name << "(" << _energy << ")";
		return os;
	}

}

