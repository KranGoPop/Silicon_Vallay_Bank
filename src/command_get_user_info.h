#include <mysql/jdbc.h>
#include <cstdint>
#include <string>
#include "db_command.h"
#include "user_info.h"

#ifndef COMMAND_GET_USER_INFO_H
#define COMMAND_GET_USER_INFO_H

class CommandGetUserInfo : public DBCommand {
private:
  std::string name_;
  std::string surname_;
  std::string address_;
  size_t passport_;
  size_t user_id_;
public:
  CommandGetUserInfo(size_t user_id);
  void Execute(sql::Statement& stm);
  std::string GetName() const;
  std::string GetSurname() const;
  std::string GetAddress() const;
  size_t GetPassport() const;
};

#endif