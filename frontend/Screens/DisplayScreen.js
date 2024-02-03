import React from 'react';
import { View, Text, Button } from 'react-native';

const DisplayScreen = ({ navigation }) => {
  return (
    <View>
      <Text>Display Screen</Text>
      <Button
        title="Do again."
        onPress={() => navigation.navigate('Input')}
      />
    </View>
  );
};

export default DisplayScreen;
