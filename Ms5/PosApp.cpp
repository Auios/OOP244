#include <cstring>
#include <iomanip>
#include "PosApp.h"
#include <math.h>

using namespace std;

namespace sict
{
	PosApp::PosApp(const char* filename, const char* billfname)
	{
		int i = 0;

		strcpy(_filename, filename);
		strcpy(_billfname, billfname);

		for (i = 0; i < MAX_NO_ITEMS; i++)
		{
			_items[i] = 0;
		}

		loadRecs();
	}

	int PosApp::menu()
	{
		int sel = -1;

		cout
			<< "The OOPs Store" << endl
			<< "1- List items" << endl
			<< "2- Add Perishable item" << endl
			<< "3- Add Non-Perishable item" << endl
			<< "4- Update item quantity" << endl
			<< "5- Show Item" << endl
			<< "6- POS" << endl
			<< "0- exit program" << endl
			<< "> ";

		cin >> sel;
		if (cin.fail())
		{
			cin.clear();
			sel = -1;
		}
		if (sel < 0 || sel > 6)
		{
			sel = -1;
		}

		cin.ignore(1000, '\n');

		return sel;
	}

	void PosApp::loadRecs()
	{
		fstream data(_filename);
		char chk;
		int i;

		if(!data.fail())
		{
			for(i = 0; i < _noOfItems; i++)
			{
				delete _items[i];
				_items[i] = 0;
			}

			i = 0;

			do
			{
				data.get(chk);

				if(chk != '\n')
				{
					if(chk == 'P')
					{
						_items[i] = new Perishable();
					}
					else if(chk == 'N')
					{
						_items[i] = new NonPerishable();
					}

					if(_items[i])
					{
						data.get();
						_items[i]->load(data);
						if(_items[i]->name()[0] != '\0')
						{
							i++;
						}
						else
						{
							delete _items[i];
						}

						_noOfItems = i;
					}
				}
			}
			while(i < MAX_NO_ITEMS && !data.eof());
		}
		else
		{
			data.close();
			data.open(_filename,fstream::out);
		}

		data.close();
	}

	void PosApp::saveRecs()
	{
		fstream data(_filename, ios::out);
		int i = 0;

		for (i = 0; i < _noOfItems; i++)
		{
			if (_items[i]->quantity() > 0)
			{
				_items[i]->save(data);
			}
		}

		data.close();
		loadRecs();
	}

	int PosApp::searchItems(const char* sku)const
	{
		int i = 0;
		int match = -1;

		while (i < _noOfItems && match != i)
		{
			if (*_items[i] == sku)
			{
				match = i;
			}
			i++;
		}

		return match;
	}

	void PosApp::updateQty()
	{
		int qty;
		int match;
		char sku[MAX_SKU_LEN + 1];

		cout
			<< endl
			<< "Please enter the SKU: ";
		cin >> sku;

		match = searchItems(sku);
		
		if (match == -1)
		{
			cout << "Not found!" << endl;
		}
		else
		{
			_items[match]->write(cout, false);
			cout << endl
				<< "Please enter the number of purchased items: ";
			cin >> qty;
			
			if (cin.fail())
			{
				cout << "Invalid Quantity value!" << endl;
			}
			else
			{
				*_items[match] += qty;
			}

			saveRecs();

			cout << "Updated!" << endl;
			cin.ignore(1000, '\n');
		}

		cout << endl;
	}

	void PosApp::addItem(bool isPerishable)
	{
		if (isPerishable)
		{
			_items[_noOfItems] = new Perishable();
		}
		else
		{
			_items[_noOfItems] = new NonPerishable();
		}

		cin >> *_items[_noOfItems];

		if (cin.fail())
		{
			_items[_noOfItems]->write(cout, true);
			cout << endl << endl;
			delete _items[_noOfItems];
		}
		else
		{
			cout << "Item added." << endl << endl;
			_noOfItems++;
			saveRecs();
		}
	}

