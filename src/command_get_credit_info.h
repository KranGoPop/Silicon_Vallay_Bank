#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"
#include "credit_account_info.h"

#ifndef COMMAND_GET_CREDIT_INFO_H
#define COMMAND_GET_CREDIT_INFO_H

class CommandGetCreditInfo : public DBCommand {
  CreditAccountInfo credit_info_;
  AccountInfo acc_info_;
  size_t acc_id_;
public:
  CommandGetCreditInfo(size_t acc_id, AccountInfo acc_info);
  void Execute(sql::Statement& stm) override;
  CreditAccountInfo GetInfo() const;
};

#endif