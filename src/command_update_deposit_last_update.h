#include <mysql/jdbc.h>
#include <chrono>
#include <cstdint>
#include "db_command.h"

#ifndef COMMAND_UPDATE_DEPOSIT_LAST_UPDATE
#define COMMAND_UPDATE_DEPOSIT_LAST_UPDATE

using namespace std::chrono;

class CommandUpdateDepositLastUpdate : public DBCommand {
private:
  size_t acc_id_;
  system_clock::time_point last_update_;
public:
  CommandUpdateDepositLastUpdate(size_t acc_id, system_clock::time_point last_update);
  void Execute(sql::Statement& stm) override;
};

#endif
