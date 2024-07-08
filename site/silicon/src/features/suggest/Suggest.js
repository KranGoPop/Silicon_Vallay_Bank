import React from "react";
import "./Suggest.css";

function Suggest({
  suggest,
  children
}) {
  return (
    <div className="react-suggest-wrapp">
      <div className="react-suggest">{suggest}</div>
      {children}
    </div>
  )
}

export default Suggest;