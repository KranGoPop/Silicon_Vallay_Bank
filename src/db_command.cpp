#include "db_command.h"
#include "bank.h"

void DBCommand::SetBankId(size_t bank_id) {
  bank_id_ = bank_id;
}

//void DBCommand::SetBank(Bank* bank) {
//  bank_ = bank;
//}