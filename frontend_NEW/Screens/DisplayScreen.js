import React from 'react';
import { View, Text, Button } from 'react-native';
import { styles } from '../styles';
import { useNavigation } from '@react-navigation/native';

const DisplayScreen = ({ route }) => {
  const navigation = useNavigation();
  const expression = route.params.inputText;

  return (
    <View>

      <Text>Display Screen</Text>

      <Button
        title="Do again."
        onPress={() => navigation.navigate('InputScreen')}
      />
      
    </View>
  );
};

export default DisplayScreen;
