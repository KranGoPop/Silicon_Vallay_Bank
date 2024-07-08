#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <mysql/jdbc.h>
#include "index.h"

#ifndef SRC_RESERVE_SILICON_VALLEY_BANK_2_SRC_BANK_H_
#define SRC_RESERVE_SILICON_VALLEY_BANK_2_SRC_BANK_H_

class Bank {
 private:
  std::string bank_name_;
  std::string location_city_;
  size_t bank_id_;
  std::shared_ptr<TransactionManager> transaction_manager_;
  std::shared_ptr<AccountManager> account_manager_;
  std::shared_ptr<UserManager> user_manager_;
  std::shared_ptr<DBManager> db_manager_;
 public:
  Bank();
  Bank(size_t bank_id, std::string bank_name, std::string bank_locaton, std::shared_ptr<sql::Statement> stm);
  Bank& operator=(const Bank& copy);
  std::shared_ptr<TransactionManager> GetTransactionManager() const;
  std::shared_ptr<AccountManager> GetAccountManager() const;
  std::shared_ptr<UserManager> GetUserManager() const;
  std::shared_ptr<DBManager> GetDBManager() const;
  size_t GetBankId() const;
  std::string GetName() const;
  std::string GetCity() const;
  ~Bank();
};

#endif
