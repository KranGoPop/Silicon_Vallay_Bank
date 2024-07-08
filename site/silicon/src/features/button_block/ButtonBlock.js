import React from "react";
import "./ButtonBlock.css";

function ButtonBlock({children}) {
  return (
    <div className="react-button-block">
      {children}
    </div>
  )
}

export default ButtonBlock;