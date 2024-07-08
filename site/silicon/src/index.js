import React from 'react';
import { createRoot } from 'react-dom/client';
import { Provider } from 'react-redux';
import { store } from './app/store';
import App from './App';
import './index.css';
import { ThemeProvider } from "@mui/material/styles";
import theme from "assets/theme";
import ErrorList from 'features/error_list/ErrorList';

const container = document.getElementById('root');
const root = createRoot(container);

root.render(
  // <React.StrictMode>
    <ThemeProvider theme={theme}>
      <Provider store={store}>
        <App />
        <ErrorList />
      </Provider>
    </ThemeProvider>
  // </React.StrictMode>
);
