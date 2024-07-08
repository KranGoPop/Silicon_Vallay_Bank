#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"

#ifndef COMMAND_UPDATE_BALANCE_H
#define COMMAND_UPDATE_BALANCE_H

class CommandUpdateBalance : public DBCommand {
private:
  double amount_;
  size_t acc_id_;
public:
  CommandUpdateBalance(size_t acc_id, double amount);
  void Execute(sql::Statement& stm) override;
};

#endif