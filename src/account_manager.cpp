#include <string>
#include <cstdint>
#include <memory>
#include <mysql/jdbc.h>
#include "transaction_manager.h"
#include "account_manager.h"
#include "deposit_account.h"
#include "credit_account.h"
#include "debit_account.h"
#include "error.h"
#include "bank.h"
#include "enums.h"
#include "transaction_record.h"
#include "db_manager.h"
#include "command_get_user_accounts.h"
#include "command_add_deposit_info.h"
#include "command_add_credit_info.h"
#include "command_get_account.h"
#include "command_get_credit_info.h"
#include "command_get_deposit_info.h"
#include "command_add_account.h"
#include "command_delete_account.h"
#include <chrono>

AccountManager::AccountManager(Bank &bank) : bank_(bank) {
}

std::shared_ptr<Account> AccountManager::GetAccount(size_t user_id, size_t account_id) {
  std::shared_ptr<Account> answer;
  auto account = std::shared_ptr<CommandGetAccount>(new CommandGetAccount(user_id, account_id));
  bank_.GetDBManager()->SendExecutable(account);

  if (account->GetInfo().GetUserId() != user_id) {
    throw ApplicationError(kAccountAccessDenied, "You can't access this account");
  }

  if (account->GetInfo().GetAccountType() == AccountType::kCredit) {
    auto credit_info = std::shared_ptr<CommandGetCreditInfo>(new CommandGetCreditInfo(account_id, account->GetInfo()));
    bank_.GetDBManager()->SendExecutable(credit_info);
    CreditAccountInfo info = credit_info->GetInfo();

    answer = std::shared_ptr<CreditAccount>(new CreditAccount(
      bank_,
      user_id,
      account_id,
      info.GetCreditLimit(),
      info.GetCommission(),
      info.GetPercent(),
      info.GetStartDate(),
      info.GetCreditCycle(),
      info.GetLastUpdate(),
      info.GetBalance()
    ));
  }
  else if (account->GetInfo().GetAccountType() == AccountType::kDeposit) {
    auto deposit_info = std::shared_ptr<CommandGetDepositInfo>(new CommandGetDepositInfo(account_id, account->GetInfo()));
    bank_.GetDBManager()->SendExecutable(deposit_info);
    DepositAccountInfo info = deposit_info->GetInfo();

    answer = std::shared_ptr<DepositAccount>(new DepositAccount(
      bank_,
      user_id,
      account_id,
      info.GetStartDate(),
      info.GetWithdrawTimeout(),
      info.GetManageTimeout(),
      info.GetPercent(),
      info.GetCycleCount(),
      info.GetLastUpdate(),
      info.GetBalance()
    ));
  }
  else if (account->GetInfo().GetAccountType() == AccountType::kDebit) {
    answer = std::shared_ptr<DebitAccount>(new DebitAccount(bank_, user_id, account_id, account->GetInfo().GetBalance()));
  }

  return answer;
}

std::shared_ptr<Account> AccountManager::GetAccountSystem(size_t account_id) {
  std::shared_ptr<Account> answer;
  auto account = std::shared_ptr<CommandGetAccount>(new CommandGetAccount(account_id));
  bank_.GetDBManager()->SendExecutable(account);

  if (account->GetInfo().GetAccountType() == AccountType::kCredit) {
    auto credit_info = std::shared_ptr<CommandGetCreditInfo>(new CommandGetCreditInfo(account_id, account->GetInfo()));
    bank_.GetDBManager()->SendExecutable(credit_info);
    CreditAccountInfo info = credit_info->GetInfo();

    answer = std::shared_ptr<CreditAccount>(new CreditAccount(
      bank_,
      info.GetUserId(),
      account_id,
      info.GetCreditLimit(),
      info.GetCommission(),
      info.GetPercent(),
      info.GetStartDate(),
      info.GetCreditCycle(),
      info.GetLastUpdate(),
      info.GetBalance()
    ));
  }
  else if (account->GetInfo().GetAccountType() == AccountType::kDeposit) {
    auto deposit_info = std::shared_ptr<CommandGetDepositInfo>(new CommandGetDepositInfo(account_id, account->GetInfo()));
    bank_.GetDBManager()->SendExecutable(deposit_info);
    DepositAccountInfo info = deposit_info->GetInfo();

    answer = std::shared_ptr<DepositAccount>(new DepositAccount(
      bank_,
      info.GetUserId(),
      account_id,
      info.GetStartDate(),
      info.GetWithdrawTimeout(),
      info.GetManageTimeout(),
      info.GetPercent(),
      info.GetCycleCount(),
      info.GetLastUpdate(),
      info.GetBalance()
    ));
  }
  else if (account->GetInfo().GetAccountType() == AccountType::kDebit) {
    AccountInfo info = account->GetInfo();

    answer = std::shared_ptr<DebitAccount>(new DebitAccount(
      bank_,
      info.GetUserId(),
      account_id,
      info.GetBalance()));
  }

  return answer;
}

