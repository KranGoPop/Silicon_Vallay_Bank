#include <cstdint>
#include "account_info.h"
#include "enums.h"

AccountInfo::AccountInfo() : bank_id_(0), balance_(0), account_id_(0), user_id_(0), account_type_(kDebit) {}

AccountInfo::AccountInfo(size_t bank_id, double balance, size_t account_id, size_t user_id, AccountType account_type) :
  bank_id_(bank_id), balance_(balance), account_id_(account_id), user_id_(user_id), account_type_(account_type) {
}

const double AccountInfo::GetBalance() const {
  return balance_;
}

const size_t AccountInfo::GetAccountId() const {
  return account_id_;
}

const size_t AccountInfo::GetUserId() const {
  return user_id_;
}

const size_t AccountInfo::GetBankId() const {
  return bank_id_;
}

const AccountType AccountInfo::GetAccountType() const {
  return account_type_;
}