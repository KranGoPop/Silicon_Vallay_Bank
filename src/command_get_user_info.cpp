#include <sstream>
#include "command_get_user_info.h"
#include "error.h"

CommandGetUserInfo::CommandGetUserInfo(size_t user_id) {
  user_id_ = user_id;
  passport_ = 0;
}

void CommandGetUserInfo::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "SELECT name, surname, address, passport FROM user_info WHERE user_id = ";
    query << user_id_;
    query << ';';

    std::unique_ptr<sql::ResultSet> res(stm.executeQuery(query.str()));

    if (res->rowsCount() == 0) {
      throw ApplicationError(kNotSuchUser, "No such user.");
    }

    while (res->next()) {
      name_ = res->getString("name");
      surname_ = res->getString("surname");
      address_ = res->getString("address");
      passport_ = res->getUInt("passport");
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}

std::string CommandGetUserInfo::GetName() const {
  return name_;
}

std::string CommandGetUserInfo::GetSurname() const {
  return surname_;
}

std::string CommandGetUserInfo::GetAddress() const {
  return address_;
}

size_t CommandGetUserInfo::GetPassport() const {
  return passport_;
}