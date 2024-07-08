#include <memory>
#include <mysql/jdbc.h>
#include "index.h"

#ifndef DB_COMMAND_H
#define DB_COMMAND_H

class DBCommand {
protected:
  size_t bank_id_ = 0;
  //Bank* bank_ = nullptr;
public:
  virtual void Execute(sql::Statement& stm) = 0;
  void SetBankId(size_t bank_id);
  //void SetBank(Bank* bank);
  ~DBCommand() {};
};

#endif