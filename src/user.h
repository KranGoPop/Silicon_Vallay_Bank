#include <cstdint>
#include <memory>
#include <string>
#include "index.h"

#ifndef USER_H
#define USER_H

class User {
 private:
  Bank &bank_;
  std::shared_ptr<UserInfo> user_info_;
  std::shared_ptr<CommunicateAccounts> communicate_account_;
  std::shared_ptr<CommunicateTransactions> communicate_transactions_;
  size_t user_id_;
  bool closed_;
 public:
  User(Bank &back, size_t user_id);
  User(Bank& bank, size_t user_id, std::string name, std::string surname, std::string address, size_t passport);
  std::shared_ptr<UserInfo> GetUserInfo();
  std::shared_ptr<CommunicateAccounts> GetAccounts();
  std::shared_ptr<CommunicateTransactions> GetTransactions();
  void MakeClosed();
  bool IsClosed() const;
  size_t GetUserId() const;
  ~User();
};

#endif
