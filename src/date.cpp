#include "date.h"

Date::Date(const Date &date_) : data(date_.data) {}

Date Date::operator*(int right) const {
  return {this->data * right};
}

const Date operator+(const Date &left, const Date &right) {
  return {left.data + right.data};
}

bool Date::operator>=(const Date &right) const {
  return this->data >= right.data;
}

Date Date::operator+=(const Date &right) {
  this->data += right.data;
  return *this;
}

Date &Date::operator=(const Date &right) {
  this->data = right.data;
  return *this;
}

bool Date::operator>(const Date &right) const {
  return this->data > right.data;
}

bool Date::operator==(const Date &right) const {
  return data == right.data;
}

bool Date::operator!=(const Date &right) const {
  return data != right.data;
}

Date GetCurrDate() {
  auto curr_time = std::time(nullptr);
  uint64_t year = 1970;
  return {year * 31557600 + curr_time};
}

unsigned int Date::GetYear() const {
  return data / sec_in_year;
}

unsigned int Date::GetMonth() const {
  uint64_t res = (data - static_cast<uint64_t>(this->GetYear()) * sec_in_year) / sec_in_day;
  if (res == 0) {
    return 0;
  }
  return res / 30 + 1;
}

unsigned int Date::GetDay() const {
  return (data - static_cast<uint64_t>(this->GetYear()) * sec_in_year) / sec_in_day % 30;
}

unsigned int Date::GetMinute() const {
  return data % 3600 / 60;
}

unsigned int Date::GetSecond() const {
  return data % 60;
}

std::string Date::GetDate() const {
  std::string res;
  res.append(std::to_string(this->GetDay()));
  res.push_back('.');
  res.append(std::to_string(this->GetMonth()));
  res.push_back('.');
  res.append(std::to_string(this->GetYear()));
  return res;
}
