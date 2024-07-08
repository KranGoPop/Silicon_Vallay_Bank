#include <sstream>
#include <chrono>
#include "command_add_credit_info.h"
#include "error.h"

using namespace std::chrono;

CommandAddCreditInfo::CommandAddCreditInfo(size_t acc_id) {
  account_id_ = acc_id;
  start_date_ = system_clock::now();
  last_update_ = start_date_;
}

void CommandAddCreditInfo::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "INSERT INTO credit_accounts(account_id, credit_limit, commision, percent, start_time, credit_cycle, last_update) VALUES(";
    query << account_id_ << ", ";
    query << credit_limit_ << ", ";
    query << commission_ << ", ";
    query << percent_ << ", ";
    query << start_date_.time_since_epoch().count() << ", ";
    query << credit_cycle_.count() << ", ";
    query << last_update_.time_since_epoch().count() << ");";

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}