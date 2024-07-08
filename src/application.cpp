#include <sstream>
#include "application.h"
#include "bank.h"
#include "error.h"

Application::Application() {
  try {
    sql::Driver* driver = sql::mysql::get_driver_instance();
    conn_ = std::shared_ptr<sql::Connection>(driver->connect("mysql://127.0.0.1", "sil", "password"));
    stm_ = std::shared_ptr<sql::Statement>(conn_->createStatement());
    stm_->execute("USE silicon;");
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, err.getSQLState());
  }
}

std::vector<BankInfo> Application::GetBanks() {
  std::vector<BankInfo> answer;
  try {
    std::unique_ptr<sql::ResultSet> res(stm_->executeQuery("SELECT id, name, city FROM banks;"));

    while (res->next()) {
      answer.push_back(BankInfo(res->getUInt64("id"), res->getString("name"), res->getString("city")));
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }

  return answer;
}

std::shared_ptr<Bank> Application::GetBank(std::string name) {
  std::shared_ptr<Bank> bank;

  try {
    std::stringstream query;
    query << "SELECT id, name, city FROM banks WHERE name = '";
    query << name << "';";

    std::unique_ptr<sql::ResultSet> res(stm_->executeQuery(query.str()));

    if (res->rowsCount() == 0) {
      throw ApplicationError(kNotSuchBank, "Bank with that name does not exist");
    }

    while (res->next()) {
      bank.reset(new Bank(res->getUInt("id"), res->getString("name"), res->getString("city"), stm_));
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }

  return bank;
}

std::shared_ptr<Bank> Application::GetBank(size_t bank_id) {
  std::shared_ptr<Bank> bank;

  try {
    std::stringstream query;
    query << "SELECT id, name, city FROM banks WHERE id = ";
    query << bank_id << ";";

    std::unique_ptr<sql::ResultSet> res(stm_->executeQuery(query.str()));

    if (res->rowsCount() == 0) {
      throw ApplicationError(kNotSuchBank, "Bank with that name does not exist");
    }

    while (res->next()) {
      bank.reset(new Bank(res->getUInt("id"), res->getString("name"), res->getString("city"), stm_));
    }
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }

  return bank;
}