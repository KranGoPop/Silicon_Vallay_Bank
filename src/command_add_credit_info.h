#include <mysql/jdbc.h>
#include <cstdint>
#include <chrono>
#include "db_command.h"

#ifndef COMMAND_ADD_CREDIT_INFO_H
#define COMMAND_ADD_CREDIT_INFO_H

using namespace std::chrono;

class CommandAddCreditInfo : public DBCommand {
private:
  size_t account_id_;
  double credit_limit_ = 1e5;
  double commission_ = 1.2;
  double percent_ = 0.1;
  system_clock::time_point start_date_;
  seconds credit_cycle_ = 10s;
  system_clock::time_point last_update_;
public:
  CommandAddCreditInfo(size_t acc_id);
  void Execute(sql::Statement& stm) override;
};

#endif