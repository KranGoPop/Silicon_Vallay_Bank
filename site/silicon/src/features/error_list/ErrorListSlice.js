import {createSlice} from "@reduxjs/toolkit";

const error_slice = createSlice({
  name: "error",
  initialState: {
    errors: [],
    last_id: 0,
  },
  reducers: {
    addErrorItem: (state, action) => {state.errors.push({id: state.last_id++, error: action.payload, visible: true})},
    removeErrorItem: (state, action) => {state.errors.find(elem => elem.id == action.payload).visible = false} 
  }
});

export const {addErrorItem, removeErrorItem} = error_slice.actions;

export const selectErrors = (state) => state.error.errors;

export const error_reducer = error_slice.reducer;