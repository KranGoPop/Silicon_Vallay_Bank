#include <mysql/jdbc.h>
#include <cstdint>
#include <string>
#include "db_command.h"

#ifndef COMMAND_CHANGE_PASSWORD_H
#define COMMAND_CHANGE_PASSWORD_H

class CommandChangePassword : public DBCommand {
private:
  size_t user_id_;
  std::string new_password_;
public:
  CommandChangePassword(size_t user_id, std::string new_password);
  void Execute(sql::Statement& stm);
};

#endif