import React from 'react';
import { View, Text } from 'react-native';
import Svg, { Circle, Line, G, Text as SvgText } from 'react-native-svg';
import { useState, useEffect } from 'react';

// let [currentNode, setCurrentNode] = useState(0);

// Converts type to it's symbol representation
const typeToSymbol = (input) => {
  let map = new Map([["add", "+"], ["sub", "-"], ["mult", "x"], ["div", "÷"], ["power", "^"], ["equals","=",],["<","<"],[">",">"],["<=","≤"],[">=","≥"], ["mod","%"]]);
  return map.get(input);
};

// // increments global current nodeID
// const handleNextNode = () => {
//   setCurrentNode(currentNode + 1);
// }

// // decrements global current nodeID
// const handlePrevNode = () => {
//   setCurrentNode(currentNode - 1);
// }
  
// Displays the tree
const TreeComponent = ({node, currentNodeID}) => {
  if (!node) {
    return null;
  }
  console.log("rendering tree " + node)
  // Recursive function to render the tree nodes
  const renderNode = (currentNode, x, y, wid, nodeID) => {
    const [color, setColor] = useState('red');
    if (!currentNode) {
      return null;
    }

    // Hide symbols which haven't been shown
    const getColour = () => {
      // Determine the color based on the nodeID
      // This is just a placeholder; replace it with your actual logic
      console.log("nodeID: " + nodeID + "currentNodeID: " + currentNodeID)
      return nodeID < currentNodeID ? 'green' : 'white';
    };

    useEffect(() => {
      console.log("currentNodeID: " + currentNodeID);
      setColor(getColour());
    }, [currentNode]);

    const radius = 15;
    console.log("drawing" + currentNode.type, + " " + x + " " + y)

    return (
      <G>
        <Circle cx={x} cy={y} r={radius} fill={color} />
        <SvgText x={x} y={y+5} fontSize="15" fontWeight={ 'bold' } textAnchor="middle" fill="white">
          {currentNode.type === 'int' ? currentNode.value : typeToSymbol(currentNode.type)}
        </SvgText>

        {currentNode.left && (
          <>
            <Line x1={x} y1={y + radius} x2={x - wid} y2={y + 100} stroke="black" />
            {renderNode(currentNode.left, x - wid, y + 100, wid / 2, nodeID+1)}
          </>
        )}

        {currentNode.right && (
          <>
            <Line x1={x} y1={y + radius} x2={x + wid} y2={y + 100} stroke="black" />
            {renderNode(currentNode.right, x + wid, y + 100, wid / 2, nodeID+1)}
          </>
        )}
      </G>
    );
  };

  return (
    <Svg height="500" width="500">
      {renderNode(node, 250, 50, 80, 0)}
    </Svg>
  );
};

export default TreeComponent;
