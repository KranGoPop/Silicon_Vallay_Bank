#include <chrono>
#include <cstdint>
#include "deposit_account_info.h"
#include "account_info.h"
#include "date.h"

using namespace std::chrono;

DepositAccountInfo::DepositAccountInfo() : AccountInfo(0, 0, 0, 0, kDebit) {
  balance_ = 0;
  account_id_ = 0;
  percent_ = 0;
  manage_timeout_ = 0s;
  withdrawal_timeout_ = 0s;
  count_of_cycles_ = 0;
}

DepositAccountInfo::DepositAccountInfo(size_t bank_id, double balance, size_t account_id, size_t user_id,
  system_clock::time_point start_date, seconds withdrawal_timeout,
  seconds manage_timeout, double percent,
  int cycle_count, system_clock::time_point last_update) :
    AccountInfo(bank_id, balance, account_id, user_id, AccountType::kDeposit), start_date_(start_date),
    withdrawal_timeout_(withdrawal_timeout),
    manage_timeout_(manage_timeout), percent_(percent), count_of_cycles_(cycle_count), last_update_(last_update) {
}

system_clock::time_point DepositAccountInfo::GetStartDate() const {
  return start_date_;
}

system_clock::time_point DepositAccountInfo::GetLastUpdate() const {
  return last_update_;
}

int DepositAccountInfo::GetCycleCount() const {
  return count_of_cycles_;
}

seconds DepositAccountInfo::GetWithdrawTimeout() const {
  return withdrawal_timeout_;
}

seconds DepositAccountInfo::GetManageTimeout() const {
  return manage_timeout_;
}

double DepositAccountInfo::GetPercent() const {
  return percent_;
}