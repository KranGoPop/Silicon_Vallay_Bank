#include <memory>
#include <stdexcept>
#include <utility>
#include <chrono>
#include <memory>
#include "transaction_manager.h"
#include "bank.h"
#include "enums.h"
#include "error.h"
#include "db_manager.h"
#include "command_add_transaction_record.h"
#include "command_get_transaction.h"
#include "command_update_transaction_cancel.h"
#include "command_get_user_transactions.h"

using namespace std::chrono;

TransactionManager::TransactionManager(Bank &bank) : bank_(bank) {
}

bool TransactionManager::AddTransactionSystem(AccountType src_acc_type,
                                              AccountType dest_acc_type,
                                              ActionType act_type,
                                              size_t user_id_res,
                                              size_t user_id_src,
                                              double amount,
                                              size_t acc_id_src,
                                              size_t acc_id_dest, bool canceled) {

  auto record = std::make_shared<CommandAddTransactionRecrod>(TransactionRecord(
    bank_.GetBankId(),
    src_acc_type,
    dest_acc_type,
    act_type,
    kUsual,
    history_.size(),
    user_id_res,
    user_id_src, 
    amount,
    acc_id_src,
    acc_id_dest,
    canceled
  ));
  bank_.GetDBManager()->SendExecutable(record);
  return true;
}

TransactionRecord TransactionManager::CancelTransactionSystem(size_t transaction_id) {
  auto comm_trans = std::shared_ptr<CommandGetTransaction>(new CommandGetTransaction(transaction_id));
  bank_.GetDBManager()->SendExecutable(comm_trans);
  TransactionRecord record = comm_trans->GetRecord();
  auto comm_update = std::make_shared<CommandUpdateTransactionCancel>(transaction_id);
  bank_.GetDBManager()->SendExecutable(comm_update);
  ActionType action;

  if (record.GetActionType() == kTransferMoney) {
    action = kTransferMoney;
  } else if (record.GetActionType() == kDepositMoney) {
    action = kWithdrawMoney;
  } else {
    action = kDepositMoney;
  }

  AccountType src_acc_type = record.GetAccountDestType();
  AccountType dest_acc_type = record.GetAccountSrcType();
  double amount = record.GetAmount();
  size_t user_sender = record.GetUserIdRecipient();
  size_t user_rec = record.GetUserIdSender();
  size_t src_acc_id = record.GetDestAccId();
  size_t dest_acc_id = record.GetSourceAccId();
  TransactionType trans_type = kCancel;

  TransactionRecord canceled_trans(
    bank_.GetBankId(),
    src_acc_type,
    dest_acc_type,
    action,
    trans_type,
    user_rec,
    0,
    user_sender,
    amount,
    src_acc_id,
    dest_acc_id,
    false
  );

  auto canceled_record = std::shared_ptr<CommandAddTransactionRecrod>(new CommandAddTransactionRecrod(canceled_trans));
  bank_.GetDBManager()->SendExecutable(canceled_record);

  return canceled_trans;
}

TransactionRecord TransactionManager::GetTransaction(size_t user_id, size_t transaction_id) {

/*  try {
    record = history_.at(transaction_id);
  }
  catch (std::out_of_range &error) {
    throw ApplicationError(kNotSuchRecord, "No match record");
  }*/

  auto record = std::make_shared<CommandGetTransaction>(user_id, transaction_id);
  bank_.GetDBManager()->SendExecutable(record);

  if (record->GetRecord().GetUserIdRecipient() != user_id && record->GetRecord().GetUserIdSender() != user_id) {
    throw ApplicationError(kRecordAccessDenied, "This record not yours");
  }

  return record->GetRecord();
}

TransactionRecord TransactionManager::GetTransactionSystem(size_t transaction_id) {
/*  std::pair<TransactionRecord, Canceled> record{};

  try {
    record = history_.at(transaction_id);
  }
  catch (std::out_of_range &error) {
    throw ApplicationError(kNotSuchRecord, "No match record");
  }*/
  auto record = std::make_shared<CommandGetTransaction>(transaction_id);
  bank_.GetDBManager()->SendExecutable(record);
  return record->GetRecord();
}

std::vector<TransactionRecord> TransactionManager::GetUserTransactions(size_t user_id) const {
/*  std::vector<std::pair<TransactionRecord, Canceled>> user_trans;

  for (auto &i : history_) {
    if (i.first.GetUserIdRecipient() == user_id || i.first.GetUserIdSender() == user_id) {
      user_trans.push_back(i);
    }
  }*/
  auto records = std::make_shared<CommandGetUserTransaction>(user_id);
  bank_.GetDBManager()->SendExecutable(records);
  return records->GetRecords();
}