import React from 'react';
import { View, Text } from 'react-native';
import Svg, { Circle, Line, G, Text as SvgText } from 'react-native-svg';

const TreeComponent = ({ node }) => {
  if (!node) {
    return null;
  }
  console.log("rendering tree " + node)
  const renderNode = (currentNode, x, y) => {
    if (!currentNode) {
      return null;
    }

    const radius = 30;
    console.log("drawing" + currentNode.type, + " " + x + " " + y)

    return (
      <G>
        <Circle cx={x} cy={y} r={radius} fill="blue" />
        <SvgText x={x} y={y} fontSize="12" textAnchor="middle" fill="white">
          {currentNode.type === 'int' ? currentNode.value : currentNode.type}
        </SvgText>

        {currentNode.left && (
          <>
            <Line x1={x} y1={y + radius} x2={x - 50} y2={y + 100} stroke="black" />
            {renderNode(currentNode.left, x - 50, y + 100)}
          </>
        )}

        {currentNode.right && (
          <>
            <Line x1={x} y1={y + radius} x2={x + 50} y2={y + 100} stroke="black" />
            {renderNode(currentNode.right, x + 50, y + 100)}
          </>
        )}
      </G>
    );
  };

  return (
    <Svg height="500" width="500">
      {renderNode(node, 250, 50)}
    </Svg>
  );
};

export default TreeComponent;
