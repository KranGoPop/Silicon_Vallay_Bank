import React from "react";
import Input from "features/input/Input";
import Button from "features/button/Button";
import { useState } from "react";
import { useDispatch, useSelector } from "react-redux";
import {
  AuthUser,
  setSignUpPage,
} from "AppSlice";
import MainLogBlock from "features/main_log_block/MainLogBlock";
import List from "features/list/List";
import Suggest from "features/suggest/Suggest";
// import slice'ов

function LogIn() {
  const dispatch = useDispatch();
  const [login, setLogin] = useState('');
  const [password, setPassword] = useState('');
  
  return (
    <MainLogBlock type="Log In" inputs={(
      <List>
        <Input text="Login" value={login} onChange={(event) => {setLogin(event.target.value)}}/>
        <Input text="Password" type="password" value={password} onChange={(event) => {setPassword(event.target.value)}} />
      </List>
    )} buttons={(
      <>
        <Button color="orange" onClick={() => {dispatch(AuthUser({login, password}))}}>Log In</Button>
        <Suggest suggest="Don't have an account?">
          <Button color="void" onClick={() => {dispatch(setSignUpPage())}}>Sign Up</Button>
        </Suggest>
      </>
    )}/>
  )
}

export default LogIn;