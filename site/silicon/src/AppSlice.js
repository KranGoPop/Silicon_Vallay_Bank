import { createSlice, createAsyncThunk } from "@reduxjs/toolkit";
import { Fetch } from "app/fetch";
import { act } from "react-dom/test-utils";

export const getStatus = createAsyncThunk('app/getStatus', async () => {
  return await Fetch({
    command: 'GetStatus'
  });
});

export const getBank = createAsyncThunk('app/getBank', async () => {
  return await Fetch({
    command: 'GetBank'
  });
});

export const setBank = createAsyncThunk('app/setBank', async (bank_name) => {
  return await Fetch({
    command: 'Select_Bank',
    args: {
      bank: bank_name,
    }
  });
});

export const AuthUser = createAsyncThunk('app/auth', async (args) => {
  return await Fetch({
    command: 'AuthenticateUser',
    args
  });
});

export const addUser = createAsyncThunk('app/addUser', async (args) => {
  return await Fetch({
    command: 'AddUser',
    args
  }) && await Fetch({
    command: 'AuthenticateUser',
    args
  });
});

export const setNameAndSurname = createAsyncThunk('app/setNameAndSurname', async ({name, surname}) => {
  await Fetch({
    command: 'SetName',
    args: {
      name
    }
  });
  return await Fetch({
    command: 'SetSurname',
    args: {
      surname,
    }
  });
});

export const setAddress = createAsyncThunk('app/setAddress', async (address) => {
  return await Fetch({
    command: 'SetAddress',
    args: {
      address
    }
  });
});

export const setPassport = createAsyncThunk('app/setPassport', async (passport) => {
  return await Fetch({
    command: 'SetPassport',
    args: {
      passport: String(passport)
    }
  });
});

export const logOut = createAsyncThunk('app/logOut', async () => {
  return await Fetch({
    command: 'Logout'
  });
});

export const deleteAcc = createAsyncThunk('app/deleteAcc', async () => {
  return await Fetch({
    command: 'DeleteUser'
  });
});

export const noToken = createAsyncThunk('app/noToken', async () => {
  return await Fetch({
    command: 'NoToken'
  });
});

const app_slice = createSlice({
  name: "app",
  initialState: {
    is_token: false,
    is_user: false,
    is_error: false,
    is_data_changed: true,
    is_login_page: true,
    sign_up_stage: 0,
    pendings: {
      get_status: false,
      get_bank: false,
    },
    bank_name: "",
    bank_city: "",
    error: "",
  },
  reducers: {
    setNoError: (state) => {
      state.is_error = false;
    },
    dataChanged: (state) => {
      state.is_data_changed = true;
    },
    setLogInPage: (state) => {
      state.is_login_page = true;
    },
    setSignUpPage: (state) => {
      state.is_login_page = false;
    },
    incrementSignUpStage: (state) => {
      state.sign_up_stage++;

      if (state.sign_up_stage > 3) {
        state.is_data_changed = true;
        state.sign_up_pending = false;
        state.sign_up_stage = 0;
      }
    }
  },
  extraReducers: (builder) => {
    builder.addCase(getStatus.pending, (state, action) => {
      state.pendings.get_status = true;
    })
    .addCase(getStatus.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
      state.is_data_changed = false;
      state.pendings.get_status = false;
    })
    .addCase(getStatus.fulfilled, (state, action) => {
      state.is_token = action.payload.result.is_token;
      state.is_user = action.payload.result.is_user;
      state.is_data_changed = false;
      state.pendings.get_status = false;
    })
    .addCase(getBank.pending, (state, action) => {
      state.pendings.get_bank = true;
    })
    .addCase(getBank.rejected, (state, action) => {
      state.is_error = true;
      state.pendings.get_bank = false;
      state.error = action.error.message;
    })
    .addCase(getBank.fulfilled, (state, action) => {
      state.pendings.get_bank = false;
      state.bank_name = action.payload.result.name;
      state.bank_city = action.payload.result.city;
    })
    .addCase(setBank.fulfilled, (state, action) => {
      state.is_data_changed = true;
    })
    .addCase(setBank.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(AuthUser.fulfilled, (state, action) => {
      state.is_data_changed = true;
    })
    .addCase(AuthUser.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(addUser.fulfilled, (state, action) => {
      state.sign_up_stage = 1;
    })
    .addCase(addUser.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(setNameAndSurname.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(setNameAndSurname.fulfilled, (state) => {
      state.sign_up_stage = 2;
    })
    .addCase(setAddress.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(setAddress.fulfilled, (state, action) => {
      state.sign_up_stage = 3;
    })
    .addCase(setPassport.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(setPassport.fulfilled, (state, action) => {
      state.sign_up_stage = 0;
      state.is_data_changed = true;
    })
    .addCase(logOut.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(deleteAcc.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    })
    .addCase(deleteAcc.fulfilled, (state) => {
      state.is_data_changed = true;
      state.is_login_page = true;
    })
    .addCase(logOut.fulfilled, (state) => {
      state.is_data_changed = true;
      state.is_login_page = true;
    })
    .addCase(noToken.fulfilled, (state) => {
      state.is_data_changed = true;
      state.is_login_page = true;
    })
    .addCase(noToken.rejected, (state, action) => {
      state.is_error = true;
      state.error = action.error.message;
    });
  }
});

export const {setNoError, dataChanged, setLogInPage, setSignUpPage, incrementSignUpStage} = app_slice.actions;
export const app_reducer = app_slice.reducer;

export const selectIsToken = (state) => state.app.is_token;
export const selectIsUser = (state) => state.app.is_user;
export const selectIsError = (state) => state.app.is_error;
export const selectAppError = (state) => state.app.error;
export const selectChange = (state) => state.app.is_data_changed;
export const selectBankName = (state) => state.app.bank_name;
export const selectBankCity = (state) => state.app.bank_city;
export const selectIsLogin = (state) => state.app.is_login_page;
export const selectSignUpStage = (state) => state.app.sign_up_stage;
export const selectSignUpPending = (state) => state.app.sign_up_pending;

export const selectGetStatusIsPending = (state) => state.app.pendings.get_status;
export const selectGetBankIsPending = (state) => state.app.pendings.get_bank;