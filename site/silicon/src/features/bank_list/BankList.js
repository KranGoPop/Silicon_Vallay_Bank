import React from "react";
import { useEffect } from "react";
import { useDispatch, useSelector } from "react-redux";
import {
  selectBanks,
  selectStatus,
  selectError,
  getBanks,
} from "./BankListSlice";
import {
  addErrorItem
} from "features/error_list/ErrorListSlice";
import "./BankList.css";
import Bank from "features/bank/Bank";
import Header from "features/header/Header";

function BankList() {
  const dispatch = useDispatch();
  const status = useSelector(selectStatus);
  const banks = useSelector(selectBanks);
  const err = useSelector(selectError);

  useEffect(() => {
    if (status == 'idle') {
      dispatch(getBanks());
    }
  }, [status, dispatch]);

  useEffect(() => {
    if (status == 'error') {
      dispatch(addErrorItem(err));
    }
  }, [status, err]);

  let colors = ['#CFF6FF', '#E8FFCA', '#CADCFF'];

  let banks_arr = banks.map((val) => 
    <Bank key={val.id} name={val.name} city={val.city} color={colors[val.id % 3]}/>
  );

  return (
    <>
      <Header/>
      <main className="bank-list-main">
        <div className="bank-title">Bank List</div>
        <div className="bank-list">
          {banks_arr}
        </div>
      </main>
    </>
  );
}

export default BankList;