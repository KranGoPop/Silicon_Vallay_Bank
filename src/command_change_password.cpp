#include <sstream>
#include "command_change_password.h"
#include "error.h"

CommandChangePassword::CommandChangePassword(size_t user_id, std::string new_password) {
  user_id_ = user_id;
  new_password_ = new_password;
}

void CommandChangePassword::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "UPDATE users SET password = SHA2('";
    query << new_password_;
    query << "', 256) WHERE user_id = ";
    query << user_id_;
    query << ';';

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}