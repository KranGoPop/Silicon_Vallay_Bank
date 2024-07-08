#include <sstream>
#include <string>
#include <memory>
#include "command_change_login.h"
#include "error.h"

CommandChangeLogin::CommandChangeLogin(size_t user_id, std::string new_login) {
  user_id_ = user_id;
  new_login_ = new_login;
}

void CommandChangeLogin::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "UPDATE users SET login = '";
    query << new_login_;
    query << "' WHERE user_id = ";
    query << user_id_;
    query << ';';

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}