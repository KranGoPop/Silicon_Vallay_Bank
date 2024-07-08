#include <chrono>
#include <cstdint>
#include "account_info.h"
#include "date.h"

#ifndef SRC_DEPOSIT_ACCOUNT_INFO_H
#define SRC_DEPOSIT_ACCOUNT_INFO_H

using namespace std::chrono;

class DepositAccountInfo : public AccountInfo {
 private:
  system_clock::time_point start_date_;
  seconds withdrawal_timeout_;
  seconds manage_timeout_;
  double percent_;
  int count_of_cycles_;
  system_clock::time_point last_update_;
 public:
  DepositAccountInfo();
  DepositAccountInfo(size_t bank_id, double balance,
                     size_t account_id,
                     size_t user_id,
                     system_clock::time_point start_date,
                     seconds withdrawal_timeout,
                     seconds manage_timeout,
                     double percent,
                     int cycle_count, 
                     system_clock::time_point last_update);
  system_clock::time_point GetStartDate() const;
  system_clock::time_point GetLastUpdate() const;
  int GetCycleCount() const;
  seconds GetWithdrawTimeout() const;
  seconds GetManageTimeout() const;
  double GetPercent() const;

};

#endif //SRC_DEPOSIT_ACCOUNT_INFO_H
