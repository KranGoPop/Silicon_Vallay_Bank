import React from "react";
import "./ErrorList.css";
import List from "features/list/List";
import { useSelector } from "react-redux";
import { selectErrors } from "./ErrorListSlice";
import Error from "features/error/Error";

function ErrorList() {
  const err_list = useSelector(selectErrors);
  return (
    <div className="react-error-list">
      <List>
        {err_list.map(item => {return item.visible && <Error key={item.id} errId={item.id} error={item.error}/>}).reverse()}
      </List>
    </div>
  );
}

export default ErrorList;