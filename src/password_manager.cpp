#include <memory>
#include "password_manager.h"
#include "bank.h"
#include "error.h"
#include "db_manager.h"
#include "command_check_password.h"
#include "command_change_password.h"

/*PasswordManager::PasswordManager() : bank_(Bank()) {
  user_id_ = 0;
}*/

PasswordManager::PasswordManager(Bank &bank, size_t user_id) : bank_(bank) {
  user_id_ = user_id;
}

bool PasswordManager::IsPasswordCorrect(std::string password) const {
  auto check_pass = std::shared_ptr<CommandCheckPassword>(new CommandCheckPassword(user_id_, password));
  bank_.GetDBManager()->SendExecutable(check_pass);
  return check_pass->GetAnswer();
}

bool PasswordManager::ChangePassword(std::string new_password, std::string old_password) {
  if (!IsPasswordCorrect(old_password)) {
    throw ApplicationError(kIncorrectPass, "Incorrect password");
  }

  auto update_pass = std::shared_ptr<CommandChangePassword>(new CommandChangePassword(user_id_, new_password));
  bank_.GetDBManager()->SendExecutable(update_pass);
  return true;
}