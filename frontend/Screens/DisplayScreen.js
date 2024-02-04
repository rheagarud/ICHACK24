import React, {useEffect, useState} from 'react';
import { View, Text, Button } from 'react-native';
import { styles } from '../styles';
import { useNavigation } from '@react-navigation/native';
import { DisplayTree } from '../components/displayTree';
import { Icon } from 'react-native-elements';


const DisplayScreen = ({ route }) => {
  const navigation = useNavigation();
  const expression = route.params.inputText;  
  const [data, setData] = useState("");
  
  useEffect(() => {
    console.log("SENDING:",expression);
    fetch('http://localhost:3000/run-command',{
      method: "POST",
      headers: {
        Accept: 'application/json',
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        hello: expression,
    }),
  })
      .then(response => {return response.json();})
      .then(fetchedData => {setData(fetchedData);})
      .then(console.log(data))
      .catch(error => console.error('Error:', error));
  }, []);

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

      <Text style={styles.header}>{expression}</Text>
      
      <DisplayTree expression={data} />

    </View>
  );
};

export default DisplayScreen;
