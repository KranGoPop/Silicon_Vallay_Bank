import React from "react";
import "./Info.css";

function Info({children}) {
  return(
    <div className="react-info">
      {children}
    </div>  
  )
}

export default Info;