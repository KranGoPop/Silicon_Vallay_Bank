#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <memory>
#include "user.h"
#include "user_manager.h"
#include "user_info.h"
#include "password_manager.h"
#include "bank.h"
#include "error.h"
#include "transaction_manager.h"
#include "transaction_record.h"
#include "credit_account_info.h"
#include "credit_account.h"
#include "deposit_account.h"
#include "deposit_account_info.h"
#include "enums.h"
#include "communicate_account.h"
#include "account_manager.h"
#include "communicate_transactions.h"
#include "application.h"

void InvalidMessage(const std::string &string) {
  std::cout << "The Enter key isn't a valid " << string << std::endl;
}

int main3() {
  Application app;

  std::shared_ptr<User> current_user;
  std::shared_ptr<Bank> current_bank;
  bool is_bank_select = false;
  bool end = false;
  bool is_logined = false;
  std::string command;

  std::cout << "\n"
               "  _   _      _ _          _ _   _       ____  _ _ _                 \n"
               " | | | | ___| | | ___    (_) |_( )___  / ___|(_) (_) ___ ___  _ __  \n"
               " | |_| |/ _ \\ | |/ _ \\   | | __|// __| \\___ \\| | | |/ __/ _ \\| '_ \\ \n"
               " |  _  |  __/ | | (_) |  | | |_  \\__ \\  ___) | | | | (_| (_) | | | |\n"
               " |_| |_|\\___|_|_|\\___( ) |_|\\__| |___/ |____/|_|_|_|\\___\\___/|_| |_|\n"
               "                     |/                                             ";
  std::cout << "\n"
               "   ____                _           _   _             ______     ______                           \n"
               "  / ___|_ __ ___  __ _| |_ ___  __| | | |__  _   _  / ___\\ \\   / / ___|   __ _  __ _ _ __   __ _ \n"
               " | |   | '__/ _ \\/ _` | __/ _ \\/ _` | | '_ \\| | | | \\___ \\\\ \\ / / |  _   / _` |/ _` | '_ \\ / _` |\n"
               " | |___| | |  __/ (_| | ||  __/ (_| | | |_) | |_| |  ___) |\\ V /| |_| | | (_| | (_| | | | | (_| |\n"
               "  \\____|_|  \\___|\\__,_|\\__\\___|\\__,_| |_.__/ \\__, | |____/  \\_/  \\____|  \\__, |\\__,_|_| |_|\\__, |\n"
               "                                             |___/                       |___/             |___/ \n";
  std::cout << "Commands:\n";
  std::cout << "AuthenticateUser | AddUser | Logout | DeleteUser | ChangeLogin | ChangePassword\n";
  std::cout << "GetUserInfo | SetName | SetSurname | SetAddress | SetPassport\n";
  std::cout << "Select_Bank | Show_Banks | OpenAccount | CloseAccount | GetAccounts | AccountInfo\n";
  std::cout << "WithdrawMoney | DepositMoney | TransferMoney | RequestCancelTransaction | GetTransactionHistory\n";
  std::cout << "Help | Status | Exit" << std::endl;

  while (!end) {
    std::cin >> command;
    if (command == "AuthenticateUser") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (is_logined) {
        std::cout << "You are logined now under other user, please log out." << std::endl;
      }
      else {
        std::string login, password;
        std::cout << "Login: ";
        std::cin >> login;
        std::cout << "Password: ";
        std::cin >> password;

        try {
          current_user = current_bank->GetUserManager()->AuthenticateUser(login, password);
          is_logined = true;
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError& error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    }
    else if (command == "Logout") {
      current_user.reset();
      is_logined = false;
      std::cout << "Success" << std::endl;
    }
    else if (command == "AddUser") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (is_logined) {
        std::cout << "You are logined now under other user, please log out." << std::endl;
      }
      else {
        std::string login, password;
        std::cout << "Login: ";
        std::cin >> login;
        std::cout << "Password: ";
        std::cin >> password;
        try {
          current_bank->GetUserManager()->AddUser(login, password);
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError& error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "DeleteUser") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        try {
          current_bank->GetUserManager()->DeleteUser(current_user->GetUserId());
          is_logined = false;
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError& error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "ChangeLogin") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        std::string current_login, new_login;
        std::cout << "Current login: ";
        std::cin >> current_login;
        std::cout << "New login: ";
        std::cin >> new_login;
        try {
          current_bank->GetUserManager()->ChangeLogin(current_login, new_login);
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError &error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "ChangePassword") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        std::string current_password, new_password;
        std::cout << "Current password: ";
        std::cin >> current_password;
        std::cout << "New password: ";
        std::cin >> new_password;
        try {
          current_bank->GetUserManager()->GetPasswordManager(current_user->GetUserId())->ChangePassword(
            new_password,
            current_password
          );
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError &error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "GetUserInfo") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        try {
          std::cout << "Name: ";
          if (!current_user->GetUserInfo()->GetName().empty()) {
            std::cout << current_user->GetUserInfo()->GetName() << std::endl;
          }
          else {
            std::cout << "<Nothing>" << std::endl;
          }

          std::cout << "Surname: ";
          if (!current_user->GetUserInfo()->GetSurname().empty()) {
            std::cout << current_user->GetUserInfo()->GetSurname() << std::endl;
          }
          else {
            std::cout << "<Nothing>" << std::endl;
          }

          std::cout << "Address: ";
          if (!current_user->GetUserInfo()->GetAddress().empty()) {
            std::cout << current_user->GetUserInfo()->GetAddress() << std::endl;
          }
          else {
            std::cout << "<Nothing>" << std::endl;
          }

          std::cout << "Passport: ";
          if (current_user->GetUserInfo()->GetPassport() != 0) {
            std::cout << current_user->GetUserInfo()->GetName() << std::endl;
          }
          else {
            std::cout << "<Nothing>" << std::endl;
          }
        }
        catch (ApplicationError &error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "SetName") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        std::string name;
        std::cout << "Name to set: ";
        std::cin >> name;

        if (name.empty()) {
          InvalidMessage("name");
        }

        else {
          try {
            current_user->GetUserInfo()->SetName(name);
            std::cout << "Success!" << std::endl;
          }
          catch (ApplicationError& error) {
            std::cout << error.GetDesc() << std::endl;
          }
        }
      }
    } else if (command == "SetSurname") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        std::string surname;
        std::cout << "Surname to set: ";
        std::cin >> surname;
        if (surname.empty()) {
          InvalidMessage("surname");
        }
        else {
          try {
            current_user->GetUserInfo()->SetSurname(surname);
            std::cout << "Success!" << std::endl;
          }
          catch (ApplicationError& error) {
            std::cout << error.GetDesc() << std::endl;
          }
        }
      }
    } else if (command == "SetAddress") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        std::string address;
        std::cout << "Address to set: ";
        std::cin >> address;
        if (address.empty()) {
          InvalidMessage("surname");
        }
        else {
          try {
            current_user->GetUserInfo()->SetAddress(address);
            std::cout << "Success!" << std::endl;
          }
          catch (ApplicationError& error) {
            std::cout << error.GetDesc() << std::endl;
          }
        }
      }
    } else if (command == "SetPassport") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        size_t passport;
        std::cout << "Passport to set: ";
        std::cin >> passport;
        try {
          current_user->GetUserInfo()->SetPassport(passport);
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError& error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "Select_Bank") {
      std::string bank;
      current_user.reset();
      is_logined = false;
      is_bank_select = false;

      std::cout << "Bank List: " << std::endl;

      try {
        for (auto& i : app.GetBanks()) {
          std::cout << "\t" << i.GetName() << std::endl;
        }
      }
      catch (ApplicationError& err) {
        std::cout << err.GetDesc();
      }

      std::cout << std::endl;
      std::cout << "Select Bank Name: ";
      std::cin >> bank;

      try {
        current_bank = app.GetBank(bank);
        std::cout << "Success!" << std::endl;
        is_bank_select = true;
      }
      catch (ApplicationError& err) {
        std::cout << err.GetDesc() << std::endl;
      }
    } else if (command == "OpenAccount") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        bool is_correct_type = true;
        std::string account_type_str;
        std::cout << "Type of account to open (Debit | Credit | Deposit): ";
        std::cin >> account_type_str;
        AccountType account_type = StrUpperAccountType(account_type_str);

        if (account_type == kOtherAccType) {
          std::cout << "You pass wrong Account Type." << std::endl;
        }
        else {
          try {
            current_user->GetAccounts()->OpenAccount(account_type);
            std::cout << "Success!" << std::endl;
          }
          catch (ApplicationError& error) {
            std::cout << error.GetDesc() << std::endl;
          }
        }
      }
    } else if (command == "CloseAccount") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        size_t account_id;
        std::cout << "ID of account to close: ";
        std::cin >> account_id;
        try {
          current_user->GetAccounts()->CloseAccount(account_id);
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError& error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "GetAccounts") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        try {
          std::vector<std::shared_ptr<Account>> accounts = current_user->GetAccounts()->GetAccounts();

          for (auto& i : accounts) {
            std::cout << i->GetAccountInfo()->GetAccountId() << " ";
            std::cout << AccountTypeStrUpper(i->GetAccountInfo()->GetAccountType()) << std::endl;
          }

          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError& error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "WithdrawMoney") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        size_t account_id = 0;
        double amount;
        std::cout << "Account ID: ";
        std::cin >> account_id;
        std::cout << "Amount: ";
        std::cin >> amount;
        try {
          current_user->GetAccounts()->WithdrawMoney(account_id, amount);
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError& error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "DepositMoney") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {  
        size_t account_id = 0;
        double amount;
        std::cout << "Account ID: ";
        std::cin >> account_id;
        std::cout << "Amount: ";
        std::cin >> amount;

        try {
          current_user->GetAccounts()->DepositMoney(account_id, amount);
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError& error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "TransferMoney") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        size_t src_account_id = 0, dest_account_id = 0;
        double amount;
        std::cout << "Source Account ID: ";
        std::cin >> src_account_id;
        std::cout << "Destination account ID: ";
        std::cin >> dest_account_id;
        std::cout << "Amount: ";
        std::cin >> amount;

        try {
          current_user->GetAccounts()->TransferMoney(src_account_id, dest_account_id, amount);
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError& error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "RequestCancelTransaction") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        size_t transaction_id;
        std::cout << "Transaction ID: ";
        std::cin >> transaction_id;

        try {
          current_user->GetTransactions()->RequestCanelTransaction(transaction_id);
          std::cout << "Success!" << std::endl;
        }
        catch (ApplicationError& error) {
          std::cout << error.GetDesc() << std::endl;
        }
      }
    } else if (command == "GetTransactionHistory") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        for (auto& i : current_user->GetTransactions()->GetTransactionHistory()) {
          std::cout << "Transaction ID: " << i.GetTransactionId() << std::endl;
          std::cout << "Source account type: " << AccountTypeStrUpper(i.GetAccountSrcType()) << std::endl;
          std::cout << "Destination account type: " << AccountTypeStrUpper(i.GetAccountDestType()) << std::endl;
          std::cout << "Action type: " << ActionTypeStrUpper(i.GetActionType()) << std::endl;
          std::cout << "Transaction type: " << TransactionTypeStrUpper(i.GetTransactionType()) << std::endl;
          std::cout << "User ID sender: " << i.GetUserIdSender() << std::endl;
          std::cout << "User ID recipient: " << i.GetUserIdRecipient() << std::endl;
          std::cout << "Source Account ID: " << i.GetSourceAccId() << std::endl;
          std::cout << "Dest Account ID: " << i.GetDestAccId() << std::endl;
          std::cout << "Amount: " << i.GetAmount() << std::endl;
          std::cout << "------------------------------------\n";
        }
      }
    } else if (command == "Show_Banks") {
      std::cout << "Banks: " << std::endl;

      try {
        for (auto& i : app.GetBanks()) {
          std::cout << '\t' << i.GetName() << " Located in " << i.GetCity() << std::endl;
        }
      }
      catch (ApplicationError& err) {
        std::cout << err.GetDesc() << std::endl;
      }

      std::cout << std::endl;
    } else if (command == "AccountInfo") {
      if (!is_bank_select) {
        std::cout << "You don't select bank >:(" << std::endl;
      }
      else if (!is_logined) {
        std::cout << "First you have to log in." << std::endl;
      }
      else {
        std::vector<std::shared_ptr<Account>> accounts = current_user->GetAccounts()->GetAccounts();
        std::cout << "Choose the account you want to watch: " << std::endl;

        for (const auto& el : accounts) {
          std::cout << AccountTypeStrUpper(el->GetAccountInfo()->GetAccountType()) << " : "
            << el->GetAccountInfo()->GetAccountId()
            << " - id\n";
        }

        int account_id = 0;
        std::cout << "Enter account_id to watch: ";
        std::cin >> account_id;
        std::cout << "Information about chosen account: " << std::endl;
        auto curr_account_info = current_user->GetAccounts()->GetAccountInfo(account_id);
        std::cout << "Account id: " << curr_account_info->GetAccountId() << std::endl;
        std::cout << "Account type: " << AccountTypeStrUpper(curr_account_info->GetAccountType()) << std::endl;
        std::cout << "Balance: " << curr_account_info->GetBalance() << std::endl;

        if (curr_account_info->GetAccountType() == AccountType::kCredit) {
          auto tmp = std::static_pointer_cast<CreditAccountInfo>(curr_account_info);
          auto time = std::chrono::system_clock::to_time_t(tmp->GetStartDate());
          auto last_update = std::chrono::system_clock::to_time_t(tmp->GetLastUpdate());
          std::cout << "Start date: " << std::put_time(std::localtime(&time), "%c %Z") << std::endl;
          std::cout << "Credit limit: " << tmp->GetCreditLimit() << std::endl;
          std::cout << "Last update: " << std::put_time(std::localtime(&last_update), "%c %Z") << std::endl;
          std::cout << "Commission: " << tmp->GetCommission() << std::endl;
          std::cout << "Percent: " << tmp->GetPercent() << std::endl;
          std::cout << "Credit cycle: " << tmp->GetCreditCycle().count() << std::endl;
        }

        if (curr_account_info->GetAccountType() == AccountType::kDeposit) {
          auto tmp = std::static_pointer_cast<DepositAccountInfo>(curr_account_info);
          auto time = std::chrono::system_clock::to_time_t(tmp->GetStartDate());
          auto last_update = std::chrono::system_clock::to_time_t(tmp->GetLastUpdate());
          std::cout << "Start date: " << std::put_time(std::localtime(&time), "%c %Z") << std::endl;
          std::cout << "Last update: " << std::put_time(std::localtime(&last_update), "%c %Z") << std::endl;
          std::cout << "Percent: " << tmp->GetPercent() << std::endl;
          std::cout << "Withdraw timeout: " << tmp->GetWithdrawTimeout().count() << std::endl;
          std::cout << "Manage timeout: " << tmp->GetManageTimeout().count() << std::endl;
        }
      }
    } else if (command == "Status") {
      if (is_bank_select) {
        std::cout << "Current Bank: " << current_bank->GetName() << std::endl;

        if (is_logined) {
          std::cout << "You under user (" << current_user->GetUserId() << ")." << std::endl;
          std::cout << "\tName: " << current_user->GetUserInfo()->GetName() << std::endl;
          std::cout << "\tSurname: " << current_user->GetUserInfo()->GetSurname() << std::endl;
        }
        else {
          std::cout << "You don't select user yet." << std::endl;
        }
      }
      else {
        std::cout << "You don't select Bank." << std::endl;
      }
    } else if (command == "Help") {
      std::cout << "Commands:\n";
      std::cout << "AuthenticateUser | AddUser | Logout | DeleteUser | ChangeLogin | ChangePassword\n";
      std::cout << "GetUserInfo | SetName | SetSurname | SetAddress | SetPassport\n";
      std::cout << "Select_Bank | Show_Banks | OpenAccount | CloseAccount | GetAccounts | AccountInfo\n";
      std::cout << "WithdrawMoney | DepositMoney | TransferMoney | RequestCancelTransaction | GetTransactionHistory\n";
      std::cout << "Help | Status | Exit" << std::endl;
    } else if (command == "Exit") {
      std::cout << "Bye";
      end = true;
    } else {
      std::cout << "Incorrect command" << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;
}