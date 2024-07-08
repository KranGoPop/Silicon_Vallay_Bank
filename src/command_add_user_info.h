#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"

#ifndef COMMAND_ADD_USER_INFO_H
#define COMMAND_ADD_USER_INFO_H

class CommandAddUserInfo : public DBCommand {
private:
  size_t user_id_;
public:
  CommandAddUserInfo(size_t user_id);
  void Execute(sql::Statement& stm);
};

#endif