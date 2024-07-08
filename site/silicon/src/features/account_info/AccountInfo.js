import React, { useEffect } from "react";
import "./AccountInfo.css"
import Header from "features/header/Header";
import CreditAccountInfo from "features/credit_account_info/CreditAccountInfo";
import DepositAccountInfo from "features/deposit_account_info/DepositAccountInfo";
import Button from "features/button/Button";
import { useState } from "react";
import ManageMoney from "features/manage_money/ManageMoney";
import { useSelector, useDispatch } from "react-redux";
import {
  selectIsInfoLoaded,
  selectCurrInfoId,
  selectAccInfo,
  getAccInfo,
  backPage,
  setModalAcc,
  selectModalAcc,
  closeAcc,
} from "features/user_page/UserPageSlice";
import History from "features/history/History";
import List from "features/list/List";
import { Modal } from "@mui/material";
import BackButton from "features/back_button/BackButton";

function AccountInfo() {
  const dispatch = useDispatch();
  const modal_acc = useSelector(selectModalAcc);
  const is_loaded = useSelector(selectIsInfoLoaded);
  const info = useSelector(selectAccInfo);
  const id = useSelector(selectCurrInfoId);

  useEffect(() => {
    if (!is_loaded) {
      dispatch(getAccInfo(id));
    }
  }, [is_loaded, dispatch]);

  return (
    <>
      <div className="acc-info">
        <div className="base-info">
          <div className="back-button-wrapp">
            <BackButton color="orange" onClick={() => {dispatch(backPage())}}/>
          </div>
          <div className="acc-type-and-id">{info.type} #{info.id}</div>
          <div className="acc-balance">{Math.round(info.balance * 100) / 100}$</div>
        </div>
        <div className="money-opers">
          <Button size="large" onClick={() => {dispatch(setModalAcc("deposit"))}}>Deposit Money</Button>
          <Button size="large" onClick={() => {dispatch(setModalAcc("withdraw"))}}>Withdraw Money</Button>
          <Button size="large" onClick={() => {dispatch(setModalAcc("transfer"))}}>Transfer Money</Button>
        </div>
        <div className="acc-info-delete">
          <Button size="large" color="red" onClick={() => {dispatch(closeAcc(info.id))}}>Close Account</Button>
        </div>
        {info.type == "Credit" && <CreditAccountInfo info={info}/>}
        {info.type == "Deposit" && <DepositAccountInfo info={info}/>}
        <div className="history">
          <List>
            <div className="acc-his-label">History</div>
            <History accId={info.id} />
          </List>
        </div>
      </div>
      <Modal open={modal_acc != "none"} onClose={() => {dispatch(setModalAcc("none"))}}>
        <ManageMoney acc_id={info.id} act_type={modal_acc} closer={() => {dispatch(setModalAcc("none"))}} />
      </Modal>
    </>
  )
}

export default AccountInfo;