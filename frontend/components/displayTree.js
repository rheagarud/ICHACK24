import React from 'react';
import { View, Text, TouchableOpacity } from 'react-native';
import { styles } from '../styles';
import TreeComponent from './nodeDisplay';
import { useState } from 'react';

export const draw = (item, currentNode)=> {
    console.log("currentNode IN DRAW:", currentNode);
    return (
        <TreeComponent node={item} currentNodeID= {currentNode} />
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

    let [currentNode, setCurrentNode] = useState(1);
    // increments global current nodeID
    const handleNextNode = () => {
        setCurrentNode(currentNode + 1);
    }
    
    // decrements global current nodeID
    const handlePrevNode = () => {
        setCurrentNode(currentNode - 1);
    }

    // skip to end
    const handleSkip = () => {
        setCurrentNode(4);
    }

    // console.log("error from expression: " + expression["error"]);
    json = JSON.parse(expression["result"]);
    console.log("JSON:", json)
    //makeTree('{"type": "sub", "left": {"type": "add", "left": {"type": "int", "value": 3}, "right": {"type": "int", "value": 5}}, "right": {"type": "int","value":4}}');
    return (
        <View>
            
            {/* <Text>Error: {expression["result"]}</Text> */}
            {
                draw(json, currentNode)
            // draw (JSON.parse('{"type": "sub", "left": {"type": "add", "left": {"type": "int", "value": 3}, "right": {"type": "int", "value": 5}}, "right": {"type": "int","value":4}}'))
            }
            <View style = {{flexDirection: "column", alignItems: "center", justifyContent: "space-between"}}>
                <View style={{ flexDirection: 'row', justifyContent: 'space-between' }}>
                    <TouchableOpacity
                        style={styles.roundedButton}
                        onPress={handlePrevNode}
                    >
                        <Text style={styles.buttonText}>Prev</Text>
                    </TouchableOpacity>
                    <TouchableOpacity
                        style={styles.roundedButton}
                        onPress={handleNextNode}
                    >
                        <Text style={styles.buttonText}>Next</Text>
                    </TouchableOpacity>
                    
                </View>
                <View style = {{width:200, alignItems: "center"}}>
                <TouchableOpacity
                    style={styles.roundedButton}
                    onPress={handleSkip}
                >
                        <Text style={styles.buttonText}>Skip to end</Text>
                    </TouchableOpacity>
                </View>
            </View>
        </View>
        
    );
};
