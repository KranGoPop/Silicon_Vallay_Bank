import React from "react";
import "features/account/Account.css";
import Button from "features/button/Button";
import { useDispatch } from "react-redux";
import { closeAcc } from "features/user_page/UserPageSlice";
import { showInfo } from "features/user_page/UserPageSlice";

function Account({type,accId,balance, row}) {
  const dispatch = useDispatch();

  let color;
  if (type == "Debit") {
    color = "#CFF6FF";
  } else if (type == "Credit") {
    color = "#FFE99C";
  } else if (type == "Deposit") {
    color = "#F9B5FF";
  }

  let onClick = null;
  if (!row) {
    onClick = () => {dispatch(showInfo({
      id: accId,
      type: type.charAt(0).toLowerCase() + type.slice(1)
    }))}
  }
  return (
    <div className="account" style={{backgroundColor: color}} onClick={onClick}>
      <div className="account-type">{type}</div>
      <div className="account-id">{accId}</div>
      <div className="account-balance">{!row ? Math.round(balance * 100) / 100 : 'Balance'} $</div>
    </div>
  )
}

export default Account;