#include <sstream>
#include "command_update_balance.h"
#include "error.h"

CommandUpdateBalance::CommandUpdateBalance(size_t acc_id, double amount) {
  acc_id_ = acc_id;
  amount_ = amount;
}

void CommandUpdateBalance::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "UPDATE accounts SET amount = ";
    query << amount_;
    query << " WHERE account_id = ";
    query << acc_id_;
    query << ';';
    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}