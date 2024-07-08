#include <sstream>
#include <memory>
#include "command_get_user_id.h"
#include "error.h"
#include "bank.h"
#include "user.h"
#include "user_info.h"

CommandGetUserId::CommandGetUserId(std::string login) {
  login_ = login;
  user_id_ = 0;
}

void CommandGetUserId::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "SELECT user_id FROM users WHERE login = '";
    query << login_;
    query << "' and bank_id = ";
    query << bank_id_;
    query << ';';

    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query.str()));

    if (res.get()->rowsCount() == 0) {
      throw ApplicationError(kNotSuchUser, "No match user with entered login");
    }

    while (res->next()) {
      user_id_ = res->getUInt("user_id");
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, err.getSQLState());
  }
}

size_t CommandGetUserId::GetUserId() const {
  return user_id_;
}