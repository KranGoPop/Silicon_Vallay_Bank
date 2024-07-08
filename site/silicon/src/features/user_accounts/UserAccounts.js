import React from "react";
import "./UserAccounts.css";
import { useEffect,useState } from "react";
import { useDispatch, useSelector } from "react-redux";
import Account from "features/account/Account";
import Button from "features/button/Button";
import List from "features/list/List";
import AccCreate from "features/acc_create/AccCreate";
import {
  getAccounts,
  selectIsAccChange,
  selectAccounts,
} from "features/user_page/UserPageSlice";
import { Modal } from "@mui/material";

function UserAccounts() {
  const dispatch = useDispatch();
  const [curr_menu, SetCurrMenu] = useState('none');
  const is_change = useSelector(selectIsAccChange);
  const accs = useSelector(selectAccounts);

  useEffect(() => {
    if (is_change) {
      dispatch(getAccounts());
    }
  }, [is_change]);

  return (
    <>
    <div className="accounts">
        <Button onClick={()=>{SetCurrMenu('debit')}} size="mega" color="blue">Open Debit</Button>
        <Button onClick={()=>{SetCurrMenu('credit')}} size="mega" color="gold">Open Credit</Button>
        <Button onClick={()=>{SetCurrMenu('deposit')}} size="mega" color="purple">Open Deposit</Button>
    </div>
    <Account type="AccountType" accId="#Id" balance = "Balance" row/>
    <List>
      {
        accs.map((e) => <Account key={e.id} type={e.type} accId={e.id} balance={e.balance} />)
      }
    </List>
    {/* {curr_menu != 'none' && <AccCreate accType={curr_menu} closer={()=>{SetCurrMenu('none')}}/>} */}
    <Modal open={curr_menu != 'none'} onClose={() => {SetCurrMenu('none')}}>
      <AccCreate accType={curr_menu} closer={() => {SetCurrMenu('none')}}/>
    </Modal>
    </>
  );
}

export default UserAccounts;