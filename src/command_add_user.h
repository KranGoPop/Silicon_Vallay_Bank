#include <mysql/jdbc.h>
#include <string>
#include "db_command.h"

#ifndef COMMAND_ADD_USER_H
#define COMMAND_ADD_USER_H

class CommandAddUser : public DBCommand {
private:
  std::string login_;
  std::string password_;
public:
  CommandAddUser(std::string login, std::string password);
  void Execute(sql::Statement& stm);
};

#endif