#include <memory>
#include "communicate_account.h"
#include "bank.h"
#include "user.h"
#include "user_info.h"
#include "account.h"
#include "transaction_manager.h"
#include "account_info.h"
#include "account_manager.h"
#include "debit_account_info.h"
#include "credit_account_info.h"
#include "deposit_account_info.h"
#include "credit_account.h"
#include "debit_account.h"
#include "deposit_account.h"
#include "error.h"

CommunicateAccounts::CommunicateAccounts(Bank& bank, User& user, size_t user_id) : bank_(bank), user_(user) {
  user_id_ = user_id;
}

bool CommunicateAccounts::OpenAccount(AccountType acc_type) {
  bank_.GetAccountManager()->OpenAccount(user_id_, acc_type);
  return true;
}

bool CommunicateAccounts::CloseAccount(size_t account_id) {
  bank_.GetAccountManager()->CloseAccount(user_id_, account_id);
  return true;
}

std::vector<std::shared_ptr<Account>> CommunicateAccounts::GetAccounts() {
  return bank_.GetAccountManager()->GetUserAccounts(user_id_);
}

bool CommunicateAccounts::WithdrawMoney(size_t account_id, double amount) {
  if (!user_.GetUserInfo()->IsTrusted() && amount > bank_.GetAccountManager()->GetLimit()) {
    throw ApplicationError(kOutOfLimit, "Until you untrasted user you can't do large operation, please add addition self-information");
  }

  auto acc = bank_.GetAccountManager()->GetAccount(user_id_, account_id);
  auto acc_info = acc->GetAccountInfo();
  acc->WithdrawMoney(amount);
  bank_.GetTransactionManager()->AddTransactionSystem(
    acc_info->GetAccountType(),
  acc_info->GetAccountType(),
    kWithdrawMoney,
    acc_info->GetUserId(),
    acc_info->GetUserId(),
    amount,
    acc_info->GetAccountId(),
    acc_info->GetAccountId()
  );

  return true;
}

bool CommunicateAccounts::DepositMoney(size_t account_id, double amount) {
  if (!user_.GetUserInfo()->IsTrusted() && amount > bank_.GetAccountManager()->GetLimit()) {
    throw ApplicationError(kOutOfLimit, "Until you untrasted user you can't do large operation, please add addition self-information");
  }

  auto acc = bank_.GetAccountManager()->GetAccount(user_id_, account_id);
  auto acc_info = acc->GetAccountInfo();
  acc->DepositMoney(amount);

  bank_.GetTransactionManager()->AddTransactionSystem(
    acc_info->GetAccountType(),
    acc_info->GetAccountType(),
    kDepositMoney,
    acc_info->GetUserId(),
    acc_info->GetUserId(),
    amount,
    acc_info->GetAccountId(),
    acc_info->GetAccountId()
  );

  return true;
}

bool CommunicateAccounts::TransferMoney(size_t src_account_id, size_t dest_account_id, double amount) {
  if (!user_.GetUserInfo()->IsTrusted() && amount > bank_.GetAccountManager()->GetLimit()) {
    throw ApplicationError(kOutOfLimit, "Until you untrasted user you can't do large operation, please add addition self-information");
  }

  auto acc_src = bank_.GetAccountManager()->GetAccount(user_id_, src_account_id);
  auto acc_dest = bank_.GetAccountManager()->GetAccountSystem(dest_account_id);
  auto acc_src_info = acc_src->GetAccountInfo();
  auto acc_dest_info = acc_dest->GetAccountInfo();

  acc_src->WithdrawMoney(amount);
  acc_dest->DepositMoney(amount);

  bank_.GetTransactionManager()->AddTransactionSystem(
    acc_src_info->GetAccountType(),
    acc_dest_info->GetAccountType(),
    kTransferMoney,
    acc_dest_info->GetUserId(),
    acc_src_info->GetUserId(),
    amount,
    acc_src_info->GetAccountId(),
    acc_dest_info->GetAccountId()
  );

  return true;
}

std::shared_ptr<AccountInfo> CommunicateAccounts::GetAccountInfo(size_t account_id) {
  return bank_.GetAccountManager()->GetAccount(user_id_, account_id)->GetAccountInfo();
}