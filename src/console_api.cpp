#include <boost/json.hpp>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <memory>
#include <chrono>
#include <string>
#include <map>
#include <time.h>
#include <errno.h>

#include "enums.h"
#include "communicate_account.h"
#include "user.h"
#include "user_info.h"
#include "error.h"
#include "user_manager.h"
#include "password_manager.h"
#include "bank.h"
#include "application.h"
#include "account.h"
#include "account_info.h"
#include "credit_account_info.h"
#include "deposit_account_info.h"
#include "communicate_transactions.h"
#include "transaction_record.h"
#include "bank_info.h"

using namespace std::chrono;
namespace json = boost::json;

std::string GetTime(const system_clock::time_point tp) {
  time_t tp_t = system_clock::to_time_t(tp);
  std::unique_ptr<std::tm> tp_s(new std::tm);
  errno_t err = gmtime_s(tp_s.get(), &tp_t);
  std::stringstream stime;

  if (err != 0) {
    throw ApplicationError(kUnknowError, "Time unknown error");
  }


  stime << tp_s->tm_year + 1900 << '-';

  if (tp_s->tm_mon + 1 < 10) {
    stime << 0 << tp_s->tm_mon + 1;
  }
  else {
    stime << tp_s->tm_mon + 1;
  }

  stime << '-';

  if (tp_s->tm_mday < 10) {
    stime << 0 << tp_s->tm_mday;
  }
  else {
    stime << tp_s->tm_mday;
  }

  stime << 'T';

  if (tp_s->tm_hour < 10) {
    stime << 0 << tp_s->tm_hour;
  }
  else {
    stime << tp_s->tm_hour;
  }

  stime << ':';

  if (tp_s->tm_min < 10) {
    stime << 0 << tp_s->tm_min;
  }
  else {
    stime << tp_s->tm_min;
  }

  stime << ':';

  if (tp_s->tm_sec < 10) {
    stime << 0 << tp_s->tm_sec;
  }
  else {
    stime << tp_s->tm_sec;
  }

  return stime.str();
}


void tag_invoke(const json::value_from_tag&, json::value& json, const UserInfo& user_info) {
  json = {
    {"name", user_info.GetName()},
    {"surname", user_info.GetSurname()},
    {"address", user_info.GetAddress()},
    {"passport", user_info.GetPassport()}
  };
}

void tag_invoke(const json::value_from_tag&, json::value& json, const BankInfo& bank_info) {
  json = {
    {"id", bank_info.GetBankId()},
    {"name", bank_info.GetName()},
    {"city", bank_info.GetCity()}
  };
}


void tag_invoke(const json::value_from_tag&, json::value& json, const std::shared_ptr<Account>& account) {
  std::shared_ptr<AccountInfo> info = account->GetAccountInfo();

  json = {
    {"id", info->GetAccountId()},
    {"type", AccountTypeStrUpper(info->GetAccountType())},
    {"balance", info->GetBalance()}
  };
}

void tag_invoke(const json::value_from_tag&, json::value& json, const std::shared_ptr<AccountInfo>& account_info) {
  json = {
    {"id", account_info->GetAccountId()},
    {"type", AccountTypeStrUpper(account_info->GetAccountType())},
    {"balance", account_info->GetBalance()}
  };
}

void tag_invoke(const json::value_from_tag&, json::value& json, const std::shared_ptr<CreditAccountInfo>& account_info) {
  auto start_date = account_info->GetStartDate();
  auto last_update = account_info->GetLastUpdate();

  json = {
    {"id", account_info->GetAccountId()},
    {"type", AccountTypeStrUpper(account_info->GetAccountType())},
    {"balance", account_info->GetBalance()},
    {"commission",account_info->GetCommission()},
    {"percent", account_info->GetPercent()},
    {"start_date", GetTime(start_date)},
    {"last_update", GetTime(last_update)},
    {"credit_limit", account_info->GetCreditLimit()},
    {"credit_cycle", account_info->GetCreditCycle().count()}
  };
}

void tag_invoke(const json::value_from_tag&, json::value& json, const std::shared_ptr<DepositAccountInfo>& account_info) {
  auto start_date = account_info->GetStartDate();
  auto last_update = account_info->GetLastUpdate();

  double balance = account_info->GetBalance();
  json = {
    {"id", account_info->GetAccountId()},
    {"type", AccountTypeStrUpper(account_info->GetAccountType())},
    {"balance", balance},
    {"percent", account_info->GetPercent()},
    {"start_date", GetTime(start_date)},
    {"last_update", GetTime(last_update)},
    {"manage_timeout", account_info->GetManageTimeout().count()},
    {"withdraw_timeout", account_info->GetWithdrawTimeout().count()}
  };
}

