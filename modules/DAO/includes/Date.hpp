#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
public:
  Date() = default;
  Date(size_t day, size_t month, size_t year);
  bool operator==(const Date &b) const;
  bool operator<(const Date &b) const;
  bool operator>(const Date &b) const;
  void showDate();
  static Date stringToDate(std::string &text);
  size_t day, month, year;
};

#endif