import { create } from "@mui/material/styles/createTransitions";
import { createSlice, createAsyncThunk } from "@reduxjs/toolkit";
import { Fetch } from "app/fetch";
import { noToken, logOut, deleteAcc } from "AppSlice";

export const getAccounts = createAsyncThunk('user/getAccs', async () => {
  return await Fetch({
    command: 'GetAccounts'
  });
});

export const getHistory = createAsyncThunk('user/getHistory', async () => {
  return await Fetch({
    command: 'GetTransactionHistory'
  });
});

export const cancelTrans = createAsyncThunk('user/cancelTrans', async (trans_id) => {
  return await Fetch({
    command: 'RequestCancelTransaction',
    args: {
      transaction_id: trans_id,
    },
  });
});

export const getUserInfo = createAsyncThunk('user/getUserInfo', async () => {
  return await Fetch({
    command: 'GetUserInfo'
  });
});

export const setUserInfo = createAsyncThunk('user/setUserInfo', async ({name, surname, address, passport}) => {
  await Fetch({
    command: 'SetName',
    args: {
      name
    }
  });
  await Fetch({
    command: 'SetSurname',
    args: {
      surname,
    },
  });
  await Fetch({
    command: 'SetPassport',
    args: {
      passport: String(passport),
    },
  });
  return await Fetch({
    command: 'SetAddress',
    args: {
      address,
    },
  });
});

export const changePass = createAsyncThunk('user/changePass', async ({old_pass, new_pass}) => {
  return await Fetch({
    command: 'ChangePassword',
    args: {
      curr_password: old_pass,
      new_password: new_pass,
    },
  });
});

export const changeLogin = createAsyncThunk('user/changeLogin', async ({new_login}) => {
  return await Fetch({
    command: 'ChangeLogin',
    args: {
      new_login: new_login,
    },
  });
});

export const closeAcc = createAsyncThunk('user/closeAcc', async (acc_id) => {
  return await Fetch({
    command: 'CloseAccount',
    args: {
      account_id: acc_id,
    },
  });
});

export const openAccount = createAsyncThunk('user/openAcc', async (acc_type) => {
  return await Fetch({
    command: 'OpenAccount',
    args: {
      account_type: acc_type,
    }
  });
});

export const getAccInfo = createAsyncThunk('user/getAccInfo', async (acc_id) => {
  return await Fetch({
    command: 'AccountInfo',
    args: {
      account_id: acc_id,
    },
  });
});

export const transferMoney = createAsyncThunk('user/transfer', async ({srcAccId, destAccId, amount}) => {
  return await Fetch({
    command: "TransferMoney",
    args: {
      source_account_id: String(srcAccId),
      destination_account_id: String(destAccId),
      amount: amount,
    },
  });
});

export const depositMoney = createAsyncThunk('user/deposit', async ({accId, amount}) => {
  return await Fetch({
    command: "DepositMoney",
    args: {
      account_id: String(accId),
      amount: amount,
    },
  });
});

export const withdrawMoney = createAsyncThunk('user/widthdraw', async ({accId, amount}) => {
  return await Fetch({
    command: "WithdrawMoney",
    args: {
      account_id: String(accId),
      amount: amount,
    },
  });
});

export const getLogin = createAsyncThunk('app/getLogin', async () => {
  return await Fetch({
    command: 'GetLogin',
  });
});

let initialState = {
  user_page: 'Accounts',
  is_acc_change: true,
  is_his_change: true,
  is_user_info_change: true,
  accounts: [],
  history: [],
  user_info: {
    name: '',
    surname: '',
    address: '',
    passport: '',
  },
  is_error: false,
  error: "",
  is_info_loaded: false,
  info: {},
  current_acc_id: 0,
  current_acc_type: 'debit',
  login: "",
  is_login_change: true,
  modal_acc: 'none',
};

