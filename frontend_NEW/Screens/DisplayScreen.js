import React, {useEffect, useState} from 'react';
import { View, Text, Button } from 'react-native';
import { styles } from '../styles';
import { useNavigation } from '@react-navigation/native';

const DisplayScreen = ({ route }) => {
  const navigation = useNavigation();
  const expression = route.params.inputText;
  const [data, setData] = useState(null);

  useEffect(() => {
    fetch('https://your-backend-url.com/endpoint')
      .then(response => response.json())
      .then(fetchedData => setData(fetchedData))
      .catch(error => console.error('Error:', error));
  }, []);
  
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
