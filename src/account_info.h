#include <cstdint>
#include "enums.h"

#ifndef HEADER__IACCOUNTINFO_H_
#define HEADER__IACCOUNTINFO_H_

class AccountInfo {
protected:
  double balance_;
  size_t account_id_;
  size_t user_id_;
  size_t bank_id_;
  AccountType account_type_;
public:
  AccountInfo();
  AccountInfo(size_t bank_id, double balance, size_t accout_id, size_t user_id, AccountType account_type);
  AccountInfo& operator=(const AccountInfo& copy) = default;
  const double GetBalance() const;
  const size_t GetAccountId() const;
  const size_t GetUserId() const;
  const size_t GetBankId() const;
  const AccountType GetAccountType() const;
};

#endif //HEADER__IACCOUNTINFO_H_
