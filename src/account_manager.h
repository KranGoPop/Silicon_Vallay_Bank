#include <cstdint>
#include <vector>
#include <memory>
#include "index.h"
#include "account.h"

#ifndef SRC__ACCOUNT_MANAGER_H_
#define SRC__ACCOUNT_MANAGER_H_

class AccountManager {
 private:
  Bank& bank_;
  const double fixed_limit_ = 10000;
 public:
  AccountManager(Bank& bank);
  AccountManager& operator=(const AccountManager& copy) = default;
  std::shared_ptr<Account> GetAccount(size_t user_id, size_t account_id);
  std::shared_ptr<Account> GetAccountSystem(size_t account_id);
  std::vector<std::shared_ptr<Account>> GetUserAccounts(size_t user_id);
  bool OpenAccount(size_t user_id, AccountType account_type);
  bool CloseAccount(size_t user_id, size_t account_id);
  bool CancelTransaction(size_t user_id, size_t transaction_id);
  double GetLimit() const;
  ~AccountManager() {};
};

#endif //SRC__ACCOUNT_MANAGER_H_
