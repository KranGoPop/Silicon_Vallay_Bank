#include "account.h"
#include "enums.h"
#include "error.h"
#include "bank.h"

Account::Account(Bank& bank, size_t user_id, size_t account_id, AccountType account_type, double balance) :
          bank_(bank), user_id_(user_id), account_id_(account_id), account_type_(account_type), balance_(balance) {
  is_account_open_ = true;
}

size_t Account::GetUserId() const {
  return user_id_;
}

void Account::CloseAccount() {
  is_account_open_ = false;
}

bool Account::IsOpen() const {
  return is_account_open_;
}

bool Account::AmountIsNegative(double amount) {
  if (amount < 0) {
    throw ApplicationError(kNegativeAmount, "Amount cannot be negative");
  }

  return true;
}