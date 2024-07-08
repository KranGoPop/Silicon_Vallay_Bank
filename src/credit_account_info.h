#include <chrono>
#include "account_info.h"
#include "enums.h"

#ifndef HEADER__CREDITACCOUNTINFO_H_
#define HEADER__CREDITACCOUNTINFO_H_

using namespace std::chrono;

class CreditAccountInfo : public AccountInfo {
 private:
  double credit_limit_;
  double commission_;
  double percent_;
  system_clock::time_point start_date_;
  seconds credit_cycle_;
  system_clock::time_point last_update_;
 public:
  CreditAccountInfo();
  CreditAccountInfo(size_t bank_id, double balance,
                    size_t account_id,
                    size_t user_id,
                    system_clock::time_point start_date,
                    double credit_limit,
                    double commission,
                    double percent,
                    seconds credit_cycle,
                    system_clock::time_point last_update);
  system_clock::time_point GetStartDate() const;
  system_clock::time_point GetLastUpdate() const;
  double GetCreditLimit() const;
  double GetCommission() const;
  double GetPercent() const;
  seconds GetCreditCycle() const;
};

#endif //HEADER__CREDITACCOUNTINFO_H_
