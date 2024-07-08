import React from "react";
import { useEffect } from "react";
import AccountInfo from "features/account_info/AccountInfo";
import "./UserPage.css";
import Button from "features/button/Button";
import Header from "features/header/Header";
import { setAccounts, setHistory, selectPageType } from "./UserPageSlice";
import { useDispatch, useSelector } from "react-redux";
import UserAccounts from "features/user_accounts/UserAccounts";
import {
  selectIsError,
  selectError,
  setNoError,
  selectIsLoginUpdate,
  selectUserLogin,
  getLogin,
} from "./UserPageSlice";
import { addErrorItem } from "features/error_list/ErrorListSlice";
import History from "features/history/History";

function UserPage() {
  const dispatch = useDispatch();
  const page = useSelector(selectPageType);
  const is_err = useSelector(selectIsError);
  const err = useSelector(selectError);
  const login = useSelector(selectUserLogin);
  const is_login_update = useSelector(selectIsLoginUpdate);

  useEffect(() => {
    if (is_err) {
      dispatch(setNoError());
      dispatch(addErrorItem(err));
    }
  }, [is_err, err, dispatch]);

  useEffect(() => {
    if (is_login_update) {
      dispatch(getLogin());
    }
  }, [is_login_update, dispatch]);

  let curr_page;

  if (page == "Accounts") {
    curr_page = <UserAccounts/>;
  } else if (page == "History") {
    curr_page = <History/>;
  } else {
    curr_page = <AccountInfo />
  }

  return (
    <>
    <Header settings/>
    {page != 'info' && 
    <div className="page-changer">
      <nav>
        <Button
          onClick={() => {dispatch(setAccounts())}}
          size="large"
          noBorderRight
          color="orange"
          underline={page == 'Accounts'}
          underlineColor={page == 'Accounts' && 'orange'}
          active={page == 'Accounts'}
        >Accounts</Button>
        <Button
          onClick={() => {dispatch(setHistory())}}
          size="large"
          noBorderLeft
          color="orange"
          underline={page == 'History'}
          underlineColor={page == 'History' && 'orange'}
          active={page == 'History'}
        >History</Button>
      </nav>
      <h2 className="page-login-wrapp">You're loggined under <div className="page-login">{login}</div></h2>
      <div className="page-page">{page}</div>
    </div>
    }
    <div className={page != 'info' ? "user-page-container" : "user-page-container-info"}>
      {curr_page}
    </div>
    </>
  )
}

export default UserPage;