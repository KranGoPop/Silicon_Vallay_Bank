import React from "react"
import Profile from "features/profile/Profile";
import profile_logo from "./profile_logo.svg";
import "./Header.css";
import { useState } from "react";
import { Modal } from "@mui/material";

function Header({settings}) {
  const [is_vivsible, setVisible] = useState(false);
  return (
    <>
    <header className="bank-list-header">
      <div className="header-into">
        <div className="header-logo">Silicon Valley Bank 2 Systems</div>
        <div className="header-desc">By Savely, Gennadiy and Vlad</div>
      </div>
      {settings && <div onClick={() => {setVisible(!is_vivsible)}} className="profile">
        <img src={profile_logo}/>
      </div>}
    </header>
    <Modal open={is_vivsible} onClose={() => {setVisible(false);}}>
      <Profile/>
    </Modal>
    </>
  );
}

export default Header;