#include <mysql/jdbc.h>
#include <cstdint>
#include <string>
#include "db_command.h"

#ifndef COMMAND_CHANGE_LOGIN_H
#define COMMAND_CHANGE_LOGIN_H

class CommandChangeLogin : public DBCommand {
private:
  size_t user_id_;
  std::string new_login_;
public:
  CommandChangeLogin(size_t user_id, std::string new_login);
  void Execute(sql::Statement& stm);
};

#endif