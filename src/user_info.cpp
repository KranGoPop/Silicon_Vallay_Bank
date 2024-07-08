#include <iostream>
#include <string>
#include <memory>
#include "user_info.h"
#include "bank.h"
#include "db_manager.h"
#include "command_update_user_info.h"

void UserInfo::SetTrusted() {
  if (!name_.empty() && !surname_.empty() && !address_.empty() && passport_ != 0) {
    trusted_ = true;
  } else {
    trusted_ = false;
  }
}

void UserInfo::SendUpdate() const {
  auto update_info = std::shared_ptr<CommandUpdateUserInfo>(new CommandUpdateUserInfo(
    user_id_,
    name_,
    surname_,
    address_,
    passport_
  ));
  bank_.GetDBManager()->SendExecutable(update_info);
}

UserInfo::UserInfo(Bank& bank, size_t user_id) : bank_(bank), user_id_(user_id) {
  user_id_ = 0;
  name_ = "";
  surname_ = "";
  address_ = "";
  passport_ = 0;
  SetTrusted();
}

UserInfo::UserInfo(Bank& bank, size_t user_id, std::string name, std::string surname, std::string address, size_t passport) : bank_(bank) {
  user_id_ = user_id;
  name_ = name;
  surname_ = surname;
  address_ = address;
  passport_ = passport;
  SetTrusted();
}

std::string UserInfo::GetName() const {
  return name_;
}

std::string UserInfo::GetSurname() const {
  return surname_;
}

std::string UserInfo::GetAddress() const {
  return address_;
}

size_t UserInfo::GetPassport() const {
  return passport_;
}

void UserInfo::SetName(std::string name) {
  name_ = name;
  SetTrusted();
  SendUpdate();
}

void UserInfo::SetSurname(std::string surname) {
  surname_ = surname;
  SetTrusted();
  SendUpdate();
}

void UserInfo::SetAddress(std::string address) {
  address_ = address;
  SetTrusted();
  SendUpdate();
}

void UserInfo::SetPassport(size_t passport) {
  passport_ = passport;
  SetTrusted();
  SendUpdate();
}

bool UserInfo::IsTrusted() const {
  return trusted_;
}