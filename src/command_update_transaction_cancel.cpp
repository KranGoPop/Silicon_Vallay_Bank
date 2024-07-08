#include <sstream>
#include "command_update_transaction_cancel.h"
#include "error.h"

CommandUpdateTransactionCancel::CommandUpdateTransactionCancel(size_t trans_id) {
  trans_id_ = trans_id;
}

void CommandUpdateTransactionCancel::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "UPDATE transactions SET canceled = true WHERE transaction_id = ";
    query << trans_id_;
    query << ';';

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}