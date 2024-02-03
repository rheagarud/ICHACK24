import React, {useEffect, useState} from 'react';
import { View, Text, Button } from 'react-native';
import { styles } from '../styles';
import { useNavigation } from '@react-navigation/native';
import { DisplayTree } from '../components/displayTree';
import { Icon } from 'react-native-elements';


const DisplayScreen = ({ route }) => {
  const navigation = useNavigation();
  const expression = route.params.inputText;

  // TODO: Uncomment when server online
  // const [data, setData] = useState(null);
  
  // useEffect(() => {
  //   fetch('https://your-backend-url.com/endpoint')
  //     .then(response => response.json())
  //     .then(fetchedData => setData(fetchedData))
  //     .catch(error => console.error('Error:', error));
  // }, []);

  // TODO: remove when server online
  const data = {"type": "sub", "left": {"type": "add", "left": {"type": "int", "value": 3}, "right": {"type": "int", "value": 5}}, "right": {"type": "int", "value": 4}}
  
  return (
    <View style={styles.container}>

      <Icon
        name='arrow-back'
        type='material'
        size={24}
        color='black'
        onPress={() => navigation.goBack()}
        containerStyle={styles.backButton}
      />

      <DisplayTree tree={data}/>
      
    </View>
  );
};

export default DisplayScreen;
