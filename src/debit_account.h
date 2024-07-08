#include <cstdint>
#include <memory>
#include "account.h"
#include "debit_account_info.h"
#include "index.h"

#ifndef HEADER__DEBITACCOUNT_H_
#define HEADER__DEBITACCOUNT_H_

class DebitAccount : public Account {
 public:
  DebitAccount(Bank& bank, size_t user_id, size_t account_id, double balance = 0);
  bool WithdrawMoney(double amount) override;
  bool DepositMoney(double amount) override;
  bool WithdrawMoneySystem(double amount) override;
  bool DepositMoneySystem(double amount) override;
  std::shared_ptr<AccountInfo> GetAccountInfo() override;
};

#endif
