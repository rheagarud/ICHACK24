import React from 'react';
import { View, Text } from 'react-native';
import { styles } from '../styles';

const typeToSymbol = (input) => {
    let map = new Map([["add", "+"], ["sub", "-"], ["mult", "x"], ["div", "÷"]]);
    return map.get(input);
};

// input tree type: dictionary
export const draw = (item)=>{
    if (item.type != "int" && item.type != "var"){
        return (
            <View>
                <View style = {styles.node}>
                    <Text style = {styles.val}>{typeToSymbol(item.type)}</Text>
                </View>
                {item.left && draw(item.left)}
                {item.right && draw(item.right)}
            </View>
        );
    }
    else{
        return (
            <View style = {styles.node}>
                <Text style = {styles.val}>{item.value}</Text>
            </View>
        );
    }
}
export const DisplayTree = ({ expression }) => {
    const json_obj = JSON.parse(expression);
    console.log(json_obj.type);
    //makeTree('{"type": "sub", "left": {"type": "add", "left": {"type": "int", "value": 3}, "right": {"type": "int", "value": 5}}, "right": {"type": "int","value":4}}');
    return (
        <View>
            {draw(json_obj)}
        </View>
    );
};
