import React from "react";
import "./ManageMoney.css";
import Button from "features/button/Button";
import List from "features/list/List";
import Input from "features/input/Input";
import { useState } from "react";
import { useDispatch } from "react-redux";
import { transferMoney, depositMoney, withdrawMoney } from "features/user_page/UserPageSlice";
import { distance } from "chroma-js";

function ManageMoney({acc_id, act_type, closer}) {
  const [amount, changeAmount] = useState("");
  const [dest_acc_id, changeDestAccId] = useState("");
  const dispatch = useDispatch();

  let lable;
  if (act_type == "deposit"){
    lable = "Deposit Money";
  } else if (act_type == "withdraw") {
    lable = "Withdraw Money";
  } else {
    lable = "Transfer Money";
  }
  return (
    <div className="block">
    <div className="manage-money">
      <div className="manage-act-type">{lable}</div>
      <List>
        {act_type == "transfer" && <Input text="Dest. Account ID" value = {dest_acc_id} onChange={(event) => {changeDestAccId(event.target.value)}} />}
        <Input text="Amount" value={amount} onChange={(event) => {changeAmount(event.target.value)}} />
      </List>
      <div className="buttons">
        <Button onClick={closer}>Cancel</Button>
        <Button onClick={() => {
          if (act_type == "deposit") {
            dispatch(depositMoney({accId: acc_id, amount}));
          } else if (act_type == "withdraw") {
            dispatch(withdrawMoney({accId: acc_id, amount}));
          } else {
            dispatch(transferMoney({srcAccId: acc_id, destAccId: dest_acc_id, amount}));
          }
        }}>Confirm</Button>
      </div>
    </div>
    </div>
  )
}

export default ManageMoney;