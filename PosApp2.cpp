#include <cstring>
#include <iomanip>
#include "PosApp.h"
using namespace std;
namespace sict{
	PosApp::PosApp(const char* filename, const char* billfname): _noOfItems(0){
		std::strcpy(_filename, filename);
		std::strcpy(_billfname, billfname);
		for (int i = 0; i < MAX_NO_ITEMS; i++)
			_items[i] = nullptr;		
	}
	int PosApp::menu(){
		int selection;
		std::cout << "\nThe OOPs Store" << std::endl;
		std::cout << "1- List items" << std::endl;
		std::cout << "2- Add Perishable item" << std::endl;
		std::cout << "3- Add Non-Perishable item" << std::endl;
		std::cout << "4- Update item quantity" << std::endl;
		std::cout << "5- Show Item" << std::endl;
		std::cout << "6- POS" << std::endl;
		std::cout << "0- exit program" << std::endl;
		std::cout << "> ";
		std::cin >> selection;
		if (std::cin.fail()){
			std::cin.clear();
			selection = -1;
		}
		if (selection != 0 && selection != 2 && selection != 3 && selection != 4 && selection != 1 && selection != 5)
			selection = -1;
		std::cin.ignore(2000, '\n');

		return selection;
	}

	void PosApp::loadRecs(){
		char check;
		fstream datafile;
		datafile.open(_filename, ios::in);
		if (!datafile.bad()){
			for (int i = 0; i < _noOfItems; i++){
				delete _items[i];
				_items[i] = nullptr;
			}
			for (int i = 0; i < MAX_NO_ITEMS && !datafile.eof(); i++){
				datafile.get(check);
				datafile.get();
				if (check == 'P')
					_items[i] = new Perishable();
				else if (check == 'N')
					
					_items[i] = new NonPerishable();

				if (check == 'P' || check == 'N'){
					(*_items[i]).load(datafile);
					_noOfItems = i;
				}
			}
		}
		else{
			datafile.clear();
			datafile.close();
			datafile.open(_filename, ios::out);
		}
		datafile.close();
	}
	void PosApp::saveRecs(){
		fstream datafile(_filename, ios::out);

		for (int i = 0; i < _noOfItems; i++){
			if (_items[i]->quantity() > 0)
				_items[i]->save(datafile);
		}
		datafile.close();
		loadRecs();
	}

	int PosApp::searchItems(const char* sku)const{
		int match = -1, i = 0;
		while (i < _noOfItems && match != i){
			if (*_items[i] == sku)
				match = i;
			i++;
		}
		return match;
	}

	void PosApp::updateQty(){
		int match, q;
		char sku[MAX_SKU_LEN + 1];
		std::cout << ">Start \nPlease enter the SKU: ";
		std::cin >> sku;
		match = searchItems(sku);
		if (match == -1)
			std::cout << "Not found!" << std::endl;
		else{
			_items[match]->write(std::cout, false);
			std::cout << "\nPlease enter the number of purchased items: ";
			std::cin >> q;
			if (std::cin.fail())
				std::cout << "Invalid Quantity value!" << std::endl;
			else
				*_items[match] += q;
			saveRecs();
			std::cout << "Updated!" << std::endl;
			std::cin.ignore(2000, '\n');
		}
		std::cout << "\n>END";
	}
	void PosApp::addItem(bool isPerishable){
		if (isPerishable)
			_items[_noOfItems] = new Perishable();
		else
			_items[_noOfItems] = new NonPerishable();

		std::cin >> *_items[_noOfItems];
		if (std::cin.fail()){
			_items[_noOfItems]->write(std::cout, true);
			std::cout << "\n" << std::endl;
			delete _items[_noOfItems];
		}
		else{
			std::cout << "Item added\n" << std::endl;
			_noOfItems++;
			saveRecs();
		}
		std::cout << "\n>END";
	}
	void PosApp::listItems()const{
		double total = 0.0;
		std::cout << "\n>Start" << std::endl;
		std::cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total |" << std::endl;
		std::cout << "-----|--------|--------------------|-------|---|----|---------|" << std::endl;
		for (int i = 0; i < _noOfItems; i++){
			std::cout << std::setfill(' ') << std::setw(4) << std::right << i + 1 << " | ";
			std::cout << *_items[i] << std::endl;

			total += *_items[i];
		}
		std::cout << "-----^--------^--------------------^-------^---^----^---------^" << std::endl;
		std::cout << "Total Asset: $" << std::fixed << std::setprecision(2) << total << std::endl << std::endl;
	}