	void PosApp::listItems()const
	{
		double total = 0;
		int i = 0;

		cout
			<< endl
			//<< ">Start"//<< endl
			<< " Row | SKU    | Item Name          | Price |TX |Qty |   Total |" << endl
			<< "-----|--------|--------------------|-------|---|----|---------|" << endl;
		
		//cout << _noOfItems << endl;

		for (i = 0; i < _noOfItems; i++)
		{
			cout
				<< setfill(' ') << setw(4) << right << i + 1 << " | " << *_items[i] << endl;

			total += ceil(100 * (_items[i]->cost() * _items[i]->quantity())) / 100;
		}

		cout
			<< "-----^--------^--------------------^-------^---^----^---------^" << endl
			<< "Total Asset: $" << fixed << setprecision(2) << (total-0.01) << endl << endl;
	}

	void PosApp::showBill()
	{
		double total = 0;
		char chk;
		Date date;
		fstream data;
		Item* items = 0;

		data.open(_billfname, ios::in);
		cout
			<< "v--------------------------------------------------------v" << endl
			<< "| " << date << setw(39) << setfill(' ') << "|" << endl
			<< "| SKU    | Item Name          | Price |TX |Qty |   Total |" << endl
			<< "|--------|--------------------|-------|---|----|---------|" << endl;

		do
		{
			data.get(chk);
			data.get();

			if(chk == 'P' || chk == 'N')
			{
				if(chk == 'P')
				{
					items = new Perishable();
				}
				else
				{
					items = new NonPerishable();
				}

				chk = '\0';

				if(items)
				{
					items->load(data);
					cout << "|";
					items->write(cout, true);
					cout << endl;
					total += *items;

					delete items;
				}
			}
		}
		while(!data.eof());

		data.clear();
		data.close();
		data.open(_billfname, ios::out | ios::trunc);
		data.close();

		cout
			<< "^--------^--------------------^-------^---^----^---------^" << endl
			<< "Total: $" << fixed << setprecision(2) << (total-0.01) << endl << endl;
	}

	void PosApp::addToBill(Item& I)
	{
		fstream data(_billfname, ios::out | ios::app);
		int tmpQty = I.quantity();
		
		I.quantity(1);
		I.save(data);

		if (tmpQty > 0)
		{
			tmpQty--;
		}

		I.quantity(tmpQty);

		saveRecs();
	}

	void PosApp::POS()
	{
		bool done = true;
		char input[MAX_SKU_LEN + 1];
		int match;

		cout << endl;

		while (done)
		{
			cout << "Sku: ";
			cin.getline(input, MAX_SKU_LEN);

			match = searchItems(input);

			if (input[0] == 0)
			{
				done = false;
			}
			else
			{
				if (match != -1)
				{
					cout
						<< "v------------------->" << endl
						<< "| " << _items[match]->name() << endl
						<< "^------------------->" << endl;

					addToBill(*_items[match]);
				}
				else
				{
					cout << "Not found!" << endl;
				}
			}
		}
		showBill();
	}

	void PosApp::run()
	{
		int sel;
		int match;
		char sku[MAX_SKU_LEN + 1];

		do
		{
			sel = menu();

			switch (sel)
			{
			case 0:
				cout << endl << "Goodbye!!" << endl;
				break;

			case 1:
				listItems();
				break;

			case 2:
				addItem(true);
				break;

			case 3:
				addItem(false);
				break;

			case 4:
				updateQty();
				break;

			case 5:
				cout << endl
					<< "Please enter the SKU: ";
				cin >> sku;
				
				cout << "v-----------------------------------v";

				match = searchItems(sku);

				
				if (match != -1)
				{
					cout << endl;
					_items[match]->write(cout, false);
				}
				else
				{
					cout << "Not found!";
				}

				cout << "^-----------------------------------^" << endl << endl;
				break;

			case 6:
				POS();
				break;

			default:
				cout << endl << "===Invalid Selection, try again===" << endl;
				break;

			}
		}
		while (sel != 0);
	}
}
