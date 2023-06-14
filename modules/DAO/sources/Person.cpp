#include "../includes/Person.hpp"
#include "../includes/Date.hpp"

Person::Person(std::string CPF, std::string name, std::string surname,
               Date birthday, std::string hometown) {
  this->CPF = CPF;
  this->name = name;
  this->surname = surname;
  this->birthday = birthday;
  this->hometown = hometown;
}

void Person::showPerson() {
  std::cout << "-----------------------------------------------"
            << "\n";
  std::cout << "CPF: " << this->CPF << "\n";
  std::cout << "Nome: " << this->name << "\n";
  std::cout << "Sobrenome: " << this->surname << "\n";
  std::cout << "Data de Nascimento: ";
  (this->birthday).showDate();
  std::cout << "Cidade Natal: " << this->hometown << "\n";
}

std::string Person::getCPF() { return this->CPF; }
std::string Person::getName() { return this->name; }
Date Person::getBirthday() { return this->birthday; }

Person::~Person() {}