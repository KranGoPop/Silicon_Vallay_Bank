#include <string>
#include <cstdint>
#include <chrono>
#include "credit_account.h"
#include "bank.h"
#include "error.h"
#include "db_manager.h"
#include "command_update_balance.h"
#include "command_update_credit_last_update.h"

using namespace std::chrono;

CreditAccount::CreditAccount(Bank &bank, size_t user_id, size_t account_id, double credit_limit,
                             double commision, double percent, system_clock::time_point start_date,
                             seconds credit_cycle, system_clock::time_point last_update, double balance) :
    Account(bank, user_id, account_id, kCredit, balance), credit_limit_(credit_limit), commission_(commision),
    percent_(percent), start_date_(start_date), credit_cycle_(credit_cycle), last_update_(last_update) {
}

CreditAccount::CreditAccount(Bank &bank, size_t user_id, size_t account_id, double credit_limit,
                             double commision, double percent, seconds credit_cycle, double balance) :
    Account(bank, user_id, account_id, kCredit, balance), credit_limit_(credit_limit), commission_(commision),
    percent_(percent), start_date_(system_clock::now()), credit_cycle_(credit_cycle) {
  last_update_ = start_date_;
}

void CreditAccount::UpdateBalance() {
  if (balance_ >= 0) {
    return;
  }
  system_clock::time_point curr_date = system_clock::now();
  if (last_update_ + credit_cycle_ > curr_date) {
    return;
  }
  system_clock::time_point start = last_update_;
  int count_of_cycles = 0;
  while (curr_date >= start + credit_cycle_) {
    start += credit_cycle_;
    ++count_of_cycles;
  }
  for (int i = 0; i < count_of_cycles; ++i) {
    balance_ -= std::abs(balance_ * percent_);
  }
  last_update_ = curr_date;
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateCreditLastUpdate>(account_id_, last_update_));
}

bool CreditAccount::WithdrawMoney(double amount) {
  AmountIsNegative(amount);
  UpdateBalance();
  if (balance_ < 0) {
    amount *= commission_;
  }
  if (balance_ - amount <= 0 && std::abs(balance_ - amount) > credit_limit_) {
    throw ApplicationError(kCreditLimitExceed, "Credit limit exceeded");
  } else {
    balance_ -= amount;
  }
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateBalance>(account_id_, balance_));
  return true;
}

bool CreditAccount::WithdrawMoneySystem(double amount) {
  AmountIsNegative(amount);
  UpdateBalance();
  if (balance_ - amount <= 0 && std::abs(balance_ - amount) > credit_limit_) {
    balance_ = -credit_limit_;
  } else {
    balance_ -= amount;
  }
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateBalance>(account_id_, balance_));
  return true;
}

bool CreditAccount::DepositMoney(double amount) {
  AmountIsNegative(amount);
  UpdateBalance();
  /*if (balance_ + amount > credit_limit_) {
    throw ApplicationError(kCreditLimitExceed, "Credit limit exceeded");
  }*/
  balance_ += amount;
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateBalance>(account_id_, balance_));
  return true;
}

bool CreditAccount::DepositMoneySystem(double amount) {
  AmountIsNegative(amount);
  UpdateBalance();
  /*if (balance_ + amount > credit_limit_) {
    throw ApplicationError(kCreditLimitExceed, "Credit limit exceeded");
  }*/
  balance_ += amount;
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateBalance>(account_id_, balance_));
  return true;
}

std::shared_ptr<AccountInfo> CreditAccount::GetAccountInfo() {
  UpdateBalance();
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateBalance>(account_id_, balance_));
  return std::shared_ptr<CreditAccountInfo>(new CreditAccountInfo(bank_.GetBankId(), balance_, account_id_,
    user_id_, start_date_, credit_limit_, commission_, percent_, credit_cycle_, last_update_));
}