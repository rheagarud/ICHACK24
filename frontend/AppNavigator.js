import { createStackNavigator } from '@react-navigation/stack';

import InputScreen from './Screens/InputScreen';
import DisplayScreen from './Screens/DisplayScreen';

const Stack = createStackNavigator();
function AppNavigator() {
  return (
    <Stack.Navigator>
      <Stack.Screen name="Input" component={InputScreen} />
      <Stack.Screen name="Display" component={DisplayScreen} />
    </Stack.Navigator>
  );
}

// const AppNavigator = createStackNavigator(
//   {
//     Input: InputScreen,
//     Display: DisplayScreen,
//   },
//   {
//     initialRouteName: 'Input',
//   }
// );

export default AppNavigator;