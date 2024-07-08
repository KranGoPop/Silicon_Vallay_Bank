#include <memory>
#include <sstream>
#include "command_check_password.h"
#include "error.h"

CommandCheckPassword::CommandCheckPassword(size_t user_id, std::string password) {
  password_ = password;
  user_id_ = user_id;
  password_correct_ = false;
}

void CommandCheckPassword::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "SELECT STRCMP(SHA2('";
    query << password_;
    query << "', 256), password) AS cmp FROM users WHERE user_id = ";
    query << user_id_;
    query << ';';
    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query.str()));

    if (res->rowsCount() == 0) {
      throw ApplicationError(kNotSuchUser, "No match user with entered login");
    }

    while (res->next()) {
      password_correct_ = res->getInt("cmp") == 0;
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}

bool CommandCheckPassword::GetAnswer() const {
  return password_correct_;
}