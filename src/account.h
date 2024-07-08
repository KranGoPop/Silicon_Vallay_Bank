#include <cstdint>
#include <memory>
#include "index.h"
#include "enums.h"
#include "account_info.h"

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
 protected:
  Bank& bank_;
  double balance_;
  const size_t user_id_;
  const size_t account_id_;
  bool is_account_open_;
  const AccountType account_type_;
  bool AmountIsNegative(double amount);
 public:
  Account(Bank& bank, size_t user_id, size_t account_id, AccountType account_type, double balance = 0);
  size_t GetUserId() const;
  bool IsOpen() const;
  void CloseAccount();
  virtual bool WithdrawMoney(double amount) = 0;
  virtual bool DepositMoney(double amount) = 0;
  virtual bool WithdrawMoneySystem(double amount) = 0;
  virtual bool DepositMoneySystem(double amount) = 0;
  virtual std::shared_ptr<AccountInfo> GetAccountInfo() = 0;
};

#endif