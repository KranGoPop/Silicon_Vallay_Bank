import { configureStore } from '@reduxjs/toolkit';
import { bank_list_reducer } from "features/bank_list/BankListSlice";
import { error_reducer } from 'features/error_list/ErrorListSlice';
import { app_reducer } from 'AppSlice';
import { user_reducer } from 'features/user_page/UserPageSlice';

export const store = configureStore({
  reducer: {
    bank: bank_list_reducer,
    error: error_reducer,
    app: app_reducer,
    user: user_reducer,
  },
});
