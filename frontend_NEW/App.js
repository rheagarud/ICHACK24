import DisplayScreen from "./Screens/DisplayScreen"
import InputScreen from "./Screens/InputScreen"

import React from 'react';
import { StyleSheet, View } from 'react-native';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

const Stack = createStackNavigator();

export default function App() {
  return (
    <View style={styles.container}>
      <NavigationContainer>
        <Stack.Navigator>

          <Stack.Screen name="DisplayScreen" component={DisplayScreen} options={{headerShown: false}}/>
          <Stack.Screen name="InputScreen" component={InputScreen} options={{headerShown: false}}/>

        </Stack.Navigator>
      </NavigationContainer>
    </View>
  );
}

// TODO: make work with styles.js
const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'stretch',
    justifyContent: 'center',
  },
});