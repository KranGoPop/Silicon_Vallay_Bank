#include <mysql/jdbc.h>
#include <cstdint>
#include <string>
#include "db_command.h"

#ifndef COMMAND_UPDATE_USER_INFO_H
#define COMMAND_UPDATE_USER_INFO_H

class CommandUpdateUserInfo : public DBCommand {
private:
  size_t user_id_;
  std::string name_;
  std::string surname_;
  std::string address_;
  size_t passport_;
public:
  CommandUpdateUserInfo(size_t user_id, std::string name, std::string surname, std::string address, size_t passport);
  void Execute(sql::Statement& stm);
};

#endif