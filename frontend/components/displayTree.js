import React from 'react';
import { View, Text } from 'react-native';
import { styles } from '../styles';

const typeToSymbol = (input) => {
    let map = new Map([["add", "+"], ["sub", "-"], ["mult", "x"], ["div", "÷"]]);
    return map.get(input);
};

// input tree type: dictionary
export const draw = (item)=>{
    console.log("Item:", item);
    if (item.type != "int" && item.type != "var"){
        console.log("type:", item.type);
        return (
            <View>
                <Text>{typeToSymbol(item.type)}</Text>
                <View style={{flexDirection: "row"}}>
                    <Text>{item.left && draw(item.left)}</Text>
                    <Text>{item.right && draw(item.right)}</Text>
                </View>
            </View>
        );
    }
    else{
        console.log("Value:", item.value);
        return (
            <View>
                <Text>{item.value}</Text>
            </View>
        );
    }
}

export const DisplayTree = ({ expression }) => {
    console.log("Expression:", expression)
    if (expression == null) {
        return (
            <View>
                <Text style={styles.errorText}>Waiting for Server</Text>
            </View>
        );
    }
    
    else if (expression["error"] != "none") {
        return (
            <View>
                <Text style={styles.errorText}>expression["error"]</Text>
            </View>
        );
    }

    json = JSON.parse(expression["result"]);
    //makeTree('{"type": "sub", "left": {"type": "add", "left": {"type": "int", "value": 3}, "right": {"type": "int", "value": 5}}, "right": {"type": "int","value":4}}');
    return (
        <View>
            {/* <Text>Error: {expression["result"]}</Text> */}
            {draw(json)}
        </View>
    );
};
