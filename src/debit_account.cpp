#include <string>
#include "debit_account.h"
#include "bank.h"
#include "enums.h"
#include "error.h"
#include "command_update_balance.h"
#include "db_manager.h"

DebitAccount::DebitAccount(Bank& bank, size_t user_id, size_t account_id, double balance) : Account(bank, user_id, account_id, AccountType::kDebit, balance) {
}

bool DebitAccount::WithdrawMoney(double amount) {
  AmountIsNegative(amount);
  if (balance_ - amount < 0) {
    throw ApplicationError(kNotEnoughFunds, "Insufficient funds");
  }
  balance_ -= amount;
  auto update_balance = std::make_shared<CommandUpdateBalance>(account_id_, balance_);
  bank_.GetDBManager()->SendExecutable(update_balance);
  return true;
}

bool DebitAccount::WithdrawMoneySystem(double amount) {
  AmountIsNegative(amount);
  if (balance_ - amount <= 0) {
    balance_ = 0;
  }
  else {
    balance_ -= amount;
  }
  auto update_balance = std::make_shared<CommandUpdateBalance>(account_id_, balance_);
  bank_.GetDBManager()->SendExecutable(update_balance);
  return true;
}

bool DebitAccount::DepositMoney(double amount) {
  AmountIsNegative(amount);
  balance_ += amount;
  auto update_balance = std::make_shared<CommandUpdateBalance>(account_id_, balance_);
  bank_.GetDBManager()->SendExecutable(update_balance);
  return true;
}

bool DebitAccount::DepositMoneySystem(double amount) {
  AmountIsNegative(amount);
  balance_ += amount;
  auto update_balance = std::make_shared<CommandUpdateBalance>(account_id_, balance_);
  bank_.GetDBManager()->SendExecutable(update_balance);
  return true;
}

std::shared_ptr<AccountInfo> DebitAccount::GetAccountInfo() {
  return std::shared_ptr<AccountInfo>(new DebitAccountInfo(bank_.GetBankId(), balance_, account_id_, user_id_));
}