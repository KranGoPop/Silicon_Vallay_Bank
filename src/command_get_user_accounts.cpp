#include <sstream>
#include <memory>
#include "command_get_user_accounts.h"
#include "error.h"
#include "enums.h"

CommandGetUserAccounts::CommandGetUserAccounts(size_t user_id) {
  user_id_ = user_id;
}

void CommandGetUserAccounts::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "SELECT account_id, account_type, amount FROM accounts WHERE user_id = ";
    query << user_id_;
    query << ';';

    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query.str()));

    while (res->next()) {
      accounts_.push_back(AccountInfo(
        bank_id_,
        res->getDouble("amount"),
        res->getUInt("account_id"),
        user_id_,
        StrAccountType(res->getString("account_type"))
      ));
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}

std::vector<AccountInfo> CommandGetUserAccounts::GetAccounts() const {
  return accounts_;
}