#include <cstdint>
#include <chrono>
#include "transaction_record.h"
#include "enums.h"

using namespace std::chrono;

TransactionRecord::TransactionRecord() : bank_id_(0), source_account_type_(kDebit), dest_account_type_(kDebit), action_type_(kWithdrawMoney),
    transaction_type_(kUsual), transaction_id_(0), user_id_recipient_(0), user_id_sender_(0), amount_(0), source_account_id_(0),
    dest_account_id_(0), time_(system_clock::now()), canceled_(false) {
}

TransactionRecord::TransactionRecord(size_t bank_id, AccountType src_account_type,
  AccountType dest_account_type,
  ActionType action_type,
  TransactionType transaction_type,
  size_t transaction_id,
  size_t user_id_recipient,
  size_t user_id_sender,
  double amount,
  size_t source_account_id,
  size_t dest_account_id,
  bool canceled) : bank_id_(bank_id), source_account_type_(src_account_type), dest_account_type_(dest_account_type),
    action_type_(action_type), transaction_type_(transaction_type), transaction_id_(transaction_id),
    user_id_recipient_(user_id_recipient), user_id_sender_(user_id_sender), amount_(amount),
    source_account_id_(source_account_id), dest_account_id_(dest_account_id), time_(system_clock::now()), canceled_(canceled) {
}

//TransactionRecord& TransactionRecord::operator=(const TransactionRecord& copy) {
//  source_account_type_ = copy.source_account_type_;
//  dest_account_type_ = copy.dest_account_type_;
//  action_type_ = copy.action_type_;
//  transaction_id_ = copy.transaction_id_;
//  time_ = copy.time_;
//  transaction_type_ = copy.transaction_type_;
//  user_id_recipient_ = copy.user_id_recipient_;
//  user_id_sender_ = copy.user_id_sender_;
//  amount_ = copy.amount_;
//  source_account_id_ = copy.source_account_id_;
//  dest_account_id_ = copy.dest_account_id_;
//  return *this;
//}

AccountType TransactionRecord::GetAccountSrcType() const {
  return source_account_type_;
}

AccountType TransactionRecord::GetAccountDestType() const {
  return dest_account_type_;
}

ActionType TransactionRecord::GetActionType() const {
  return action_type_;
}

TransactionType TransactionRecord::GetTransactionType() const {
  return transaction_type_;
}

system_clock::time_point TransactionRecord::GetTime() const {
  return time_;
}

double TransactionRecord::GetAmount() const {
  return amount_;
}

size_t TransactionRecord::GetTransactionId() const {
  return transaction_id_;
}

size_t TransactionRecord::GetUserIdRecipient() const {
  return user_id_recipient_;
}

size_t TransactionRecord::GetUserIdSender() const {
  return user_id_sender_;
}

size_t TransactionRecord::GetSourceAccId() const {
  return source_account_id_;
}

size_t TransactionRecord::GetDestAccId() const {
  return dest_account_id_;
}

bool TransactionRecord::IsCanceled() const {
  return canceled_;
}