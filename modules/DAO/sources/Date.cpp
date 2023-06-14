#include "../includes/Date.hpp"
#include <iostream>
#include <string>
Date::Date(size_t month, size_t day, size_t year) {
  this->day = day;
  this->month = month;
  this->year = year;
}
bool Date::operator==(const Date &b) const {
  return (this->day == b.day && this->month == b.month && this->year == b.year);
}
bool Date::operator<(const Date &b) const {
  if (this->year > b.year) {
    return true;
  } else {
    if (this->year < b.year) {
      return false;
    } else if (this->year == b.year) {
      if (this->month > b.month) {
        return true;
      } else {
        if (this->month < b.month) {
          return false;
        } else if (this->month == b.month) {
          if (this->day > b.day) {
            return true;
          } else {
            if (this->day < b.day) {
              return false;
            } else if (this->day == b.day) {
              return false;
            }
          }
        }
      }
    }
  }
}
bool Date::operator>(const Date &b) const {
  if (!(*this < b) && !(*this == b)) {
    return true;
  }
  return false;
}

void Date::showDate() {
  std::cout << this->month << "/" << this->day << "/" << this->year << "\n";
}