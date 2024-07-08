#include <cstdint>
#include <vector>
#include <utility>
#include "index.h"
#include "transaction_manager.h"

#ifndef COMMUNICATE_TRANSACTIONS_H
#define COMMUNICATE_TRANSACTIONS_H

class CommunicateTransactions {
 private:
  Bank &bank_;
  size_t user_id_;
 public:
  CommunicateTransactions(Bank &bank, size_t user_id);
  bool RequestCanelTransaction(size_t transaction_id);
  std::vector<TransactionRecord> GetTransactionHistory();
};

#endif