import React from "react";
import "./MainLogBlock.css";
import { useSelector, useDispatch } from "react-redux";
import { selectBankName, noToken } from "AppSlice";
import BackButton from "features/back_button/BackButton";

function MainLogBlock({type, inputs, buttons}) {
  const dispatch = useDispatch();
  const bank_name = useSelector(selectBankName);

  return (
    <div className="main-log-block">
      <div className="main-log-block_bank-name">
        <div>{bank_name}</div>
      </div>
      <div className="main-log-block_type">
        {type}
      </div>
      <div className="main-log-block_inputs">{inputs}</div>
      <div className="main-log-block_buttons">{buttons}</div>
      <div className="main-log-block_back">
        <BackButton onClick={()=>{dispatch(noToken())}}/>
      </div>
    </div>
  );
}

export default MainLogBlock;