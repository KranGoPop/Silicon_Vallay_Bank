import React from "react";
import { useState } from "react";
import { useDispatch } from "react-redux";
import Button from "features/button/Button";
import Input from "features/input/Input";
import MainLogBlock from "features/main_log_block/MainLogBlock";
import List from "features/list/List";
import Suggest from "features/suggest/Suggest";
import { setLogInPage, addUser } from "AppSlice";
import { addErrorItem } from "features/error_list/ErrorListSlice";

function SignUp() {
  const dispatch = useDispatch();
  const [login, setLogin] = useState('');
  const [pass1, setPass1] = useState('');
  const [pass2, setPass2] = useState('');

  return (
    <MainLogBlock type="Sing Up" inputs={(
      <List>
        <Input value={login} text="Login" onChange={(event) => {setLogin(event.target.value)}}/>
        <Input value={pass1} type="password" text="Password" onChange={(event) => {setPass1(event.target.value)}} />
        <Input value={pass2} type="password" text="Confirm password" onChange={(event) => {setPass2(event.target.value)}} />
      </List>
    )} buttons={(
      <>
        <Button color='orange' text="Sign Up" onClick={() => {
          if (pass1 != pass2) {
            dispatch(addErrorItem('Passwords not equal!'));
          }
          else {
            dispatch(addUser({
              login,
              password: pass1
            }));
          }
        }}>Sign Up</Button>
        <Suggest suggest="Have an account?">
          <Button color="void" onClick={() => {dispatch(setLogInPage())}}>Log In</Button>
        </Suggest>
      </>
    )}/>
  );
}

export default SignUp;