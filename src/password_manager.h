#include <string>
#include <utility>
#include <cstdint>
#include "index.h"

#ifndef SRC__PASSWORD_MANAGER_H_
#define SRC__PASSWORD_MANAGER_H_

class PasswordManager {
 private:
  Bank &bank_;
  size_t user_id_;
 public:
  PasswordManager() = default;
  PasswordManager(Bank &bank, size_t user_id);
  PasswordManager &operator=(const PasswordManager &pass_man) = default;
  bool IsPasswordCorrect(std::string password) const;
  bool ChangePassword(std::string new_password, std::string old_password);
};

#endif //SRC__PASSWORD_MANAGER_H_
