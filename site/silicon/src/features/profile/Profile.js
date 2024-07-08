import React from "react";
import { useEffect, useState } from "react";
import { useSelector, useDispatch } from "react-redux";
import "features/profile/Profile.css"
import Input from "features/input/Input";
import Button from "features/button/Button";
import List from "features/list/List";
import {
  selectUserInfo,
  selectIsUserInfoChange,
  getUserInfo,
  setName,
  setSurname,
  setAddress,
  setPassport,
  setUserInfo,
  changeLogin,
  changePass,
  selectIsLoginUpdate,
  selectUserLogin,
} from "features/user_page/UserPageSlice";
import { deleteAcc, noToken } from "AppSlice";

function Profile() {
  const dispatch = useDispatch();
  const user_info = useSelector(selectUserInfo);
  const is_user_info_change = useSelector(selectIsUserInfoChange);
  const login = useSelector(selectUserLogin);
  const is_login_update = useSelector(selectIsLoginUpdate);
  
  const [new_login, setNewLogin] = useState('');

  let name = user_info.name;
  let surname = user_info.surname;
  let address = user_info.address;
  let passport = user_info.passport;
  let is_verified = false;
  if (name != "" && surname != "" && address != "" && passport) {
    is_verified = true;
  }

  const [old_pass, setOldPass] = useState('');
  const [new_pass, setNewPass] = useState('');

  useEffect(() => {
    if (is_user_info_change) {
      dispatch(getUserInfo())
    }
  }, [is_user_info_change, dispatch]);

  return (
    <>
    <div className="profile-acc-info">
      <div className="profile-acc-info-item">
        <List>
          <div>
            <List>
              <div className="react-login">Your login: {login}</div>
              <Input text="New Login" value={new_login} onChange={(event) => {setNewLogin(event.target.value)}}/>
            </List>
            <Button onClick={() => {dispatch(changeLogin({new_login}))}}>Change login</Button>
          </div>
          <div>
            <List>
              <Input text="Old Password" value={old_pass} onChange={(event) => {setOldPass(event.target.value)}}/>
              <Input text="New Password" value={new_pass} onChange={(event) => {setNewPass(event.target.value)}}/>
            </List>
            <Button onClick={() => {dispatch(changePass({old_pass, new_pass}))}}>Change password</Button>
          </div>
        </List>
      </div>
      <div className="profile-acc-info-item">
      <List>
        <div>
          <List>
            <Input text="Name" value={name} onChange={(event) => {dispatch(setName(event.target.value))}}/>
            <Input text="Surname" value={surname} onChange={(event) => {dispatch(setSurname(event.target.value))}}/>
            <Input text="Address" value={address} onChange={(event) => {dispatch(setAddress(event.target.value))}}/>
            <Input text="Passport" value={passport} onChange={(event) => {dispatch(setPassport(event.target.value))}}/>
            {is_verified ? <div>You're revified</div> : <div>You're not tusted X</div>}
          </List>
          <Button onClick={() => {dispatch(setUserInfo({name, surname, address, passport}))}}>Change Account Info</Button>
        </div>
      </List>
      </div>
      <div className="profile-acc-info-item">
        <List>
          <div><Button color="blue" onClick={()=>{dispatch(noToken())}}>Log Out</Button></div>
          <div><Button color="red" onClick={()=>{dispatch(deleteAcc())}}>Delete Acc</Button></div>
        </List>
      </div>
    </div>
    </>
  )
}

export default Profile;