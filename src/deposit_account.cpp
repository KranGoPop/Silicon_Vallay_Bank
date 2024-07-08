#include <string>
#include <chrono>
#include <memory>
#include <mysql/jdbc.h>
#include "deposit_account.h"
#include "deposit_account_info.h"
#include "error.h"
#include "bank.h"
#include "enums.h"
#include "db_manager.h"
#include "command_update_balance.h"
#include "command_update_deposit_last_update.h"

using namespace std::chrono;

DepositAccount::DepositAccount(Bank& bank, size_t user_id, size_t account_id,
  system_clock::time_point start_date, seconds withdraw_timeout,
  seconds manage_timeout, double percent, int cycle_count, system_clock::time_point last_update, double balance)
  : Account(bank, user_id, account_id, kDeposit, balance), start_date_(start_date), withdrawal_timeout_(withdraw_timeout),
    manage_timeout_(manage_timeout), percent_(percent), count_of_cycles_(cycle_count), last_update_(last_update) {

}

DepositAccount::DepositAccount(Bank& bank, size_t user_id, size_t account_id,
  seconds withdraw_timeout, seconds manage_timeout, double percent, int cycle_count, double balance)
  : Account(bank, user_id, account_id, kDeposit, balance), start_date_(system_clock::now()), withdrawal_timeout_(withdraw_timeout),
  manage_timeout_(manage_timeout), percent_(percent), count_of_cycles_(cycle_count) {
  last_update_ = start_date_;
}

void DepositAccount::UpdateBalance() {
  system_clock::time_point curr_date = system_clock::now();
  if (last_update_ + withdrawal_timeout_ > curr_date) {
    return;
  }
  system_clock::time_point start = start_date_ + (withdrawal_timeout_ + manage_timeout_) * count_of_cycles_;
  int count_of_cycles = 0;
  while (curr_date >= start + withdrawal_timeout_) {
    start += withdrawal_timeout_ + manage_timeout_;
    ++count_of_cycles;
  }
  for (int i = 0; i < count_of_cycles; ++i) {
    balance_ *= percent_;
  }
  count_of_cycles_ += count_of_cycles;
  last_update_ = curr_date;
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateDepositLastUpdate>(account_id_, last_update_));
}

bool DepositAccount::DepositMoney(double amount) {
  AmountIsNegative(amount);
  UpdateBalance();
  balance_ += amount;
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateBalance>(account_id_, balance_));
  return true;
}

bool DepositAccount::DepositMoneySystem(double amount) {
  AmountIsNegative(amount);
  UpdateBalance();
  balance_ += amount;
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateBalance>(account_id_, balance_));
  return true;
}

bool DepositAccount::WithdrawMoney(double amount) {
  AmountIsNegative(amount);
  UpdateBalance();
  system_clock::time_point curr_date = system_clock::now();
  system_clock::time_point start = start_date_ + (withdrawal_timeout_ + manage_timeout_) * count_of_cycles_;
  if (start >= curr_date) {
    if (balance_ - amount < 0) {
      throw ApplicationError(kNotEnoughFunds, "Not enough funds");
    }
    balance_ -= amount;
    bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateBalance>(account_id_, balance_));
    return true;
  } else {
    throw ApplicationError(kNotAManage, "It's not a manage time");
  }
}

bool DepositAccount::WithdrawMoneySystem(double amount) {
  AmountIsNegative(amount);
  UpdateBalance();
  if (balance_ - amount <= 0) {
    balance_ = 0;
  } else {
    balance_ -= amount;
  }
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateBalance>(account_id_, balance_));
  return true;
}

std::shared_ptr<AccountInfo> DepositAccount::GetAccountInfo() {
  UpdateBalance();
  bank_.GetDBManager()->SendExecutable(std::make_shared<CommandUpdateBalance>(account_id_, balance_));
  return std::shared_ptr<DepositAccountInfo>(new DepositAccountInfo(bank_.GetBankId(), balance_, account_id_,
    user_id_, start_date_, withdrawal_timeout_, manage_timeout_, percent_, count_of_cycles_, last_update_));
}