#include <sstream>
#include <memory>
#include "command_check_user_exist.h"
#include "error.h"

CommandCheckUserExist::CommandCheckUserExist(std::string login) {
  login_ = login;
  exist_ = false;
}

void CommandCheckUserExist::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "SELECT user_id FROM users WHERE login = '";
    query << login_;
    query << "' AND bank_id = ";
    query << bank_id_;
    query << ';';

    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query.str()));

    if (res->rowsCount() != 0) {
      exist_ = true;
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}

bool CommandCheckUserExist::IsExist() const {
  return exist_;
}