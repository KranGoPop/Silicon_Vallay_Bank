#include <string>

#ifndef APPLICATION_ERROR
#define APPLICATION_ERROR

enum ErrorType {
  kNotEnoughFunds,  // Not enough funds
  kAccountIdNotFound,  // Account id is not found
  kNotAManage,  // It's not a manage time
  kCreditLimitExceed,  // Credit limit exceeded
  kIncorrentAccType,  // Incorrect account type
  kAccountClosed,  // Current account is closed
  kIncorrectPass,  // Incorrect password
  kNotSuchUser,  // No match user with entered login
  kNotSuchRecord,  // No match record
  kRecordAccessDenied,  // This record not yours
  kCancelCenceled,  // You can't cancel canceled transaction
  kAccountAccessDenied,  // You can't access this account
  kUnknowError,  // Something goes wrong
  kLoginExist,  // User with this login exist
  kNegativeAmount,  // Amount cannot be negative
  kSQLError,  // Some sql error
  kOutOfLimit,  // Until you untrasted user you can't do large operation, please add addition self-information
  kNotSuchBank,  // Bank with that name does not exist
  kUnknownAccountType,  // You pass unknown Account Type
  kJSONError,  // Some Error In JSON
  kOutOfRange,  // Not all params are specified 
};

class ApplicationError {
private:
  const ErrorType error_code_;
  std::string error_desc_;
public:
  ApplicationError(ErrorType error_code_, std::string error_desc_);
  ErrorType GetCode() const;
  std::string GetDesc() const;
};

#endif