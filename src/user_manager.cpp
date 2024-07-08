#include <cstdint>
#include <stdexcept>
#include <string>
#include <memory>
#include "user_manager.h"
#include "user.h"
#include "password_manager.h"
#include "bank.h"
#include "error.h"
#include "db_manager.h"
#include "command_add_user.h"
#include "command_check_user_exist.h"
#include "command_add_user_info.h"
#include "command_get_user_id.h"
#include "command_get_user_info.h"
#include "command_change_login.h"
#include "command_delete_user.h"
#include "command_delete_user_info.h"

//UserManager::UserManager() : bank_(Bank()) {
//  users_ = std::vector<std::shared_ptr<User>>();
//  passwords_ = std::vector<std::shared_ptr<PasswordManager>>();
//  logins_ = std::unordered_map<std::string, UserID>();
//}
UserManager::UserManager(Bank& bank) : bank_(bank) {
}

std::shared_ptr<User> UserManager::AuthenticateUser(std::string login, std::string password) {
  if (!LoginExistSystem(login)) {
    throw ApplicationError(kNotSuchUser, "No match user with entered login");
  }

  auto user_id_comm = std::shared_ptr<CommandGetUserId>(new CommandGetUserId(login));
  bank_.GetDBManager()->SendExecutable(user_id_comm);
  size_t user_id = user_id_comm->GetUserId();

  if (!GetPasswordManager(user_id)->IsPasswordCorrect(password)) {
    throw ApplicationError(kIncorrectPass, "Incorrect password");
  }

  auto user_info = std::shared_ptr<CommandGetUserInfo>(new CommandGetUserInfo(user_id));
  bank_.GetDBManager()->SendExecutable(user_info);
  return std::shared_ptr<User>(new User(
    bank_, user_id, user_info->GetName(),
    user_info->GetSurname(), user_info->GetAddress(),
    user_info->GetPassport()
  ));
}

std::shared_ptr<User> UserManager::GetUser(size_t user_id) {
  auto user_info = std::shared_ptr<CommandGetUserInfo>(new CommandGetUserInfo(user_id));
  bank_.GetDBManager()->SendExecutable(user_info);
  return std::shared_ptr<User>(new User(
    bank_, user_id, user_info->GetName(),
    user_info->GetSurname(), user_info->GetAddress(),
    user_info->GetPassport()
  ));
}

std::shared_ptr<PasswordManager> UserManager::GetPasswordManager(size_t user_id) {
  return std::shared_ptr<PasswordManager>(new PasswordManager(bank_, user_id));
}

bool UserManager::DeleteUser(size_t user_id) {
  auto delete_user = std::shared_ptr<CommandDeleteUser>(new CommandDeleteUser(user_id));
  bank_.GetDBManager()->SendExecutable(delete_user);
  auto delete_user_info = std::shared_ptr<CommandDeleteUserInfo>(new CommandDeleteUserInfo(user_id));
  bank_.GetDBManager()->SendExecutable(delete_user_info);

  return true;
}

bool UserManager::AddUser(std::string login, std::string password) {
  auto check_user = std::shared_ptr<CommandCheckUserExist>(new CommandCheckUserExist(login));
  bank_.GetDBManager()->SendExecutable(check_user);
  if (!check_user->IsExist()) {
    auto add_user = std::shared_ptr<CommandAddUser>(new CommandAddUser(login, password));
    bank_.GetDBManager()->SendExecutable(add_user);
    auto comm_user_id = std::shared_ptr<CommandGetUserId>(new CommandGetUserId(login));
    bank_.GetDBManager()->SendExecutable(comm_user_id);
    auto add_info = std::shared_ptr<CommandAddUserInfo>(new CommandAddUserInfo(comm_user_id->GetUserId()));
    bank_.GetDBManager()->SendExecutable(add_info);
  }
  else {
    throw ApplicationError(kLoginExist, "User with this login exist");
  }

  return true;
}

bool UserManager::LoginExistSystem(std::string login) const {
  auto user_exist = std::shared_ptr<CommandCheckUserExist>(new CommandCheckUserExist(login));
  bank_.GetDBManager()->SendExecutable(user_exist);
  return user_exist->IsExist();
}

bool UserManager::ChangeLogin(std::string current_login, std::string new_login) {
  auto check_user = std::shared_ptr<CommandCheckUserExist>(new CommandCheckUserExist(current_login));
  bank_.GetDBManager()->SendExecutable(check_user);
  auto check_new_login = std::shared_ptr<CommandCheckUserExist>(new CommandCheckUserExist(new_login));
  bank_.GetDBManager()->SendExecutable(check_new_login);

  if (check_user->IsExist()) {
    if (check_new_login->IsExist()) {
      throw ApplicationError(kLoginExist, "User with this login exist");
    }

    auto user = std::shared_ptr<CommandGetUserId>(new CommandGetUserId(current_login));
    bank_.GetDBManager()->SendExecutable(user);
    auto change_login = std::shared_ptr<CommandChangeLogin>(new CommandChangeLogin(user->GetUserId(), new_login));
    bank_.GetDBManager()->SendExecutable(change_login);
  }
  else {
    throw ApplicationError(kNotSuchUser, "No match user with entered login");
  }
  
  return true;
}