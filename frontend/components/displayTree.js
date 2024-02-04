import React from 'react';
import { View, Text } from 'react-native';

const typeToSymbol = (input) => {
    let map = new Map([["add", "+"], ["sub", "-"], ["mult", "x"], ["div", "÷"]]);
    return map.get(input);
};

// input tree type: dictionary
export const draw = (item)=>{
    if (item.type != "int" && item.type != "var"){
        return (
            <View>
                <Text>{typeToSymbol(item.type)}</Text>
                {item.left && draw(item.left)}
                {item.right && draw(item.right)}
            </View>
        );
    }
    else{
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
                <Text>Invalid input</Text>
            </View>
        );
    }
    // const json_obj = JSON.parse(expression);
    // console.log("Draw input type:", json_obj.type);
    //makeTree('{"type": "sub", "left": {"type": "add", "left": {"type": "int", "value": 3}, "right": {"type": "int", "value": 5}}, "right": {"type": "int","value":4}}');
    return (
        <View>
            <Text>Error: {expression["result"]}</Text>
            {/* {draw(json_obj)} */}
        </View>
    );
};
