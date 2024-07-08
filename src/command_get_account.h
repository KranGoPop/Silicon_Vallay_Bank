#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"
#include "account_info.h"

#ifndef COMMAND_GET_ACCOUNT_H
#define COMMAND_GET_ACCOUNT_H

class CommandGetAccount : public DBCommand {
private:
  AccountInfo acc_info_;
  size_t acc_id_;
  size_t user_id_;
  bool is_user_;
public:
  CommandGetAccount(size_t acc_id);
  CommandGetAccount(size_t user_id, size_t acc_id);
  void Execute(sql::Statement& stm) override;
  AccountInfo GetInfo() const;
};

#endif