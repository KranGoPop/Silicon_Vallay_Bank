#include <sstream>
#include "command_add_user_info.h"
#include "error.h"

CommandAddUserInfo::CommandAddUserInfo(size_t user_id) {
  user_id_ = user_id;
}

void CommandAddUserInfo::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "INSERT INTO user_info(user_id) values(";
    query << user_id_;
    query << ");";

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}