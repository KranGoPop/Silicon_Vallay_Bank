import React from "react";
import "./Error.css";
import Button from "features/button/Button";
import { removeErrorItem } from "features/error_list/ErrorListSlice";
import { useDispatch } from "react-redux";

function Error({
  errId,
  error,
  close
}) {
  const dispatch = useDispatch();
  return (
    <div className='react-error'>
      <div className="react-error-desc">{error}</div>
      <Button color="void" onClick={()=> {dispatch(removeErrorItem(errId))}}>Close</Button>
    </div>
  )
}

export default Error;