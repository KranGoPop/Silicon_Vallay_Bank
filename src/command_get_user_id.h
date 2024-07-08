#include <string>
#include <cstdint>
#include <memory>
#include "db_command.h"
#include "index.h"

#ifndef COMMAND_GET_USER_ID
#define COMMAND_GET_USER_ID

class CommandGetUserId : public DBCommand {
private:
  std::string login_;
  size_t user_id_;
public:
  CommandGetUserId(std::string login);
  void Execute(sql::Statement& stm);
  size_t GetUserId() const;
};

#endif