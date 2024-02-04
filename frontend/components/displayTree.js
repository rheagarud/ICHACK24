import React from 'react';
import { View, Text } from 'react-native';
import { styles } from '../styles';
import TreeComponent from './nodeDisplay';

export const draw = (item)=> {
   return (
     <TreeComponent node={item} />
   );

}

// input tree type: dictionary
// export const draw = (item)=>{
//     console.log("Item:", item);
//     if (item.type != "int" && item.type != "var"){
//         console.log("type:", item.type);
//         return (
//             <View>
//                 <Text>{typeToSymbol(item.type)}</Text>
//                 <View style={{flexDirection: "row"}}>
//                     <Text>{item.left && draw(item.left)}</Text>
//                     <Text>{item.right && draw(item.right)}</Text>
//                 </View>
//             </View>
//         );
//     }
//     else{
//         console.log("Value:", item.value);
//         return (
//             <View>
//                 <Text>{item.value}</Text>
//             </View>
//         );
//     }
// }

export const DisplayTree = ({ expression }) => {
    console.log("Expression:", expression)
    if (expression == null) {
        return (
            <View>
                <Text style={styles.errorText}>Waiting for Server...</Text>
            </View>
        );
    }
    else if (expression["error"] != "none") {
        console.log("error from expressions: " + expression["error"]);
        return (
            <View>
                <Text style={styles.errorText}>{expression["error"]}</Text>
            </View>
        );
    }
    // console.log("error from expression: " + expression["error"]);
    json = JSON.parse(expression["result"]);
    console.log("JSON:", json)
    //makeTree('{"type": "sub", "left": {"type": "add", "left": {"type": "int", "value": 3}, "right": {"type": "int", "value": 5}}, "right": {"type": "int","value":4}}');
    return (
        <View>
            {/* <Text>Error: {expression["result"]}</Text> */}
            {
                draw(json)
            // draw (JSON.parse('{"type": "sub", "left": {"type": "add", "left": {"type": "int", "value": 3}, "right": {"type": "int", "value": 5}}, "right": {"type": "int","value":4}}'))
            }
        </View>
    );
};
