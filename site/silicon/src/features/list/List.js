import React from "react";
import "./List.css"

function List({children}) {
  return (
    <div className="react-list">
      {children}
    </div>
  )
}

export default List;