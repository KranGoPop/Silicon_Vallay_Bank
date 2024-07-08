#include <string>
#include <cstdint>

#ifndef BANK_INFO_H
#define BANK_INFO_H

class BankInfo {
private:
  std::string name_;
  std::string city_;
  size_t bank_id_;
public:
  BankInfo() = default;
  BankInfo(size_t bank_id, std::string name, std::string city);
  std::string GetName() const;
  std::string GetCity() const;
  size_t GetBankId() const;
};

#endif