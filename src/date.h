#include <ctime>
#include <stdint.h>
#include <string>

#ifndef DATE
#define DATE

struct Date {
  Date() = default;
  Date(const Date &date_);
  Date(unsigned int year_, unsigned short month_, unsigned short day_) : data(
      year_ * 31557600 + (30 * month_ + day_) * 86400) {}
  Date(uint64_t data_) : data(data_) {}
  friend Date GetCurrDate();
  unsigned int GetYear() const;
  unsigned int GetMonth() const;
  unsigned int GetDay() const;
  unsigned int GetMinute() const;
  unsigned int GetSecond() const;
  std::string GetDate() const;
  friend const Date operator+(const Date &left, const Date &right);
  bool operator>(const Date &) const;
  bool operator>=(const Date &) const;
  Date operator+=(const Date &);
  bool operator==(const Date &) const;
  bool operator!=(const Date &) const;
  Date &operator=(const Date &);
  Date operator*(int) const;
 private:
  uint64_t data = 0;  // дата в секундах
  const int sec_in_year = 31557600;
  const int sec_in_day = 86400;
};

Date GetCurrDate();
const Date operator+(const Date &left, const Date &right);

#endif