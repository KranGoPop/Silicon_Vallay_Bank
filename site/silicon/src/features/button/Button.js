import React from "react";
import "./Button.css";
import { useState } from "react";

function Button({
  onClick,
  children,
  color = 'orange',
  size = "medium",
  noBorderLeft,
  noBorderRight,
  underline,
  underlineColor = '#E09B5B',
  active,
  ghost,
}) {
  const [on_focus, setFocus] = useState(false);
  let classes = "react-button "

  if (underlineColor == 'orange') {
    underlineColor = '#CE9E71';
  }

  if (color == 'orange') {
    color = '#FFDCBB';
  } else if (color == 'void') {
    color = '#00000000';
  } else if (color == 'blue') {
    color = "#CFF6FF";
  } else if (color == "green") {
    color = "#94F2A3";
  } else if (color == "red") {
    color = "#FD6F6F";
  } else if (color == "purple") {
    color = "#F9B5FF";
  } else if (color == "gold") {
    color = "#FFE99C";
  }
  
  if (size == "large") {
    classes += "react-size_large";
  } else if (size == "mega") {
    classes += "react-size_mega";
  } else {
    classes += "react-size_def";
  }

  let tl = undefined;
  let bl = undefined;
  let tr = undefined;
  let br = undefined;

  if (noBorderLeft) {
    tl = 0;
    bl = 0;
  }

  if (noBorderRight) {
    tr = 0;
    br = 0;
  }

  return (
    <button className={classes} onClick={!ghost ? onClick : null} style={{
      backgroundColor: color,
      borderTopLeftRadius: tl,
      borderTopRightRadius: tr,
      borderBottomLeftRadius: bl,
      borderBottomRightRadius: br,
      color: active ? '#000' : undefined,
      cursor: ghost && 'default',
      opacity: ghost && 0,
    }}>
      {children}
      {(underline) && <div className="react-button-underline" style={{backgroundColor: underlineColor}}></div>}
    </button>
  );
}

export default Button;