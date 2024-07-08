import React from "react";
import "features/transaction/Transaction.css";
import Button from "features/button/Button";
import { useDispatch } from "react-redux";
import { cancelTrans } from "features/user_page/UserPageSlice";

function Transaction({trans}) {
  const dispatch = useDispatch();

  let color = "#94F2A3";
  if (trans.trans_type == "Cancel") {
    color = "#BBEFFF";
  }

  let acc_type;

  if (trans.action_type == 'TransferMoney') {
    acc_type = <div className="accs-type">{trans.src_acc_type}&rarr;{trans.dest_acc_type}</div>
  }
  else {
    acc_type = <div className="accs-type">{trans.src_acc_type}</div>
  }

  let acc_id;

  if (trans.action_type == 'TransferMoney') {
    acc_id = <div className="accs-id">AccIds# {trans.src_acc_id}&rarr;{trans.dest_acc_id}</div>;
  }
  else {
    acc_id = <div className="accs-id">AccId# {trans.src_acc_id}</div>
  }

  let user_id;

  if (trans.action_type == 'TransferMoney') {
    user_id = <div className="users-id">UserIds# {trans.src_user_id}&rarr;{trans.dest_user_id}</div>
  }
  else {
    user_id = <div className="users-id">UserId# {trans.src_user_id}</div>
  }

  return (
    <div className="transaction" style={{backgroundColor: color}}>
      <div className="trans-date">Transaction Time: {new Date(trans.time).toUTCString()}</div>
      <div className="trans-acc-type">From what Account to what account transaction pass: {trans.src_acc_type}&rarr;{trans.dest_acc_type}</div>
      <div className="trans-acc-id">From what AccountId to what AccountId transaction pass: {trans.src_acc_id}&rarr;{trans.dest_acc_id}</div>
      <div className="act-type">Action Type: {trans.action_type}</div>
      {trans.trans_type == "Cancel" && <div className="trans-type">This canceled transaction. P.S. Administration</div>}
      <div className="value">Amount: {trans.amount}$</div>
      {trans.trans_type != "Cancel" && !trans.canceled && <Button onClick={() => {dispatch(cancelTrans(trans.id))}}>Cancel</Button>}
    </div>  
  )
}

export default Transaction;