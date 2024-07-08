import {createSlice, createAsyncThunk} from "@reduxjs/toolkit";
import {Fetch} from "app/fetch";
import { act } from "react-dom/test-utils";

export const getBanks = createAsyncThunk('bank/getBanks', async () => {
  let res = await (Fetch({
      command: "Show_Banks"
  }));
  return res.result;
});

const bank_list_slice = createSlice({
  name: "bank",
  initialState: {
    banks: [],
    status: 'idle',
    error: ""
  },
  reducers: {
  },
  extraReducers: (builder) => {
    builder.addCase(getBanks.rejected, (state, action) => {
      state.status = 'error';
      state.error = action.error.message;
    })
    .addCase(getBanks.fulfilled, (state, action) => {
      state.status = 'success';
      state.banks = action.payload;
    });
  }
});

export const bank_list_reducer = bank_list_slice.reducer;

// export const {setNoError} = bank_list_slice.actions;

export const selectBanks = (state) => state.bank.banks;
export const selectStatus = (state) => state.bank.status;
export const selectError = (state) => state.bank.error;