	void PosApp::showBill(){
		char check;
		double total = 0.0;
		Date d;
		std::fstream datafile;
		Item* items = nullptr;
		datafile.open(_billfname, std::ios::in);
		std::cout << ">Start" << std::endl;
		std::cout << "v--------------------------------------------------------v" << std::endl;
		std::cout << "| " << d << setw(38) << "|"<< std::endl;
		std::cout << "| SKU    | Item Name          | Price |TX |Qty |   Total |" << std::endl;
		std::cout << "|--------|--------------------|-------|---|----|---------|" << std::endl;
		while (datafile){
			datafile.get(check);
			datafile.get();
			if (check == 'P')
				items = new Perishable();
			else if (check == 'N')
				
				items = new NonPerishable();

			if (check == 'P' || check == 'N'){
				items->load(datafile);
				items->write(std::cout, true);
				total += *items;
				delete items;
				std::cout << "^--------^--------------------^-------^---^----^---------^" << std::endl;
				std::cout << "Total: $" << std::fixed << std::setprecision(2) << total << std::endl << std::endl;
			}
		}
		std::cout << ">END" << std::endl;
		datafile.clear();
		datafile.close();
		datafile.open(_billfname, ios::out|ios::trunc);
		datafile.close();

	}
	void PosApp::addToBill(Item& I){
		int qty = I.quantity();
		I.quantity(1);
		fstream datafile(_billfname, ios::out | ios::app);
		I.save(datafile);
		if (qty > 0)
			qty--;
		I.quantity(qty);
		saveRecs();

	}
	void PosApp::POS(){
		bool done = true;
		char input[MAX_SKU_LEN+1];
		int match;
		std::cout << ">START" << std::endl;
		while (done){
			std::cout << "Sku: ";
			std::cin.getline(input, MAX_SKU_LEN);
			match = searchItems(input);
			if (input[0] == '\0')
				done = false;
			else{
				if (match == -1){
					std::cout << "v-------------------->" << std::endl;
					std::cout << "| " << _items[match]->name() << std::endl;
					std::cout << "^-------------------->" << std::endl;
					addToBill(*_items[match]);
				}
				else
					std::cout << "Not found!" << std::endl;
			}
		}
		showBill();
	}
	void PosApp::run(){
		int selection, match;
		char sku[MAX_SKU_LEN + 1];

		do{
			selection = menu();
			if (selection == 1)
				listItems();
			else if (selection == 2)
				addItem(true);
			else if (selection == 3)
				addItem(false);
			else if (selection == 4){
				updateQty();
			}
			else if (selection == 5){
				std::cout << "\nPlease enter the Sku: ";
				std::cin >> sku;
				match = searchItems(sku);
				if (match != -1){
					std::cout << "v-------------------->" << std::endl;
					std::cout << _items[match];
					std::cout << "^-------------------->" << std::endl;
				}
				else
					std::cout << "Not found!" << std::endl;
			}
			else if (selection == 6){
				POS();
			}
			else if (selection == 0){
				std::cout << "\nGoodbye!!\n>END" << std::endl;
			}
			else if (selection != 0)
				std::cout << "\n===Invalid Selection, try again===" << std::endl;
		} while (selection != 0);
	}



}