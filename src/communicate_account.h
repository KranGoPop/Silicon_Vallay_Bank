#include <cstdint>
#include <vector>
#include <memory>
#include "index.h"
#include "enums.h"
#include "account_info.h"

#ifndef COMMUNICATION_ACCOUNT_H
#define COMMUNICATION_ACCOUNT_H

class CommunicateAccounts {
private:
  Bank& bank_;
  User& user_;
  size_t user_id_;
public:
  CommunicateAccounts(Bank& bank, User& user, size_t user_id);
  bool OpenAccount(AccountType acc_type);
  bool CloseAccount(size_t account_id);
  std::vector<std::shared_ptr<Account>> GetAccounts();
  bool WithdrawMoney(size_t account_id, double amount);
  bool DepositMoney(size_t account_id, double amount);
  bool TransferMoney(size_t src_account_id, size_t dest_account_id, double amount);
  std::shared_ptr<AccountInfo> GetAccountInfo(size_t account_id);
};

#endif