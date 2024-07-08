#include <sstream>
#include "command_delete_user.h"
#include "error.h"

CommandDeleteUser::CommandDeleteUser(size_t user_id) {
  user_id_ = user_id;
}

void CommandDeleteUser::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "DELETE FROM users WHERE user_id = ";
    query << user_id_;
    query << ';';

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}