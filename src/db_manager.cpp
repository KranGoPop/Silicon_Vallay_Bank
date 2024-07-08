#include "db_manager.h"
#include "bank.h"
#include "db_command.h"
#include "error.h"

DBManager::DBManager(size_t bank_id, std::shared_ptr<sql::Statement> stm) : bank_id_(bank_id)/*, bank_(bank)*/ {
  bank_id_ = bank_id;
  stm_ = stm;
}

void DBManager::SendExecutable(std::shared_ptr<DBCommand> command) {
  command->SetBankId(bank_id_);
  command->Execute(*stm_);
}