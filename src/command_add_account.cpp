#include <sstream>
#include "command_add_account.h"
#include "error.h"

CommandAddAccount::CommandAddAccount(size_t user_id, AccountType acc_type) {
  user_id_ = user_id;
  account_type_ = acc_type;
  acc_id_ = 0;
}

void CommandAddAccount::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "INSERT INTO accounts(bank_id, user_id, account_type) VALUES(";
    query << bank_id_;
    query << ", ";
    query << user_id_;
    query << ", '";
    query << AccountTypeStr(account_type_);
    query << "');";
    std::stringstream query2;
    query2 << "SELECT MAX(account_id) as mm FROM accounts;";

    stm.execute(query.str());
    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query2.str()));

    while (res->next()) {
      acc_id_ = res->getUInt("mm");
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}

size_t CommandAddAccount::GetAccId() const {
  return acc_id_;
}