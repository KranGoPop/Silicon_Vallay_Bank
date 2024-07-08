#include <sstream>
#include <memory>
#include <chrono>
#include "command_get_deposit_info.h"
#include "error.h"

using namespace std::chrono;

CommandGetDepositInfo::CommandGetDepositInfo(size_t acc_id, AccountInfo acc_info) : acc_info_(acc_info) {
  acc_id_ = acc_id;
}

void CommandGetDepositInfo::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "SELECT user_id, start_time, withdraw_timeout, manage_timeout, percent, cycle_count, last_update FROM deposit_accounts, accounts WHERE deposit_accounts.account_id = ";
    query << acc_id_;
    query << ';';

    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query.str()));

    while (res->next()) {
      depos_info_ = DepositAccountInfo(
        bank_id_,
        acc_info_.GetBalance(),
        acc_info_.GetAccountId(),
        res->getUInt("user_id"),
        system_clock::time_point(system_clock::duration(res->getUInt64("start_time"))),
        seconds(res->getInt("withdraw_timeout")),
        seconds(res->getInt("manage_timeout")),
        res->getDouble("percent"),
        res->getInt("cycle_count"),
        system_clock::time_point(system_clock::duration(res->getUInt64("last_update")))
      );
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}

DepositAccountInfo CommandGetDepositInfo::GetInfo() const {
  return depos_info_;
}