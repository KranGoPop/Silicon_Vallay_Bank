#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"
#include "transaction_record.h"

#ifndef COMMAND_GET_TRANSACTION_H

class CommandGetTransaction : public DBCommand {
private:
  TransactionRecord record_;
  size_t trans_id_;
  size_t user_id_;
  bool is_user_;
public:
  CommandGetTransaction(size_t trans_id);
  CommandGetTransaction(size_t user_id, size_t trans_id);
  void Execute(sql::Statement& stm) override;
  TransactionRecord GetRecord() const;
};

#endif