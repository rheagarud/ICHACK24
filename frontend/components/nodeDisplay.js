import React from 'react';
import { View, Text } from 'react-native';
import Svg, { Circle, Line, G, Text as SvgText } from 'react-native-svg';

const typeToSymbol = (input) => {
  let map = new Map([["add", "+"], ["sub", "-"], ["mult", "x"], ["div", "÷"], ["power", "^"], ["equals","=",],["<","<"],[">",">"],["<=","<="],[">=",">="]]);
  return map.get(input);
};

const TreeComponent = ({ node }) => {
  if (!node) {
    return null;
  }
  console.log("rendering tree " + node)
  const renderNode = (currentNode, x, y, wid) => {
    if (!currentNode) {
      return null;
    }

    const radius = 15;
    console.log("drawing" + currentNode.type, + " " + x + " " + y)

    return (
      <G>
        <Circle cx={x} cy={y} r={radius} fill="green" />
        <SvgText x={x} y={y+5} fontSize="15" textAnchor="middle" fill="white">
          {currentNode.type === 'int' ? currentNode.value : typeToSymbol(currentNode.type)}
        </SvgText>

        {currentNode.left && (
          <>
            <Line x1={x} y1={y + radius} x2={x - wid} y2={y + 100} stroke="black" />
            {renderNode(currentNode.left, x - wid, y + 100, wid / 2)}
          </>
        )}

        {currentNode.right && (
          <>
            <Line x1={x} y1={y + radius} x2={x + wid} y2={y + 100} stroke="black" />
            {renderNode(currentNode.right, x + wid, y + 100, wid / 2)}
          </>
        )}
      </G>
    );
  };

  return (
    <Svg height="500" width="500">
      {renderNode(node, 250, 50, 80)}
    </Svg>
  );
};

export default TreeComponent;
