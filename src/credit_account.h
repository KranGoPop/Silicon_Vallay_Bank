#include <cstdint>
#include "account.h"
#include "credit_account_info.h"
#include "enums.h"

#ifndef HEADER__CREDITACCOUNT_H_
#define HEADER__CREDITACCOUNT_H_

using namespace std::chrono;

class CreditAccount : public Account {
 private:
  const double credit_limit_ = 1e5;
  const double commission_ = 1.2;
  const double percent_ = 0.1;
  const system_clock::time_point start_date_;
  const seconds credit_cycle_ = 60s;
  system_clock::time_point last_update_;
  void UpdateBalance();
 public:
  CreditAccount(Bank& bank, size_t user_id, size_t account_id, double credit_limit,
    double commision, double percent, system_clock::time_point start_date_,
    seconds credit_cycle, system_clock::time_point last_update, double balance = 0);
  CreditAccount(Bank& bank, size_t user_id, size_t account_id, double credit_limit,
    double commision, double percent,
    seconds credit_cycle, double balance = 0);
  bool WithdrawMoney(double amount) override;
  bool WithdrawMoneySystem(double amount) override;
  bool DepositMoney(double amount) override;
  bool DepositMoneySystem(double amount) override;
  std::shared_ptr<AccountInfo> GetAccountInfo() override;
};

#endif //HEADER__CREDITACCOUNT_H_
