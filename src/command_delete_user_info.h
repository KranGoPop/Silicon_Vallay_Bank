#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"

#ifndef COMMAND_DELETE_USER_INFO_H
#define COMMAND_DELETE_USER_INFO_H

class CommandDeleteUserInfo : public DBCommand {
private:
  size_t user_id_;
public:
  CommandDeleteUserInfo(size_t user_id);
  void Execute(sql::Statement& stm);
};

#endif