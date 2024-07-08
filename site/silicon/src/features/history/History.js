import React from "react";
import { useEffect } from "react";
import { useSelector, useDispatch } from "react-redux";
import { selectHistory, getHistory, selectIsHistoryChange } from "features/user_page/UserPageSlice";
import Transaction from "features/transaction/Transaction";
import List from "features/list/List";

function History({accId}) {
  const dispatch = useDispatch();
  const history = useSelector(selectHistory);
  const is_his_change = useSelector(selectIsHistoryChange);

  useEffect(() => {
    if (is_his_change) {
      dispatch(getHistory());
    }
  }, [is_his_change, dispatch]);

  return (
    <List>
      {history.map(item => 
        (!accId && <Transaction key={item.id} trans={item}/>)
        ||
        (accId && (item.src_acc_id == accId || item.dest_acc_id == accId) && <Transaction key={item.id} trans={item}/>)
      ).reverse()}
    </List>
  );
}

export default History;