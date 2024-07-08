#include <cstdint>
#include "account_info.h"
#include "enums.h"

#ifndef HEADER__DEBITACCOUNTINFO_H_
#define HEADER__DEBITACCOUNTINFO_H_

class DebitAccountInfo : public AccountInfo {
 public:
  DebitAccountInfo(size_t bank_id, double balance, size_t account_id, size_t user_id) : AccountInfo(bank_id, balance, account_id, user_id, AccountType::kDebit) {}
};

#endif //HEADER__DEBITACCOUNTINFO_H_
