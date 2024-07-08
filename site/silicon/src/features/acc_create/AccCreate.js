import React from "react";
import { ReactDOM } from "react";
import { useEffect } from "react";
import "./AccCreate.css";
import Button from "features/button/Button";
import { useDispatch } from "react-redux";
import { openAccount } from "features/user_page/UserPageSlice";
import { Modal } from "@mui/material";

function AccCreate({accType, closer}) {
  const dispatch = useDispatch();
  return (
    <div className="react-acc-create-wrapp">
    <div className="react-acc-create">
      <div className="react-acc-create-name">{accType.charAt(0).toUpperCase() + accType.slice(1)}</div>
      <div className="react-acc-button">
        <Button onClick={()=>{dispatch(openAccount(accType)); closer();}}>Create</Button>
        <Button onClick={closer}>Close</Button>
      </div>
    </div>
    </div>
  );
}

export default AccCreate;