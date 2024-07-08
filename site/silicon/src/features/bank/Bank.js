import React from "react";
import './Bank.css';
import { useDispatch } from "react-redux";
import { setBank } from "AppSlice";

function Bank({
  color,
  name,
  city
}) {
  const dispatch = useDispatch();
  return (
    <div className="bank" style={{backgroundColor: color}} onClick={() => {
      dispatch(setBank(name));
    }}>
      <div className="bank-name">{name}</div>
      <div className="bank-city">Located in {city}</div>
    </div>
  );
}

export default Bank;