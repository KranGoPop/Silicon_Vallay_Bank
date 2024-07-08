#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"
#include "enums.h"

#ifndef COMMAND_ADD_ACCOUNT_H
#define COMMAND_ADD_ACCOUNT_H

class CommandAddAccount : public DBCommand {
private:
  size_t user_id_;
  AccountType account_type_;
  size_t acc_id_;
public:
  CommandAddAccount(size_t user_id, AccountType acc_type);
  void Execute(sql::Statement& stm) override;
  size_t GetAccId() const;
};

#endif