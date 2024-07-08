#include <string>
#include <cstdint>
#include "index.h"

#ifndef USER_INFO
#define USER_INFO

class UserInfo {
 private:
  Bank& bank_;
  size_t user_id_;
  std::string name_;
  std::string surname_;
  std::string address_;
  size_t passport_;
  bool trusted_;
  void SetTrusted();
  void SendUpdate() const;
 public:
  UserInfo(Bank& bank, size_t user_id);
  UserInfo(Bank& bank, size_t user_id, std::string name, std::string surname, std::string address, size_t passport);
  std::string GetName() const;
  std::string GetSurname() const;
  std::string GetAddress() const;
  size_t GetPassport() const;
  void SetName(std::string name);
  void SetSurname(std::string surname);
  void SetAddress(std::string address);
  void SetPassport(size_t passport);
  bool IsTrusted() const;
};

#endif