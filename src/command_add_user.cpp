#include <sstream>
#include <memory>
#include <cstdint>
#include "command_add_user.h"
#include "error.h"

CommandAddUser::CommandAddUser(std::string login, std::string password) {
  login_ = login;
  password_ = password;
}

void CommandAddUser::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "INSERT INTO users(bank_id, login, password) VALUES(";
    query << bank_id_;
    query << ", '";
    query << login_;
    query << "', SHA2('";
    query << password_;
    query << "', 256));";

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}