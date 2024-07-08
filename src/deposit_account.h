#include <chrono>
#include <cstdint>
#include "account.h"
#include "deposit_account_info.h"

#ifndef SRC__DEPOSIT_H_
#define SRC__DEPOSIT_H_

using namespace std::chrono;

class DepositAccount : public Account {
 private:
  const system_clock::time_point start_date_;
  const seconds withdrawal_timeout_ = 1s;
  const seconds manage_timeout_ = 10s;
  const double percent_ = 1.1;
  int count_of_cycles_ = 0;
  system_clock::time_point last_update_;
  void UpdateBalance();
 public:
  DepositAccount(Bank& bank, size_t user_id, size_t account_id,
    system_clock::time_point start_date, seconds withdraw_timeout,
    seconds manage_timeout, double percent, int cycle_count, system_clock::time_point last_update, double balance = 0);
  DepositAccount(Bank& bank, size_t user_id, size_t account_id,
    seconds withdraw_timeout, seconds manage_timeout, double percent, int cycle_count, double balance = 0);
  bool WithdrawMoney(double amount) override;
  bool WithdrawMoneySystem(double amount) override;
  bool DepositMoney(double amount) override;
  bool DepositMoneySystem(double amount) override;
  std::shared_ptr<AccountInfo> GetAccountInfo() override;
};

#endif //SRC__DEPOSIT_H_
