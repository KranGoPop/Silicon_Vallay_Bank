#include <sstream>
#include "command_update_deposit_last_update.h"
#include "error.h"

CommandUpdateDepositLastUpdate::CommandUpdateDepositLastUpdate(size_t acc_id, system_clock::time_point last_update) {
  acc_id_ = acc_id;
  last_update_ = last_update;
}

void CommandUpdateDepositLastUpdate::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "UPDATE deposit_accounts SET last_update = ";
    query << last_update_.time_since_epoch().count();
    query << " WHERE account_id = ";
    query << acc_id_;
    query << ';';

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}