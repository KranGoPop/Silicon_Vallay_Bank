import React from 'react';
import { useEffect } from 'react';
import './App.css';
import { useSelector, useDispatch } from 'react-redux';
import {
  getStatus,
  getBank,
  setNoError,
  selectIsToken,
  selectIsUser,
  selectIsError,
  selectAppError,
  selectChange,
  selectIsLogin,
  selectGetStatusIsPending,
} from 'AppSlice';
import { addErrorItem } from 'features/error_list/ErrorListSlice';
import BankList from 'features/bank_list/BankList';
import LogIn from 'features/login/LogIn';
import SignUpWrapper from 'features/sign_up_wrapper/SignUpWrapper';
import UserPage from "features/user_page/UserPage";

function App() {
  const dispatch = useDispatch();
  const is_token = useSelector(selectIsToken);
  const is_user = useSelector(selectIsUser);
  const is_erorr = useSelector(selectIsError);
  const is_change = useSelector(selectChange);
  const is_login_page = useSelector(selectIsLogin);
  const error = useSelector(selectAppError);
  const is_get_status_pending = useSelector(selectGetStatusIsPending);

  useEffect(() => {
    if (is_change && !is_get_status_pending) {
      dispatch(getStatus());
    }
  }, [is_change, is_get_status_pending, dispatch]);

  useEffect(() => {
    if (is_token) {
      dispatch(getBank());
    }
  }, [is_token, dispatch]);

  useEffect(() => {
    if (is_erorr) {
      dispatch(setNoError());
      dispatch(addErrorItem(error));
    }
  }, [is_erorr, error, dispatch]);

  let result;

  if (!is_token) {
    result = <BankList/>
  } else if (is_token && !is_user) {
    if (is_login_page) {
      result = <LogIn />;
    } else {
      result = <SignUpWrapper />;
    }
  } else {
    result = <UserPage />;
  }

  return result;
}

export default App;