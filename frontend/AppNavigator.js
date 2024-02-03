import { createAppContainer } from 'react-navigation';
import { createStackNavigator } from 'react-navigation-stack';

import InputScreen from './Screens/InputScreen';
import DisplayScreen from './Screens/DisplayScreen';

const AppNavigator = createStackNavigator(
  {
    Input: InputScreen,
    Display: DisplayScreen,
  },
  {
    initialRouteName: 'Input',
  }
);

export default createAppContainer(AppNavigator);