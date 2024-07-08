#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"

#ifndef COMMAND_UPDATE_TRANSACTION_CANCEL_H
#define COMMAND_UPDATE_TRANSACTION_CANCEL_H

class CommandUpdateTransactionCancel : public DBCommand {
private:
  size_t trans_id_;
public:
  CommandUpdateTransactionCancel(size_t trans_id);
  void Execute(sql::Statement& stm) override;
};

#endif