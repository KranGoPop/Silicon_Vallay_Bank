import React from "react";
import "./BackButton.css";
import back_button from "./back.svg";
import Button from "features/button/Button";

function BackButton({
  color="blue",
  onClick
}) {
  return (
    <Button color={color} onClick={onClick}>
      <div className="back-button_img"><img src={back_button}/></div>
      <div>Back</div>
    </Button>
  )
}

export default BackButton;