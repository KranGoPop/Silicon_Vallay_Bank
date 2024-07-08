#include <cstdint>
#include <chrono>
#include "enums.h"

#ifndef HEADER__TRANSACTIONRECORD_H_
#define HEADER__TRANSACTIONRECORD_H_

using namespace std::chrono;

class TransactionRecord {
private:
  size_t bank_id_;
  AccountType source_account_type_;
  AccountType dest_account_type_;
  ActionType action_type_;
  TransactionType transaction_type_;
  system_clock::time_point time_;
  size_t transaction_id_;
  size_t user_id_recipient_;
  size_t user_id_sender_;
  double amount_;
  size_t source_account_id_;
  size_t dest_account_id_;
  bool canceled_;
public:
  TransactionRecord();
  TransactionRecord(size_t bank_id, AccountType src_account_type,
                    AccountType dest_account_type,
                    ActionType action_type,
                    TransactionType transaction_type,
                    size_t transaction_id,
                    size_t user_id_recipient,
                    size_t user_id_sender,
                    double amount,
                    size_t source_account_id,
                    size_t dest_account_id,
                    bool canceled);
  TransactionRecord &operator=(const TransactionRecord &copy) = default;
  AccountType GetAccountSrcType() const;
  AccountType GetAccountDestType() const;
  ActionType GetActionType() const;
  TransactionType GetTransactionType() const;
  system_clock::time_point GetTime() const;
  double GetAmount() const;
  size_t GetTransactionId() const;
  size_t GetUserIdRecipient() const;
  size_t GetUserIdSender() const;
  size_t GetSourceAccId() const;
  size_t GetDestAccId() const;
  bool IsCanceled() const;
  ~TransactionRecord() {};
};

#endif //HEADER__TRANSACTIONRECORD_H_
