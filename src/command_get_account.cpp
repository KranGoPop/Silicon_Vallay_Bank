#include <sstream>
#include <memory>
#include "command_get_account.h"
#include "error.h"
#include "enums.h"

CommandGetAccount::CommandGetAccount(size_t acc_id) {
  acc_id_ = acc_id;
  is_user_ = false;
  user_id_ = 0;
}

CommandGetAccount::CommandGetAccount(size_t user_id, size_t acc_id) {
  acc_id_ = acc_id;
  user_id_ = user_id;
  is_user_ = true;
}

void CommandGetAccount::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "SELECT bank_id, user_id, account_type, amount FROM accounts WHERE account_id = ";
    query << acc_id_;
    query << ';';

    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query.str()));

    if (res->rowsCount() == 0) {
      throw ApplicationError(kAccountIdNotFound, "Account id is not found");
    }

    while (res->next()) {
      if (is_user_ && res->getUInt("user_id") != user_id_) {
        throw ApplicationError(kAccountAccessDenied, " You can't access this account");
      }

      acc_info_ = AccountInfo(
        res->getUInt("bank_id"),
        res->getDouble("amount"),
        acc_id_,
        res->getUInt("user_id"),
        StrAccountType(res->getString("account_type"))
      );
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}

AccountInfo CommandGetAccount::GetInfo() const {
  return acc_info_;
}