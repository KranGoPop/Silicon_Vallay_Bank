#include <mysql/jdbc.h>
#include <string>
#include "db_command.h"

#ifndef COMMAND_CHECK_USER_EXIST_H
#define COMMAND_CHECK_USER_EXIST_H

class CommandCheckUserExist : public DBCommand {
private:
  std::string login_;
  bool exist_;
public:
  CommandCheckUserExist(std::string login);
  void Execute(sql::Statement& stm);
  bool IsExist() const;
};

#endif