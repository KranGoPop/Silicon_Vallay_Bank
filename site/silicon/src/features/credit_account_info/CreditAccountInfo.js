import React from "react";
import "./CreditAccountInfo.css";
import Info from "features/info/Info";

function CreditAccountInfo({acc_id}) {
  let commission = 10;
  let percent = 0.10;
  let start_date = "02.May.2023";
  let last_update = "05.May.2023";
  let credit_limit = 1000000;
  let credit_cycle = 10;
  return (
    <div className="credit-acc-info">
      <h1>Info</h1>
      <div className="info">
        <Info>
          <div><div>Start Date</div><div>{new Date(start_date).toUTCString()}</div></div>
          <div><div>Credit Cycle</div><div>{credit_cycle}s</div></div>
          <div><div>Commission</div><div>{commission}%</div></div>
          <div><div>Credit %</div><div>{percent * 100}%</div></div>
          <div><div>Credit Limit</div><div>{credit_limit}$</div></div>
        </Info>
      </div>
    </div>
  )
}

export default CreditAccountInfo;