#include <sstream>
#include "command_update_user_info.h"
#include "error.h"

CommandUpdateUserInfo::CommandUpdateUserInfo(size_t user_id, std::string name = "", std::string surname = "", std::string address = "", size_t passport = 0) {
  user_id_ = user_id;
  name_ = name;
  surname_ = surname;
  address_ = address;
  passport_ = passport;
}

void CommandUpdateUserInfo::Execute(sql::Statement& stm) {
  try {
    std::stringstream query;
    query << "UPDATE user_info SET name = '";
    query << name_;
    query << "', surname = '";
    query << surname_;
    query << "', address = '";
    query << address_;
    query << "', passport = ";
    query << passport_;
    query << " WHERE user_id = ";
    query << user_id_;
    query << ";";

    stm.execute(query.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}