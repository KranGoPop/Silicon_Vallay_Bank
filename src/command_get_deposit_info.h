#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"
#include "deposit_account_info.h"

#ifndef COMMAND_GET_DEPOSIT_INFO_H
#define COMMAND_GET_DEPOSIT_INFO_H

class CommandGetDepositInfo : public DBCommand {
private:
  size_t acc_id_;
  AccountInfo acc_info_;
  DepositAccountInfo depos_info_;
public:
  CommandGetDepositInfo(size_t acc_id, AccountInfo acc_info);
  void Execute(sql::Statement& stm) override;
  DepositAccountInfo GetInfo() const;
};

#endif