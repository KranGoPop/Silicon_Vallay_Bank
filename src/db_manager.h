#include <memory>
#include <mysql/jdbc.h>
#include <cstdint>
#include "index.h"

#ifndef DB_MANAGER_H
#define DB_MANAGER_H

class DBManager {
private:
  size_t bank_id_;
  std::shared_ptr<sql::Statement> stm_;
public:
  DBManager(size_t bank_id, std::shared_ptr<sql::Statement> stm);
  void SendExecutable(std::shared_ptr<DBCommand> command);
  ~DBManager() {};
};

#endif