#include <sstream>
#include <chrono>
#include "command_add_transaction_record.h"
#include "error.h"
#include "enums.h"

using namespace std::chrono;

CommandAddTransactionRecrod::CommandAddTransactionRecrod(TransactionRecord record) : record_(record) {
}

void CommandAddTransactionRecrod::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "INSERT INTO transactions(bank_id, source_acc_type, dest_acc_type, action_type, trans_type, ";
    query << "trans_time, user_recip_id, user_sender_id, amount, src_acc_id, dest_acc_id) VALUES(";
    query << bank_id_ << ", '";
    query << AccountTypeStr(record_.GetAccountSrcType()) << "', '";
    query << AccountTypeStr(record_.GetAccountDestType()) << "', '";
    query << ActionTypeStr(record_.GetActionType()) << "', '";
    query << TransactionTypeStr(record_.GetTransactionType()) << "', ";
    query << record_.GetTime().time_since_epoch().count() << ", ";
    query << record_.GetUserIdRecipient() << ", ";
    query << record_.GetUserIdSender() << ", ";
    query << record_.GetAmount() << ", ";
    query << record_.GetSourceAccId() << ", ";
    query << record_.GetDestAccId();
    query << ");";
    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}