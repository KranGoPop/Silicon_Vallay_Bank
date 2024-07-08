#include <chrono>
#include <cstdint>
#include "account_info.h"
#include "enums.h"
#include "credit_account_info.h"

using namespace std::chrono;

CreditAccountInfo::CreditAccountInfo() : AccountInfo(0, 0, 0, 0, kCredit) {
  credit_limit_ = 0;
  commission_ = 0;
  percent_ = 0;
  credit_cycle_ = 0s;
}

CreditAccountInfo::CreditAccountInfo(size_t bank_id, double balance,
  size_t account_id, size_t user_id, system_clock::time_point start_date,
  double credit_limit, double commission, double percent,
  seconds credit_cycle, system_clock::time_point last_update)
  : AccountInfo(bank_id, balance, account_id, user_id, AccountType::kCredit),
    start_date_(start_date), credit_cycle_(credit_cycle), credit_limit_(credit_limit),
    commission_(commission), percent_(percent), last_update_(last_update) {
}

system_clock::time_point CreditAccountInfo::GetStartDate() const {
  return start_date_;
}

system_clock::time_point CreditAccountInfo::GetLastUpdate() const {
  return last_update_;
}

double CreditAccountInfo::GetCommission() const {
  return commission_;
}

double CreditAccountInfo::GetCreditLimit() const {
  return credit_limit_;
}

double CreditAccountInfo::GetPercent() const {
  return percent_;
}

seconds CreditAccountInfo::GetCreditCycle() const {
  return credit_cycle_;
}