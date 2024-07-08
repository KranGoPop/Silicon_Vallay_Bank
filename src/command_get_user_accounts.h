#include <mysql/jdbc.h>
#include <vector>
#include <cstdint>
#include "db_command.h"
#include "account_info.h"

#ifndef COMMAND_GET_USER_ACCOUNTS_H
#define COMMAND_GET_USER_ACCOUNTS_H

class CommandGetUserAccounts : public DBCommand {
private:
  size_t user_id_;
  std::vector<AccountInfo> accounts_;
public:
  CommandGetUserAccounts(size_t user_id);
  void Execute(sql::Statement& stm) override;
  std::vector<AccountInfo> GetAccounts() const;
};

#endif