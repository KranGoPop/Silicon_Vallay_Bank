#include <string>
#include <mysql/jdbc.h>
#include <cstdint>
#include "db_command.h"

#ifndef COMMAND_CHECK_PASSWORD_H
#define COMMAND_CHECK_PASSWORD_H

class CommandCheckPassword : public DBCommand {
private:
  std::string password_;
  size_t user_id_;
  bool password_correct_;
public:
  CommandCheckPassword(size_t user_id, std::string password);
  void Execute(sql::Statement& stm);
  bool GetAnswer() const;
};

#endif