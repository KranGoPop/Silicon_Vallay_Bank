#include <sstream>
#include <memory>
#include <chrono>
#include "command_get_transaction.h"
#include "error.h"
#include "enums.h"

using namespace std::chrono;

CommandGetTransaction::CommandGetTransaction(size_t trans_id) {
  trans_id_ = trans_id;
  user_id_ = 0;
  is_user_ = false;
}

CommandGetTransaction::CommandGetTransaction(size_t user_id, size_t trans_id) {
  trans_id_ = trans_id;
  user_id_ = user_id;
  is_user_ = true;
}

void CommandGetTransaction::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "SELECT bank_id, transaction_id, source_acc_type, dest_acc_type, action_type, trans_type, trans_time, user_recip_id, user_sender_id";
    query << ", amount, src_acc_id, dest_acc_id, canceled FROM transactions WHERE transaction_id = ";
    query << trans_id_;
    query << ';';

    size_t bank_id = 0, trans_id = 0, user_src_id = 0, user_dest_id = 0, acc_src_id = 0, acc_dest_id = 0;
    bool canceled = false;
    AccountType acc_src_type = kDebit, acc_dest_type = kDebit;
    ActionType action_type = kDepositMoney;
    TransactionType trans_type = kCancel;
    system_clock::time_point time;
    double amount = 0;

    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query.str()));

    if (res->rowsCount() == 0) {
      throw ApplicationError(kNotSuchRecord, "No match record");
    }

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
    }

   /* if (user_src_id != user_id_ && user_dest_id != user_id_) {
      throw ApplicationError(kRecordAccessDenied, "This record not yours");
    }*/

    record_ = TransactionRecord(
      bank_id, acc_src_type, acc_dest_type, action_type, trans_type, trans_id, user_dest_id, user_src_id, amount, acc_src_id, acc_dest_id, canceled
    );
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}

TransactionRecord CommandGetTransaction::GetRecord() const {
  return record_;
}