import React from 'react';
import { View, Text } from 'react-native';

// input tree type: dictionary
export const DisplayTree = ({ tree }) => {
    return (
        <View>
            {/* TODO: display tree */}
            <Text>{JSON.stringify(tree)}</Text>
        </View>
    );
};
