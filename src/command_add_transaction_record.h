#include <mysql/jdbc.h>
#include "transaction_record.h"
#include "db_command.h"

#ifndef COMMAND_ADD_TRANSACTION_RECORD_H
#define COMMAND_ADD_TRANSACTION_RECORD_H

class CommandAddTransactionRecrod : public DBCommand {
private:
  TransactionRecord record_;
public:
  CommandAddTransactionRecrod(TransactionRecord record);
  void Execute(sql::Statement& stm) override;
};

#endif