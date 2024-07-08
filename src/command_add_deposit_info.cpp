#include <sstream>
#include "command_add_deposit_info.h"
#include "error.h"

CommandAddDepositInfo::CommandAddDepositInfo(size_t acc_id, seconds withdraw_timeout, seconds manage_timeout, double percent, int cycle_count) {
  acc_id_ = acc_id;
  widthdraw_timeout_ = withdraw_timeout;
  manage_timeout_ = manage_timeout;
  percent_ = percent;
  count_of_cycles_ = cycle_count;
  start_date_ = system_clock::now();
  last_update_ = start_date_;
}

void CommandAddDepositInfo::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "INSERT INTO deposit_accounts(account_id, start_time, withdraw_timeout, manage_timeout, percent, cycle_count, last_update) VALUES(";
    query << acc_id_ << ", ";
    query << start_date_.time_since_epoch().count() << ", ";
    query << widthdraw_timeout_.count() << ", ";
    query << manage_timeout_.count() << ", ";
    query << percent_ << ", ";
    query << count_of_cycles_ << ", ";
    query << last_update_.time_since_epoch().count() << ");";

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}