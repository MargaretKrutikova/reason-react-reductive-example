open Api;

let createDataProvider = (): dataProvider => {
  // Access window.SERVER_DATA from here to get baseUrl and other data relevant to the data provider
  let isDevMode = false;
  let baseUrl = "https://reqres.in/api/";
  isDevMode ? createFakeDataProvider() : createDataProvider(~baseUrl);
};

let store = createDataProvider() |> AppStore.createStore;

let createMake = (~name, ~lense: 'state => 'lense) =>
  Reductive.Lense.createMake(~name, ~lense, store);