const user_slice = createSlice({
  name: "user",
  initialState,
  reducers: {
    setAccounts: (state) => {
      state.user_page = 'Accounts';
    },
    setHistory: (state) => {
      state.user_page = 'History';
    },
    setNoError: (state) => {
      state.is_error = false;
    },
    setName: (state, action) => {
      state.user_info.name = action.payload;
    },
    setSurname: (state, action) => {
      state.user_info.surname = action.payload;
    },
    setAddress: (state, action) => {
      state.user_info.address = action.payload;
    },
    setPassport: (state, action) => {
      state.user_info.passport = action.payload;
    },
    backPage: (state) => {
      state.user_page = 'Accounts';
    },
    showInfo: (state, action) => {
      state.user_page = 'info';
      state.is_info_loaded = false;
      state.info = {};
      state.current_acc_id = action.payload.id;
      state.current_acc_type = action.payload.type;
    },
    noUser: () => {
      return initialState;
    },
    setModalAcc: (state, action) => {
      state.modal_acc = action.payload;
    }
  },
  extraReducers: (builder) => {
    builder.addCase(getAccounts.fulfilled, (state, action) => {
      state.accounts = action.payload.result;
      state.is_acc_change = false;
    })
    .addCase(getAccounts.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(getHistory.fulfilled, (state, action) => {
      state.history = action.payload.result;
      state.is_his_change = false;
    })
    .addCase(getHistory.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(cancelTrans.fulfilled, (state) => {
      state.is_his_change = true;
      state.is_info_loaded = false;
    })
    .addCase(cancelTrans.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(getUserInfo.fulfilled, (state, action) => {
      state.user_info = action.payload.result;
      state.user_info.passport = state.user_info.passport === 0 ? '' : state.user_info.passport;
      state.is_user_info_change = false;
    })
    .addCase(getUserInfo.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(setUserInfo.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(changeLogin.fulfilled, (state) => {
      state.is_login_change = true;
    })
    .addCase(changeLogin.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(changePass.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(closeAcc.fulfilled, (state) => {
      state.is_acc_change = true;
      state.user_page = 'Accounts';
    })
    .addCase(closeAcc.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(openAccount.fulfilled, (state) => {
      state.is_acc_change = true;
    })
    .addCase(openAccount.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(getAccInfo.fulfilled, (state, action) => {
      state.info = action.payload.result;
      state.is_info_loaded = true;
    })
    .addCase(getAccInfo.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(transferMoney.fulfilled, (state) => {
      state.is_his_change = true;
      state.is_info_loaded = false;
      state.modal_acc = 'none';
      state.is_acc_change = true;
    })
    .addCase(transferMoney.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(depositMoney.fulfilled, (state) => {
      state.is_info_loaded = false;
      state.is_his_change = true;
      state.modal_acc = 'none';
      state.is_acc_change = true;
    })
    .addCase(depositMoney.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(withdrawMoney.fulfilled, (state) => {
      state.is_info_loaded = false;
      state.is_his_change = true;
      state.modal_acc = 'none';
      state.is_acc_change = true;
    })
    .addCase(withdrawMoney.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(getLogin.fulfilled, (state, action) => {
      state.is_login_change = false;
      state.login = action.payload.result.login;
    })
    .addCase(getLogin.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(deleteAcc.fulfilled || logOut.fulfilled || noToken.fulfilled, (state) => {
      return initialState;
    });
  }
});

export const {
  setAccounts,
  setHistory,
  setNoError,
  setName,
  setSurname,
  setAddress,
  setPassport,
  showInfo,
  backPage,
  noUser,
  setModalAcc,
} = user_slice.actions;

export const user_reducer = user_slice.reducer;

export const selectPageType = (state) => state.user.user_page;
export const selectHistory = (state) => state.user.history;
export const selectAccounts = (state) => state.user.accounts;
export const selectIsAccChange = (state) => state.user.is_acc_change;
export const selectIsHistoryChange = (state) => state.user.is_his_change;
export const selectIsError = (state) => state.user.is_error;
export const selectError = (state) => state.user.error;
export const selectUserInfo = (state) => state.user.user_info;
export const selectIsUserInfoChange = (state) => state.user.is_user_info_change;
export const selectAccInfo = (state) => state.user.info;
export const selectIsInfoLoaded = (state) => state.user.is_info_loaded;
export const selectCurrInfoId = (state) => state.user.current_acc_id;
export const selectUserLogin = (state) => state.user.login;
export const selectIsLoginUpdate = (state) => state.user.is_login_change;
export const selectModalAcc = (state) => state.user.modal_acc;