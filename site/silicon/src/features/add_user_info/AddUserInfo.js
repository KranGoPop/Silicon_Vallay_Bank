import React from "react";
import { useState } from "react";
import { useDispatch } from "react-redux";
import "./AddUserInfo.css"
import Input from "features/input/Input";
import Button from "features/button/Button";
import {
  incrementSignUpStage,
  setNameAndSurname,
  setAddress as sendAddress,
  setPassport as sendPassport,
  setLogInPage
} from "AppSlice";
import MainLogBlock from "features/main_log_block/MainLogBlock";
import List from "features/list/List";
import Suggest from "features/suggest/Suggest";
import ButtonBlock from "features/button_block/ButtonBlock";
import { addErrorItem } from "features/error_list/ErrorListSlice";

function AddUserInfo({step}) { 
  const dispacth = useDispatch();
  const [name, setName] = useState('');
  const [surname, setSurname] = useState('');
  const [address, setAddress] = useState('');
  const [passport, setPassport] = useState('');

  let inputs;
  let buttons;

  if (step == 1) {

    inputs = (
      <>
      <List>
        <Input text={"Name"} value={name} onChange={(event) => {setName(event.target.value)}}/>
        <Input text={"Surname"} value={surname} onChange={(event) => {setSurname(event.target.value)}} />
      </List>
      </>
    );

    buttons = (
      <>
        <Button onClick={() => {
          if (name === '' || surname === '') {
            dispacth(addErrorItem('You should pass name and surname'));
          } else {
            dispacth(setNameAndSurname({name, surname}));
          }     
        }}>Next</Button>
      </>
    );
  }
  else if (step == 2) {

    inputs = (
      <>
        <Input text="Address" value={address} onChange={(event) => {setAddress(event.target.value)}}/>
      </>
    );
    buttons = (
      <>
        <ButtonBlock>
          <Button onClick={() => {dispacth(sendAddress(address))}}>Next</Button>
          <Button onClick={() => {dispacth(incrementSignUpStage())}}>Skip</Button>
        </ButtonBlock>
      </>
    );
  }
  else if (step == 3) {

    inputs = (
      <>
        <Input text="Passport" value={passport} onChange={(event) => {setPassport(event.target.value)}}/>
      </>
    );
    buttons = (
      <>
      <ButtonBlock>
        <Button onClick={() => {dispacth(sendPassport(passport))}}>Next</Button>
        <Button onClick={() => {dispacth(incrementSignUpStage())}}>Skip</Button>
      </ButtonBlock>
      </>
    );
  }
  
  return (
    <MainLogBlock type="Sing Up" inputs={inputs} buttons={(
      <>
        <ButtonBlock>
          {buttons}
        </ButtonBlock>
        <Suggest suggest="Have an account?">
          <Button color="void" onClick={() => {dispacth(setLogInPage())}}>Log In</Button>
        </Suggest>
      </>
    )} />
  );
}

export default AddUserInfo;