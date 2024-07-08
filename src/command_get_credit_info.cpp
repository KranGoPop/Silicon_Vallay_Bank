#include <sstream>
#include <memory>
#include "command_get_credit_info.h"
#include "error.h"

CommandGetCreditInfo::CommandGetCreditInfo(size_t acc_id, AccountInfo acc_info) : acc_info_(acc_info) {
  acc_id_ = acc_id;
}

void CommandGetCreditInfo::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "SELECT user_id, credit_limit, commision, percent, start_time, credit_cycle, last_update FROM credit_accounts, accounts WHERE credit_accounts.account_id = ";
    query << acc_id_;
    query << ';';

    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query.str()));

    while (res->next()) {
      credit_info_ = CreditAccountInfo(
        bank_id_,
        acc_info_.GetBalance(),
        acc_info_.GetAccountId(),
        res->getUInt("user_id"),
        system_clock::time_point(system_clock::duration(res->getUInt64("start_time"))),
        res->getDouble("credit_limit"),
        res->getDouble("commision"),
        res->getDouble("percent"),
        seconds(res->getInt("credit_cycle")),
        system_clock::time_point(system_clock::duration(res->getUInt64("last_update")))
      );
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}

CreditAccountInfo CommandGetCreditInfo::GetInfo() const {
  return credit_info_;
}