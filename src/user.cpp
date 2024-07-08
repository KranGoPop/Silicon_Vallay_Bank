#include <cstdint>
#include "user.h"
#include "bank.h"
#include "user_info.h"
#include "communicate_account.h"
#include "communicate_transactions.h"

User::User(Bank &bank, size_t user_id) :
    bank_(bank),
    user_info_(new UserInfo(bank, user_id)),
    communicate_account_(new CommunicateAccounts(bank, *this, user_id)),
    communicate_transactions_(new CommunicateTransactions(bank, user_id)) {
  user_id_ = user_id;
  closed_ = false;
}

User::User(Bank& bank, size_t user_id, std::string name, std::string surname, std::string address, size_t passport)
  : bank_(bank), user_info_(new UserInfo(bank, user_id, name, surname, address, passport)),
    communicate_account_(new CommunicateAccounts(bank, *this, user_id)),
    communicate_transactions_(new CommunicateTransactions(bank, user_id)) {
  user_id_ = user_id;
  closed_ = false;
}

void User::MakeClosed() {
  closed_ = true;
}

bool User::IsClosed() const {
  return closed_;
}

std::shared_ptr<UserInfo> User::GetUserInfo() {
  return user_info_;
}

std::shared_ptr<CommunicateAccounts> User::GetAccounts() {
  return communicate_account_;
}

std::shared_ptr<CommunicateTransactions> User::GetTransactions() {
  return communicate_transactions_;
}

size_t User::GetUserId() const {
  return user_id_;
}

User::~User() {
}