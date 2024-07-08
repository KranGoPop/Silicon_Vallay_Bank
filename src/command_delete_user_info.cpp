#include <sstream>
#include "command_delete_user_info.h"
#include "error.h"

CommandDeleteUserInfo::CommandDeleteUserInfo(size_t user_id) {
  user_id_ = user_id;
}

void CommandDeleteUserInfo::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "DELETE FROM user_info WHERE user_id = ";
    query << user_id_;
    query << ';';

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}