#include "app.h"
#include <iostream>
using namespace vsite::oop::v4;

// read animal id's (until 0) and display species name
// display total leg count
int main()
{
	leg_counter count_leg = leg_counter();

	int animal_id;
	while (true) {
		std::cout << "What number animal would you like: ";
		std::cin >> animal_id;

		if (animal_id == 0) {
			break;
		}

		std::unique_ptr<animal> new_animal = animal_factory(animal_id);
		std::cout << count_leg.add_animal(new_animal.get()) << std::endl;
	}

	std::cout << "We counted: " << count_leg.legs() << " legs" << std::endl;
}
