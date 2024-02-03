import React, {useEffect, useState} from 'react';
import { View, Text, Button } from 'react-native';

const DisplayScreen = ({ navigation }) => {
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
