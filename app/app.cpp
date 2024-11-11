#include "app.h"

namespace vsite::oop::v4
{

	std::string leg_counter::add_animal(animal* some_animal)
	{
		if (some_animal == nullptr) {
			return "No new animal has been made";
		}

		leg_num += some_animal->legs();
		std::string animal_name = some_animal->species();

		return animal_name;
	}

	unsigned int leg_counter::legs() const
	{
		return leg_num;
	}

	unsigned int cockroach::legs() const
	{
		return 6;
	}

	std::string cockroach::species() const
	{
		return "cockroach";
	}

	std::string sparrow::species() const
	{
		return "sparrow";
	}

	unsigned int bird::legs() const
	{
		return 2;
	}

	std::string tarantula::species() const
	{
		return "tarantula";
	}

	unsigned int spider::legs() const
	{
		return 8;
	}

	std::unique_ptr<animal> animal_factory(const int animal_number)
	{
		switch (animal_number)
		{
		case 1:
			return std::make_unique<cockroach>();
		case 2:
			return std::make_unique<sparrow>();
		case 3:
			return std::make_unique<tarantula>();
		default:
			return nullptr;
		}
	}
}