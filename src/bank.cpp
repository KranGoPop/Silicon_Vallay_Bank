#include <utility>
#include "bank.h"
#include "account_manager.h"
#include "user_manager.h"
#include "transaction_manager.h"
#include "user_manager.h"
#include "db_manager.h"

Bank::Bank() {
  bank_name_ = "";
  location_city_ = "";
  transaction_manager_ = nullptr;
  account_manager_ = nullptr;
  user_manager_ = nullptr;
  bank_id_ = 0;
}

Bank::Bank(size_t bank_id, std::string name, std::string location, std::shared_ptr<sql::Statement> stm) :
    transaction_manager_(new TransactionManager(*this)),
    account_manager_(new AccountManager(*this)),
    user_manager_(new UserManager(*this)),
    db_manager_(new DBManager(bank_id, stm)) {
  bank_name_ = name;
  location_city_ = location;
  bank_id_ = bank_id;
  //db_manager_.reset(new DBManager(bank_id_/*, this*/));
}

Bank &Bank::operator=(const Bank &copy) {
  bank_name_ = copy.bank_name_;
  location_city_ = copy.location_city_;
  transaction_manager_ = copy.transaction_manager_;
  account_manager_ = copy.account_manager_;
  user_manager_ = copy.user_manager_;
  return *this;
}

std::shared_ptr<TransactionManager> Bank::GetTransactionManager() const {
  return transaction_manager_;
}

std::shared_ptr<AccountManager> Bank::GetAccountManager() const {
  return account_manager_;
}

std::shared_ptr<UserManager> Bank::GetUserManager() const {
  return user_manager_;
}

std::shared_ptr<DBManager> Bank::GetDBManager() const {
  return db_manager_;
}

size_t Bank::GetBankId() const {
  return bank_id_;
}

std::string Bank::GetName() const {
  return bank_name_;
}

std::string Bank::GetCity() const {
  return location_city_;
}

Bank::~Bank() {
}