import { StyleSheet } from 'react-native';

export const styles = StyleSheet.create({
    container: {
        flex: 1,
        justifyContent: 'center',
        alignItems: 'center',
        padding: 16,
    },
    header: {
        fontSize: 24,
        fontWeight: 'bold',
        marginBottom: 16,
    },
    textBox: {
        height: 40,
        borderColor: 'gray',
        borderWidth: 1,
        paddingLeft: 15,
        marginBottom: 16,
        width: '100%',
        borderRadius: 8,
        justifyContent: 'center',
        textAlign: 'left',
    },
    roundedButton: {
        backgroundColor: 'black',
        borderRadius: 100,
    },
    backButton: {
        position: 'absolute',
        top: 40,
        left: 10,
    },
    errorText: {
        color: 'red',
        marginBottom: 16,
    },
});