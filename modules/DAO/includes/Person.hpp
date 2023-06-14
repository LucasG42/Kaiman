#ifndef PERSON_H_
#define PERSON_H_

#include <ctime>
#include <iostream>
#include <string>

#include "Date.hpp"

class Person {
private:
  std::string CPF;
  std::string name;
  std::string surname;
  Date birthday;
  std::string hometown;

public:
  Person(std::string CPF, std::string name, std::string surname, Date birthday,
         std::string hometown);
  std::string getCPF();
  std::string getName();
  Date getBirthday();
  void showPerson();
  ~Person();
};

#endif // PERSON_H_
