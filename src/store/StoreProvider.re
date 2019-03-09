open Api;

let createDataProvider = (): dataProvider => {
  let isDevMode = false;
  let baseUrl = "https://reqres.in/api/";
  isDevMode ? createFakeDataProvider() : createDataProvider(~baseUrl);
};

let store = createDataProvider() |> AppStore.createStore;

let createMake: (
  ~name: string, 
  ~lense: ReactTemplate.AppStore.appState => 'lense,
  ~component: (
    ~state: 'lense,
    ~dispatch: AppStore.action('state) => unit,
    array(ReasonReact.reactElement)
  ) => ReasonReact.component('a, 'b, 'c),
  array(ReasonReact.reactElement)
) =>
ReasonReact.component(
  Reductive.Lense.state('lense),
  ReasonReact.noRetainedProps, 
  Reductive.Lense.action
) = (~name, ~lense: 'state => 'lense) => Reductive.Lense.createMake(~name, ~lense, Obj.magic(store));
