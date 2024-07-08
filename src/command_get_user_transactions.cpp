#include <sstream>
#include <chrono>
#include "command_get_user_transactions.h"
#include "error.h"
#include "enums.h"

using namespace std::chrono;

CommandGetUserTransaction::CommandGetUserTransaction(size_t user_id) {
  user_id_ = user_id;
}

void CommandGetUserTransaction::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "SELECT bank_id, transaction_id, source_acc_type, dest_acc_type, action_type, trans_type, trans_time, user_recip_id, user_sender_id";
    query << ", amount, src_acc_id, dest_acc_id, canceled FROM transactions WHERE user_recip_id = ";
    query << user_id_;
    query << " OR user_sender_id = ";
    query << user_id_;
    query << ';';

    size_t bank_id = 0, trans_id = 0, user_src_id = 0, user_dest_id = 0, acc_src_id = 0, acc_dest_id = 0;
    bool canceled = false;
    AccountType acc_src_type = kDebit, acc_dest_type = kDebit;
    ActionType action_type = kDepositMoney;
    TransactionType trans_type = kCancel;
    system_clock::time_point time;
    double amount = 0;

    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query.str()));

    while (res->next()) {
      bank_id = res->getUInt("bank_id");
      trans_id = res->getUInt64("transaction_id");
      user_src_id = res->getUInt("user_sender_id");
      user_dest_id = res->getUInt("user_recip_id");
      acc_src_id = res->getUInt("src_acc_id");
      acc_dest_id = res->getUInt("dest_acc_id");
      canceled = res->getBoolean("canceled");
      acc_src_type = StrAccountType(res->getString("source_acc_type"));
      acc_dest_type = StrAccountType(res->getString("dest_acc_type"));
      action_type = StrActionType(res->getString("action_type"));
      trans_type = StrTransactionType(res->getString("trans_type"));
      time = system_clock::time_point(system_clock::duration(res->getUInt64("trans_time")));
      amount = res->getDouble("amount");

      records_.push_back(TransactionRecord(
        bank_id, acc_src_type, acc_dest_type, action_type, trans_type, trans_id, user_dest_id, user_src_id, amount, acc_src_id, acc_dest_id, canceled
      ));
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}

std::vector<TransactionRecord> CommandGetUserTransaction::GetRecords() const {
  return records_;
}