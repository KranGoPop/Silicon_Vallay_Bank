import React from "react";
import "./DepositAccountInfo.css";
import Info from "features/info/Info";

function DepositAccountInfo({acc_id}) {
  let percent = 0.1;
  let start_date = "02.May.2023";
  let last_update = "05.May.2023";
  let manage_timeout = 5;
  let withdraw_timeout = 10;
  return (
    <div className="deposit-acc-info">
      <h1>Info</h1>
      <div className="info">
        <Info>
          <div><div>Start Date</div><div>{new Date(start_date).toUTCString()}</div></div>
          <div><div>Manage Timeout</div><div>{manage_timeout}s</div></div>
          <div><div>Withdraw Timeout</div><div>{withdraw_timeout}s</div></div>
          <div><div>Add percent</div><div>{percent}%</div></div>
        </Info>
      </div>
    </div>
  )
}

export default DepositAccountInfo;