#pragma once
#include <string>
#include <memory>

namespace vsite::oop::v4 
{
	class animal
	{
	public:
		virtual std::string species() const = 0;
		virtual unsigned int legs() const = 0;
		virtual ~animal() = default;
	};

	class insect: public animal
	{
		unsigned int legs() const override;
	};

	class cockroach: public insect
	{
	public:
		std::string species() const override;
		~cockroach() = default;
	};

	class spider: public insect
	{
	public:
		unsigned int legs() const override;
	};

	class tarantula: public spider
	{
	public:	
		std::string species() const override;
		~tarantula() = default;
	};

	class bird: public animal
	{
	public:
		unsigned int legs() const override;
	};

	class sparrow: public bird
	{
	public:
		std::string species() const override;
		~sparrow() = default;
	};

	class leg_counter
	{
	public:
		leg_counter() : leg_num(0) {}
		~leg_counter() = default;
		unsigned int legs() const;
		std::string add_animal(const animal* some_animal);

	private:
		unsigned int leg_num;
	};

	std::unique_ptr<animal> animal_factory(const int animal_number);

}