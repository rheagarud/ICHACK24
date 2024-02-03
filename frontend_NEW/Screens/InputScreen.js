// InputScreen.js
import React, { useState } from 'react';
import { View, Text, TextInput, Button, StyleSheet } from 'react-native';
import { useNavigation } from '@react-navigation/native';
import { styles } from '../styles';

const InputScreen = () => {
  const [inputText, setInputText] = useState('');
  const navigation = useNavigation();

  const handleInputChange = (text) => {
    setInputText(text);
  };

  const handleButtonPress = () => {
    console.log('READING TEXT:', '[' + inputText + ']');
    navigation.navigate('DisplayScreen', { inputText })
  };

  return (
    <View style={styles.container}>

      <Text style={styles.header}>Visualise your expression!</Text>

      <TextInput
        style={styles.textBox}
        placeholder="Enter your expression here"
        onChangeText={handleInputChange}
        value={inputText}
      />

      <Button title="Parse"
        onPress={handleButtonPress}
        style = {styles.roundedButton}
      />
      
    </View>
  );
};

export default InputScreen;
