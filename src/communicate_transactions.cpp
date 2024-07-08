#include "communicate_transactions.h"
#include "account_manager.h"
#include "transaction_manager.h"
#include "bank.h"
#include "transaction_record.h"

CommunicateTransactions::CommunicateTransactions(Bank &bank, size_t user_id) : bank_(bank) {
  user_id_ = user_id;
}

bool CommunicateTransactions::RequestCanelTransaction(size_t transaction_id) {
  bank_.GetAccountManager()->CancelTransaction(user_id_, transaction_id);
  return true;
}

std::vector<TransactionRecord> CommunicateTransactions::GetTransactionHistory() {
  return bank_.GetTransactionManager()->GetUserTransactions(user_id_);
}