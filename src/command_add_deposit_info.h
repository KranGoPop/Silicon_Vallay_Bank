#include <mysql/jdbc.h>
#include <chrono>
#include <cstdint>
#include "db_command.h"

#ifndef COMMAND_ADD_DEPOSIT_INFO_H
#define COMMAND_ADD_DEPOSIT_INFO_H

using namespace std::chrono;

class CommandAddDepositInfo : public DBCommand {
private:
  size_t acc_id_;
  system_clock::time_point start_date_;
  seconds widthdraw_timeout_;
  seconds manage_timeout_;
  double percent_;
  int count_of_cycles_;
  system_clock::time_point last_update_;
public:
  CommandAddDepositInfo(size_t acc_id, seconds withdraw_timeout, seconds manage_timeout, double percent, int cycle_count);
  void Execute(sql::Statement& stm) override;
};

#endif