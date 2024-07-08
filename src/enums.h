#include <string>

#ifndef HEADER__ENUMS_H_
#define HEADER__ENUMS_H_

enum AccountType { kDebit, kCredit, kDeposit, kOtherAccType };
enum ActionType { kWithdrawMoney, kDepositMoney, kTransferMoney, kOtherActionType };
enum TransactionType { kUsual, kCancel, kOtherTransType };

std::string AccountTypeStr(AccountType acc_type);
std::string AccountTypeStrUpper(AccountType acc_type);
std::string ActionTypeStr(ActionType action_type);
std::string ActionTypeStrUpper(ActionType action_type);
std::string TransactionTypeStr(TransactionType trans_type);
std::string TransactionTypeStrUpper(TransactionType trans_type);

AccountType StrAccountType(std::string acc_type);
ActionType StrActionType(std::string action_type);
TransactionType StrTransactionType(std::string trans_type);

AccountType StrUpperAccountType(std::string acc_type);
ActionType StrUpperActionType(std::string acc_type);
TransactionType StrUpperTransactionType(std::string acc_type);

#endif //HEADER__ENUMS_H_
