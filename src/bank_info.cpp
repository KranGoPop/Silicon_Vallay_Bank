#include "bank_info.h"

BankInfo::BankInfo(size_t bank_id, std::string name, std::string city) : bank_id_(bank_id) {
  name_ = name;
  city_ = city;
}

std::string BankInfo::GetName() const {
  return name_;
}

std::string BankInfo::GetCity() const {
  return city_;
}

size_t BankInfo::GetBankId() const {
  return bank_id_;
}