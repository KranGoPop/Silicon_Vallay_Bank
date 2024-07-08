#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"

#ifndef COMMAND_DELETE_USER_H
#define COMMAND_DELETE_USER_H

class CommandDeleteUser : public DBCommand {
private:
  size_t user_id_;
public:
  CommandDeleteUser(size_t user_id);
  void Execute(sql::Statement& stm);
};

#endif