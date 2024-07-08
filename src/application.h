#include <mysql/jdbc.h>
#include <memory>
#include <cstdint>
#include <vector>
#include "index.h"
#include "bank_info.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class Application {
private:
  std::shared_ptr<sql::Connection> conn_;
  std::shared_ptr<sql::Statement> stm_;
public:
  Application();
  std::shared_ptr<Bank> GetBank(std::string name);
  std::shared_ptr<Bank> GetBank(size_t bank_id);
  std::vector<BankInfo> GetBanks();
};

#endif