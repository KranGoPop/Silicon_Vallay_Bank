#include "enums.h"

std::string AccountTypeStr(AccountType acc_type) {
  std::string answer;

  if (acc_type == kDebit) {
    answer = "debit";
  }
  else if (acc_type == kCredit) {
    answer = "credit";
  }
  else if (acc_type == kDeposit) {
    answer = "deposit";
  }
  else if (acc_type == kOtherAccType) {
    answer = "other_account_type";
  }

  return answer;
}


AccountType StrAccountType(std::string acc_type) {
  AccountType answer = kDebit;

  if (acc_type == "debit") {
    answer = kDebit;
  }
  else if (acc_type == "credit") {
    answer = kCredit;
  }
  else if (acc_type == "deposit") {
    answer = kDeposit;
  }
  else {
    answer = kOtherAccType;
  }

  return answer;
}

std::string AccountTypeStrUpper(AccountType acc_type) {
  std::string answer;

  if (acc_type == kDebit) {
    answer = "Debit";
  }
  else if (acc_type == kCredit) {
    answer = "Credit";
  }
  else if (acc_type == kDeposit) {
    answer = "Deposit";
  }
  else if (acc_type == kOtherAccType) {
    answer = "Other Account Type";
  }

  return answer;
}

AccountType StrUpperAccountType(std::string acc_type) {
  AccountType answer;
  if (acc_type == "Debit") {
    answer = kDebit;
  }
  else if (acc_type == "Credit") {
    answer = kCredit;
  }
  else if (acc_type == "Deposit") {
    answer = kDeposit;
  }
  else {
    answer = kOtherAccType;
  }

  return answer;
}

std::string ActionTypeStr(ActionType action_type) {
  std::string answer;

  if (action_type == kDepositMoney) {
    answer = "deposit";
  }
  else if (action_type == kWithdrawMoney) {
    answer = "withdraw";
  }
  else if (action_type == kTransferMoney) {
    answer = "transfer";
  }
  else if (action_type == kOtherActionType) {
    answer = "other_action_type";
  }

  return answer;
}

ActionType StrActionType(std::string action_type) {
  ActionType answer = kDepositMoney;

  if (action_type == "deposit") {
    answer = kDepositMoney;
  }
  else if (action_type == "withdraw") {
    answer = kWithdrawMoney;
  }
  else if (action_type == "transfer") {
    answer = kTransferMoney;
  }
  else {
    answer = kOtherActionType;
  }

  return answer;
}

std::string ActionTypeStrUpper(ActionType action_type) {
  std::string answer;

  if (action_type == kDepositMoney) {
    answer = "DepositMoney";
  }
  else if (action_type == kWithdrawMoney) {
    answer = "WithdrawMoney";
  }
  else if (action_type == kTransferMoney) {
    answer = "TransferMoney";
  }
  else if (action_type == kOtherActionType) {
    answer = "Other Action Type";
  }

  return answer;
}

ActionType StrUpperActionType(std::string acc_type) {
  ActionType answer;

  if (acc_type == "DepositMoney") {
    answer = kDepositMoney;
  }
  else if (acc_type == "WithdrawMoney") {
    answer = kWithdrawMoney;
  }
  else if (acc_type == "TransferMoney") {
    answer = kTransferMoney;
  }
  else {
    answer = kOtherActionType;
  }

  return answer;
}

std::string TransactionTypeStr(TransactionType trans_type) {
  std::string answer;

  if (trans_type == kCancel) {
    answer = "cancel";
  }
  else if (trans_type == kUsual) {
    answer = "usual";
  }
  else if (trans_type == kOtherTransType) {
    answer = "other_transaction_type";
  }

  return answer;
}


TransactionType StrTransactionType(std::string trans_type) {
  TransactionType answer = kUsual;

  if (trans_type == "cancel") {
    answer = kCancel;
  }
  else if (trans_type == "usual") {
    answer = kUsual;
  }
  else {
    answer = kOtherTransType;
  }

  return answer;
}

std::string TransactionTypeStrUpper(TransactionType trans_type) {
  std::string answer;

  if (trans_type == kCancel) {
    answer = "Cancel";
  }
  else if (trans_type == kUsual) {
    answer = "Usual";
  }
  else if (trans_type == kOtherTransType) {
    answer = "Other Transaction Type";
  }

  return answer;
}

TransactionType StrUpperTransactionType(std::string acc_type) {
  TransactionType answer;

  if (acc_type == "Cancel") {
    answer = kCancel;
  }
  else if (acc_type == "Usual") {
    answer = kUsual;
  }
  else {
    answer = kOtherTransType;
  }

  return answer;
}