void tag_invoke(const json::value_from_tag&, json::value& json, const TransactionRecord& record) {
  auto record_time = record.GetTime();
  json = {
    {"id", record.GetTransactionId()},
    {"src_acc_type", AccountTypeStrUpper(record.GetAccountSrcType())},
    {"dest_acc_type", AccountTypeStrUpper(record.GetAccountDestType())},
    {"action_type", ActionTypeStrUpper(record.GetActionType())},
    {"time", GetTime(record_time)},
    {"trans_type", TransactionTypeStrUpper(record.GetTransactionType())},
    {"src_user_id", record.GetUserIdSender()},
    {"dest_user_id", record.GetUserIdRecipient()},
    {"src_acc_id", record.GetSourceAccId()},
    {"dest_acc_id", record.GetDestAccId()},
    {"amount", record.GetAmount()},
    {"canceled", record.IsCanceled()}
  };
}

int main(int argc, char* argv[]) {
  /*std::string s = "{\"command\": \"GetTransactionHistory\", \"args\" : { \"bank_id\": 4, \"user_id\" : 3}}";*/
  // Переменные
  Application app;
  std::shared_ptr<User> current_user;
  std::shared_ptr<Bank> current_bank;
  std::map<std::string, std::string> object = { {"status", "error"}, {"error","none"} };
  // Json тема
  json::stream_parser p;
  json::error_code error;
  std::string command;
  json::value val;
  json::value output;

  bool is_error = false;

  try {
    std::string s;
    if (argc == 3 && std::string(argv[1]) == "-json") {
      s = argv[2];
    }
    else {
      throw ApplicationError(kJSONError, "No JSON");
    }
    //s = "{\"command\":\"WithdrawMoney\", \"args\":{\"user_id\": 36, \"bank_id\":4, \"amount\": \"12\", \"account_id\": \"33\"}}";

    p.write(s, error);
    if (error) {
      throw ApplicationError(kJSONError, "JSON Error: Parse");
    }
    p.finish(error);
    if (error) {
      throw ApplicationError(kJSONError, "JSON Error: Parse");
    }

    val = p.release();

    if (val.kind() == json::kind::object) {
      const auto& obj = val.get_object();
      const auto& aa = obj.at("command");
      command = aa.get_string();
      val = obj.at("args");
    }
  }
  catch (std::exception& err) {
    is_error = true;
    output = {
      {"status", "error"},
      {"error", err.what()}
    };
  }
  catch (ApplicationError& err) {
    is_error = true;
    output = {
      {"status", "error"},
      {"error", err.GetDesc()}
    };
  }

  try {
    if (!is_error) {
      if (command == "AuthenticateUser") {
        std::string login;
        std::string password;
        size_t bank;

        try {
          const auto& obj = val.get_object();
          login = obj.at("login").get_string();
          password = obj.at("password").get_string();
          bank = obj.at("bank_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->AuthenticateUser(login, password);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", { {"set", current_user->GetUserId()} } }
        };
      }
      else if (command == "Select_Bank") {
        std::string bank;
        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank").get_string();
        }
        catch (std::exception& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_user.reset();
        current_bank = app.GetBank(bank);
        object["status"] = "success";

        output = {
          {"status", object["status"]},
          {"error", object["error"]},
          {"result", {}},
          {"php_command", { {"set", current_bank->GetBankId()} } }
        };
      }
      else if (command == "AddUser") {
        std::string login;
        std::string password;
        size_t bank;
        try {
          const auto& obj = val.get_object();
          login = obj.at("login").get_string();
          password = obj.at("password").get_string();
          bank = obj.at("bank_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_bank->GetUserManager()->AddUser(login, password);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "DeleteUser") {
        size_t user_id;
        size_t bank;
        try {
          const auto& obj = val.get_object();
          user_id = obj.at("user_id").get_int64();
          bank = obj.at("bank_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_bank->GetUserManager()->DeleteUser(user_id);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "ChangeLogin") {
        std::string curr_login, new_login;
        size_t bank;

        try {
          const auto& obj = val.get_object();
          curr_login = obj.at("curr_login").get_string();
          new_login = obj.at("new_login").get_string();
          bank = obj.at("bank_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_bank->GetUserManager()->ChangeLogin(curr_login, new_login);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "ChangePassword") {
        std::string curr_password, new_password;
        size_t user_id = 0, bank;
        try {
          const auto& obj = val.get_object();
          curr_password = obj.at("curr_password").get_string();
          new_password = obj.at("new_password").get_string();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_bank->GetUserManager()->GetPasswordManager(user_id)->ChangePassword(new_password, curr_password);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "GetUserInfo") {
        size_t user_id;
        size_t bank;
        try {
          const auto& obj = val.get_object();
          user_id = obj.at("user_id").get_int64();
          bank = obj.at("bank_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }
        json::value user_info;

        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        user_info = json::value_from(*current_user->GetUserInfo().get());
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", user_info},
        {"php_command", {}}
        };
      }
      else if (command == "SetName") {
        std::string name;
        size_t bank, user_id;

        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          name = obj.at("name").get_string();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        current_user->GetUserInfo()->SetName(name);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "SetSurname") {
        std::string surname;
        size_t bank, user_id;

        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          surname = obj.at("surname").get_string();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        current_user->GetUserInfo()->SetSurname(surname);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "SetAddress") {
        std::string address;
        size_t bank, user_id;

        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          address = obj.at("address").get_string();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        current_user->GetUserInfo()->SetAddress(address);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "SetPassport") {
        size_t bank, user_id, passport = 0;
        std::string str_passport;

        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          str_passport = obj.at("passport").get_string();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        if (str_passport == "") {
          throw ApplicationError(kOutOfRange, "Passport should be not null");
        }
        else {
          try {
            passport = std::stoi(str_passport);
          }
          catch (std::exception& ex) {
            throw ApplicationError(kOutOfRange, ex.what());
          }
        }
        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        current_user->GetUserInfo()->SetPassport(passport);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "OpenAccount") {
        std::string acc_type_str;
        size_t bank, user_id;

        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          acc_type_str = obj.at("account_type").get_string();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        AccountType acc_type = StrAccountType(acc_type_str);
        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        current_user->GetAccounts()->OpenAccount(acc_type);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "CloseAccount") {
        size_t account_id = 0, bank, user_id;
        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          account_id = obj.at("account_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        current_user->GetAccounts()->CloseAccount(account_id);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "GetAccounts") {
        size_t bank, user_id;

        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        json::value user_accounts;
        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        auto accounts = current_user->GetAccounts()->GetAccounts();
        json::storage_ptr sp = json::make_shared_resource<json::monotonic_resource>();
        user_accounts = json::value_from(accounts);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", user_accounts},
        {"php_command", {}}
        };
      }
      else if (command == "AccountInfo") {
        size_t account_id = 0, user_id, bank;
        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          account_id = obj.at("account_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        json::value user_account_info;
        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        auto account_info = current_user->GetAccounts()->GetAccountInfo(account_id);
        if (account_info->GetAccountType() == kCredit) {
          user_account_info = json::value_from(std::static_pointer_cast<CreditAccountInfo>(account_info));
        }
        else if (account_info->GetAccountType() == kDeposit) {
          user_account_info = json::value_from(std::static_pointer_cast<DepositAccountInfo>(account_info));
        }
        else {
          user_account_info = json::value_from(account_info);
        }
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", user_account_info},
        {"php_command", {}}
        };
      }
      else if (command == "WithdrawMoney") {
        size_t account_id = 0, user_id, bank;
        double amount = 0;
        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          account_id = std::stoi(std::string(obj.at("account_id").get_string()));
          amount = std::stod(std::string(obj.at("amount").get_string()));
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        current_user->GetAccounts()->WithdrawMoney(account_id, amount);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "DepositMoney") {
        size_t account_id = 0, amount = 0, user_id, bank;
        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          account_id = std::stoi(std::string(obj.at("account_id").get_string()));
          amount = std::stod(std::string(obj.at("amount").get_string()));
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        current_user->GetAccounts()->DepositMoney(account_id, amount);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "TransferMoney") {
        size_t src_account_id = 0, dest_account_id = 0, amount = 0, user_id, bank;
        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          src_account_id = std::stoi(std::string(obj.at("source_account_id").get_string()));
          dest_account_id = std::stoi(std::string(obj.at("destination_account_id").get_string()));
          amount = std::stod(std::string(obj.at("amount").get_string()));
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        current_user->GetAccounts()->TransferMoney(src_account_id, dest_account_id, amount);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "GetTransactionHistory") {
        size_t user_id, bank;

        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        json::value transactions_history;
        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        auto history = current_user->GetTransactions()->GetTransactionHistory();
        json::storage_ptr sp = json::make_shared_resource<json::monotonic_resource>();
        transactions_history = json::value_from(history, sp);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", transactions_history},
        {"php_command", {}}
        };
      }
      else if (command == "RequestCancelTransaction") {
        size_t transaction_id = 0, bank, user_id;
        try {
          const auto& obj = val.get_object();
          bank = obj.at("bank_id").get_int64();
          user_id = obj.at("user_id").get_int64();
          transaction_id = obj.at("transaction_id").get_int64();
        }
        catch (std::out_of_range& err) {
          throw ApplicationError(kOutOfRange, "Not all params are specified");
        }

        current_bank = app.GetBank(bank);
        current_user = current_bank->GetUserManager()->GetUser(user_id);
        current_user->GetTransactions()->RequestCanelTransaction(transaction_id);
        object["status"] = "success";

        output = {
        {"status", object["status"]},
        {"error", object["error"]},
        {"result", {}},
        {"php_command", {}}
        };
      }
      else if (command == "Show_Banks") {
        json::value banks;
        auto banks_list = app.GetBanks();
        json::storage_ptr sp = json::make_shared_resource<json::monotonic_resource>();
        banks = json::value_from(banks_list, sp);
        object["status"] = "success";
        output = {
          {"status", object["status"]},
          {"error", object["error"]},
          {"result", banks},
          {"php_command", {}}
        };
      }
      else {
        output = {
          {"status", "error"},
          {"error", "Command not exist"}
        };
      }
    }
  }
  catch (ApplicationError& err) {
    output = {
      { "status", "error" },
      { "error", err.GetDesc() }
    };
  }

  std::cout << json::serialize(output) << std::endl;
  //system("PAUSE");
  return 0;
}