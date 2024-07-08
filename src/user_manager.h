#include <vector>
#include <unordered_map>
#include <memory>
#include "index.h"

#ifndef USER_MANAGER_H
#define USER_MANAGER_H

typedef size_t UserID;

class UserManager {
 private:
  Bank &bank_;
  bool LoginExistSystem(std::string login) const;
 public:
  //UserManager();
  UserManager(Bank& bank);
  UserManager& operator=(const UserManager& copy) = default;
  std::shared_ptr<User> AuthenticateUser(std::string login, std::string password);
  std::shared_ptr<User> GetUser(size_t user_id);
  std::shared_ptr<PasswordManager> GetPasswordManager(size_t user_id);
  bool AddUser(std::string login, std::string password);
  bool DeleteUser(size_t user_id);
  bool ChangeLogin(std::string current_login, std::string new_login);
  ~UserManager() {};
};

#endif //SRC__ACCOUNT_MANAGER_H_
