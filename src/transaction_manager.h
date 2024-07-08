#include <vector>
#include <cstdint>
#include <utility>
#include <memory>
#include "index.h"
#include "transaction_record.h"

#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

typedef bool Canceled;

class TransactionManager {
 private:
  Bank &bank_;
  std::vector<std::pair<TransactionRecord, Canceled>> history_;
 public:
  TransactionManager(Bank &bank);
  TransactionManager &operator=(const TransactionManager &copy) = default;
  bool AddTransactionSystem(AccountType src_acc_type,
                            AccountType dest_acc_type,
                            ActionType act_type,
                            size_t user_id_res,
                            size_t user_id_src,
                            double amount,
                            size_t acc_id_src,
                            size_t acc_id_dest, bool canceled = false);
  TransactionRecord CancelTransactionSystem(size_t transaction_id);
  TransactionRecord GetTransaction(size_t user_id, size_t transaction_id);
  TransactionRecord GetTransactionSystem(size_t transaction_id);
  std::vector<TransactionRecord> GetUserTransactions(size_t user_id) const;
  ~TransactionManager() {};
};

#endif