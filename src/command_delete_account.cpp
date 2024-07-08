#include <sstream>
#include "command_delete_account.h"
#include "error.h"

CommandDeleteAccount::CommandDeleteAccount(size_t acc_id) {
  acc_id_ = acc_id;
}

void CommandDeleteAccount::Execute(sql::Statement& stm) {
  try {
    std::stringstream query_acc, query_credit, query_depos;
    query_acc << "DELETE FROM accounts WHERE account_id = ";
    query_acc << acc_id_;
    query_acc << ';';

    query_credit << "DELETE FROM credit_accounts WHERE account_id = ";
    query_credit << acc_id_;
    query_credit << ';';

    query_depos << "DELETE FROM deposit_accounts WHERE account_id = ";
    query_depos << acc_id_;
    query_depos << ';';

    stm.execute(query_acc.str());
    stm.execute(query_credit.str());
    stm.execute(query_depos.str());
  }
  catch (sql::SQLException& err) {
    throw ApplicationError(kSQLError, "SQL Error: " + err.getSQLState());
  }
}