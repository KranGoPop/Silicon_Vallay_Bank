#include <string>
#include "error.h"

ApplicationError::ApplicationError(ErrorType error_code, std::string error_desc) : error_code_(error_code), error_desc_(error_desc) {
}

ErrorType ApplicationError::GetCode() const {
  return error_code_;
}

std::string ApplicationError::GetDesc() const {
  return error_desc_;
}