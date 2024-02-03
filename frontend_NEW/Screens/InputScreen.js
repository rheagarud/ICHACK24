// InputScreen.js
import React, { useState } from 'react';
import { View, Text, TextInput, Button, StyleSheet } from 'react-native';
import { useNavigation } from '@react-navigation/native';
import { styles } from '../styles';

const isInputValid = (input) => {
  return input.trim() !== '';
};

const InputScreen = () => {
  const [inputText, setInputText] = useState('');
  const [errorText, setErrorText] = useState('');
  const navigation = useNavigation();

  const handleInputChange = (text) => {
    setInputText(text);
    setErrorText('');
  };

  const handleButtonPress = () => {
    if (isInputValid(inputText)) {
      navigation.navigate('DisplayScreen')
    } else {
      setErrorText('Invalid input. Please enter a valid expression.')
    }
  }

  return (
    <View style={styles.container}>

      <Text style={styles.header}>Visualise your expression!</Text>

      <TextInput
        style={styles.textBox}
        placeholder="Enter your expression here"
        onChangeText={handleInputChange}
        value={inputText}
      />

      <Text style={styles.errorText}>{errorText}</Text>

      <Button title="Parse"
        onPress={handleButtonPress}
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
    borderRadius: 8,
  },
  roundedButton: {
    backgroundColor: 'black',
    borderRadius: 8,
  },
  errorText: {
    color: 'red',
    marginBottom: 16,
  },
});

export default InputScreen;
