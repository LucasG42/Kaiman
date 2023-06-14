#include "Kaiman/Kaiman.hpp"
#include "modules/DAO/includes/Date.hpp"
#include "modules/DAO/includes/Person.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

Date stringToDate(std::string &text) {
  std::string texto;
  texto += text[0];
  texto += text[1];
  int month = std::stoi(texto);
  texto = "";
  texto += text[3];
  texto += text[4];
  int day = std::stoi(texto);
  texto = "";
  texto += text[6];
  texto += text[7];
  texto += text[8];
  texto += text[9];
  int year = std::stoi(texto);

  return Date(month, day, year);
}

bool validateCPF(std::string const &cpf) {
  std::regex regex("^\\d{3}\\.\\d{3}\\.\\d{3}-\\d{2}$");
  return std::regex_match(cpf, regex);
}
bool validateData(std::string const &date) {
  std::regex regex(R"(^(0[1-9]|1[0-2])/(0[1-9]|1\d|2\d|3[01])/\d{4}$)");
  return std::regex_match(date, regex);
}

void showResult(std::vector<Person *> const &result) {
  for (auto pessoa : result) {
    pessoa->showPerson();
  }
}
bool startWith(std::string const &s1, std::string const &s2) {
  int size = std::min(s1.size(), s2.size());
  for (int i = 0; i < size; i++) {
    if (s1[i] != s2[i]) {
      return false;
    }
  }
  return true;
}

void standDate(std::string &inputDate) {
  std::stringstream ss(inputDate);
  std::string component;
  std::string transformedDate;

  // Split the input string into components
  std::getline(ss, component, '/');
  int month = std::stoi(component);
  std::getline(ss, component, '/');
  int day = std::stoi(component);
  std::getline(ss, component, '/');
  int year = std::stoi(component);

  // Format the components with leading zeros
  std::stringstream formattedMonth;
  formattedMonth << std::setw(2) << std::setfill('0') << month;
  std::stringstream formattedDay;
  formattedDay << std::setw(2) << std::setfill('0') << day;

  // Concatenate the formatted components
  transformedDate = formattedMonth.str() + "/" + formattedDay.str() + "/" +
                    std::to_string(year);

  inputDate = transformedDate;
}
int main(int argc, char *argv[]) {

  // Lendo o arquivo e indexando as pessoas.
  if (argc < 2) {
    std::cout << "Por favor insira o caminho do arquivo .csv que deseja usar "
                 "na aplicação \n";
    return 0;
  }

  std::string input = std::string(argv[1]);
  std::vector<std::string> tmp;
  tmp.reserve(5);

  Kaiman<std::string, Person *> CPF;
  Kaiman<std::string, Person *> Name;
  Kaiman<Date, Person *> Birthday;

  std::ifstream fin;
  std::string line;

  fin.open(input);

  int i = 0;
  while (std::getline(fin, line)) {
    if (i == 0) {
      i = 1;
      continue;
    }

    std::istringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ',')) {
      tmp.push_back(token);
    }

    standDate(tmp[3]);

    Date date = stringToDate(tmp[3]);

    Person *person = new Person(tmp[0], tmp[1], tmp[2], date, tmp[4]);

    CPF.insert(person->getCPF(), person);
    Name.insert(person->getName(), person);
    Birthday.insert(person->getBirthday(), person);
    tmp.clear();
  }

  // Command Line Interface

  int opc = 0;
  std::string answer;

  std::cout << "-----------------------------------------------"
            << "\n";
  std::cout
      << "Bem Vindo ao sistema, por favor use das opções abaixo para prosseguir"
      << "\n";
  std::cout << "-----------------------------------------------"
            << "\n";
  try {
    do {
      std::cout << "-----------------------------------------------"
                << "\n";
      std::cout << "1- Pesquisa por CPF"
                << "\n";

      std::cout << "2- Pesquisa por Nome"
                << "\n";

      std::cout
          << "3- Pesquise por pessoas nascidas no intervalo entre duas datas"
          << "\n";

      std::cout << "Para sair digite -1"
                << "\n";
      std::cin >> opc;

      auto iterador = Kaiman<std::string, Person *>::Iterator(CPF.getRoot());
      switch (opc) {
      case -1:
        continue;
      case 1:
        std::cout << "Digite o CPF: \n";
        std::cin >> answer;
        if (validateCPF(answer)) {
          auto result = CPF.find(answer);
          showResult(result);
        } else {
          std::cout << "CPF informado não é válido \n";
        }
        answer.clear();
        break;

      case 2:
        std::cout << "Digite o nome da pessoa \n";
        std::cin >> answer;
        ;
        while (iterador.hasNext()) {
          for (auto person : iterador.next()) {
            if (startWith(person->getName(), answer)) {
              person->showPerson();
            }
          }
        }
        break;
      case 3:
        std::string data1;
        std::string data2;
        std::cout << "Digite datas no formato MM/DD/YYYY caso contrário não "
                     "irá funcionar\n";
        std::cout << " Digite a data de inicio: \n";
        std::cin >> data1;

        std::cout << " Digite a data de fim: \n";
        std::cin >> data2;

        if (validateData(data1) && validateData(data2)) {
          if (stringToDate(data1) > stringToDate(data2)) {
            std::cout << "Data de inicio maior que a inicial\n";
          } else {
            iterador = Kaiman<std::string, Person *>::Iterator(CPF.getRoot());
            while (iterador.hasNext()) {
              for (auto person : iterador.next()) {
                std::cout << "Data de nascimento da pessoa ";
                person->getBirthday().showDate();
                if (person->getBirthday() > stringToDate(data1) &&
                    person->getBirthday() < stringToDate(data2)) {
                  person->showPerson();
                }
              }
            }
          }
        } else {
          std::cout << "Erro no formato das datas \n";
        }

        break;
      }
    } while (opc != -1);
  } catch (...) {
    std::cout << "Ocorreu um erro inesperado... Reinicie o sistema\n";
  }
}
