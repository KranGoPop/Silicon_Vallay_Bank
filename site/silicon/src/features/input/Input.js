import React from "react";
import "./Input.css";
import { useEffect, useState, useRef } from "react";

function Input({text, value, onChange, bgColor='yellow', type='text'}) {
  const [ph_class, setPHClass] = useState("react-input-placeholder");
  const [on_focus, setFocus] = useState(false);
  const input = useRef(null);

  if (bgColor == 'yellow') {
    bgColor = "#FFFCE2";
  }
  useEffect(() => {
    if (value !== '' || on_focus) {
      setPHClass("react-input-placeholder react-input-up");
    } else {
      setPHClass("react-input-placeholder");
    }
  }, [value === '', on_focus])

  return (
    <div className="react-input-wrapp" onClick={()=>{input.current.focus()}}>
      <div className={ph_class}>{text}</div>
      <input
        ref={input}
        className="react-input"
        type={type}
        placeholder=""
        value={value}
        onFocus={()=>{setFocus(true);}}
        onBlur={()=>{setFocus(false);}}
        onChange={onChange}
        style={{backgroundColor: bgColor}}
      />
    </div>
  );
}

export default Input;