std::vector<std::shared_ptr<Account>> AccountManager::GetUserAccounts(size_t user_id) {
  auto accounts = std::shared_ptr<CommandGetUserAccounts>(new CommandGetUserAccounts(user_id));
  bank_.GetDBManager()->SendExecutable(accounts);
  std::vector < std::shared_ptr<Account>> user_accounts;

  for (auto& el : accounts->GetAccounts()) {
    if (el.GetAccountType() == AccountType::kCredit) {
      auto credit_info = std::shared_ptr<CommandGetCreditInfo>(new CommandGetCreditInfo(el.GetAccountId(), el));
      bank_.GetDBManager()->SendExecutable(credit_info);
      CreditAccountInfo info = credit_info->GetInfo();

      user_accounts.push_back(std::shared_ptr<CreditAccount>(new CreditAccount(
        bank_,
        info.GetUserId(),
        el.GetAccountId(),
        info.GetCreditLimit(),
        info.GetCommission(),
        info.GetPercent(),
        info.GetStartDate(),
        info.GetCreditCycle(),
        info.GetLastUpdate(),
        info.GetBalance()
      )));
    }
    else if (el.GetAccountType() == AccountType::kDeposit) {
      auto deposit_info = std::shared_ptr<CommandGetDepositInfo>(new CommandGetDepositInfo(el.GetAccountId(), el));
      bank_.GetDBManager()->SendExecutable(deposit_info);
      DepositAccountInfo info = deposit_info->GetInfo();

      user_accounts.push_back(std::shared_ptr<DepositAccount>(new DepositAccount(
        bank_,
        info.GetUserId(),
        el.GetAccountId(),
        info.GetStartDate(),
        info.GetWithdrawTimeout(),
        info.GetManageTimeout(),
        info.GetPercent(),
        info.GetCycleCount(),
        info.GetLastUpdate(),
        info.GetBalance()
      )));
    }
    else {
      user_accounts.push_back(std::shared_ptr<DebitAccount>(new DebitAccount(
        bank_,
        el.GetUserId(),
        el.GetAccountId(),
        el.GetBalance()
      )));
    }
  }
  return user_accounts;
}

bool AccountManager::OpenAccount(size_t user_id, AccountType account_type) {
  auto new_account = std::shared_ptr<CommandAddAccount>(new CommandAddAccount(user_id, account_type));
  bank_.GetDBManager()->SendExecutable(new_account);
  if (account_type == kDeposit) {
    auto deposit_account = std::shared_ptr<CommandAddDepositInfo>(new CommandAddDepositInfo(new_account->GetAccId(), 10s, 10s, 1.1, 0));
    bank_.GetDBManager()->SendExecutable(deposit_account);
  }
  else if (account_type == kCredit) {
    auto credit_account = std::shared_ptr<CommandAddCreditInfo>(new CommandAddCreditInfo(new_account->GetAccId()));
    bank_.GetDBManager()->SendExecutable(credit_account);
  }
  else if (account_type == kOtherAccType) {
    throw ApplicationError(kUnknownAccountType, "You pass unknown Account Type");
  }
  return true;
}

bool AccountManager::CloseAccount(size_t user_id, size_t account_id) {
  auto account = GetAccount(user_id, account_id);

  if (account->GetUserId() != user_id) {
    throw ApplicationError(kAccountAccessDenied, "You can't access this account");
  }

  auto command = std::shared_ptr<CommandDeleteAccount>(new CommandDeleteAccount(account_id));
  bank_.GetDBManager()->SendExecutable(command);
  return true;
}

bool AccountManager::CancelTransaction(size_t user_id, size_t transaction_id) {
  auto record = bank_.GetTransactionManager()->GetTransaction(user_id,transaction_id);

  if (record.GetTransactionType() == kCancel || record.IsCanceled()) {
    throw ApplicationError(kCancelCenceled, "You can't cancel canceled transaction");
  }

  if (record.GetUserIdRecipient() != user_id && record.GetUserIdSender() != user_id) {
    throw ApplicationError(kRecordAccessDenied, "This record not yours");
  }

  TransactionRecord canceled_trans = bank_.GetTransactionManager()->CancelTransactionSystem(transaction_id);

  auto src_acc = GetAccountSystem(canceled_trans.GetSourceAccId());
  auto dest_acc = GetAccountSystem(canceled_trans.GetDestAccId());
  double amount = canceled_trans.GetAmount();
  ActionType action = canceled_trans.GetActionType();

  if (action == kTransferMoney) {
    src_acc->WithdrawMoneySystem(amount);
    dest_acc->DepositMoneySystem(amount);
  } else if (action == kDepositMoney) {
    src_acc->DepositMoneySystem(amount);
  } else if (action == kWithdrawMoney) {
    src_acc->WithdrawMoneySystem(amount);
  }
  else {
    throw ApplicationError(kUnknownAccountType, "You pass unknown Account Type");
  }

  return true;
}

double AccountManager::GetLimit() const {
  return fixed_limit_;
}