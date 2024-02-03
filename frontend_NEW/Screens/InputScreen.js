// InputScreen.js
import React, { useState } from 'react';
import { View, Text, TextInput, Button, StyleSheet } from 'react-native';
import { useNavigation } from '@react-navigation/native';
import DisplayScreen from './DisplayScreen';

const InputScreen = () => {
  const [inputText, setInputText] = useState('');
  const navigation = useNavigation();

  const handleInputChange = (text) => {
    setInputText(text);
  };

  const handleButtonPress = () => {

  };

  return (
    <View style={styles.container}>
      <Text style={styles.header}>Visualise how your expression is parsed!</Text>
      <TextInput
        style={styles.textBox}
        placeholder="Enter your expression here"
        onChangeText={handleInputChange}
        value={inputText}
      />
      <Button title="Submit"
      onPress={() => navigation.navigate('DisplayScreen')}
      style = {styles.roundedButton}
      />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    padding: 16,
  },
  header: {
    fontSize: 24,
    fontWeight: 'bold',
    marginBottom: 16,
  },
  textBox: {
    height: 40,
    borderColor: 'gray',
    borderWidth: 1,
    paddingLeft: 8,
    marginBottom: 16,
    width: '100%',
    borderRadius: 8, // Adjust the value as needed for the desired roundness
  },
  roundedButton: {
    backgroundColor: 'black',
    borderRadius: 8,
  },
});

export default InputScreen;
