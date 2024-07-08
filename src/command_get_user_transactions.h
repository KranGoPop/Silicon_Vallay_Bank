#include <mysql/jdbc.h>
#include <cstdint>
#include <vector>
#include "db_command.h"
#include "transaction_record.h"

#ifndef COMMAND_GET_USER_TRANSACTIONS_H
#define COMMAND_GET_USER_TRANSACTIONS_H

class CommandGetUserTransaction : public DBCommand {
private:
  size_t user_id_;
  std::vector<TransactionRecord> records_;
public:
  CommandGetUserTransaction(size_t user_id);
  void Execute(sql::Statement& stm) override;
  std::vector<TransactionRecord> GetRecords() const;
};

#endif