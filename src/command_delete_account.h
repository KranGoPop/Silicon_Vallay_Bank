#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"

#ifndef COMMAND_DELETE_ACCOUNT_H
#define COMMAND_DELETE_ACCOUNT_H

class CommandDeleteAccount : public DBCommand {
private:
  size_t acc_id_;
public:
  CommandDeleteAccount(size_t acc_id);
  void Execute(sql::Statement& stm) override;
};

#endif