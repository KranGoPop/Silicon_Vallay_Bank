import React from "react"
import { useSelector } from "react-redux";
import SignUp from "features/signup/SignUp";
import AddUserInfo from "features/add_user_info/AddUserInfo";
import { selectSignUpPending, selectSignUpStage } from "AppSlice";

function SignUpWrapper() {
  const stage = useSelector(selectSignUpStage);

  let answer;

  if (stage == 0) {
    answer = <SignUp />;
  }
  else if (stage < 4) {
    answer = <AddUserInfo step={stage} />;
  }
  else {
    answer = <div>Error</div>;
  }

  return answer;
}

export default SignUpWrapper;