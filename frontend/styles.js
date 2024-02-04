import { StyleSheet } from 'react-native';

export const styles = StyleSheet.create({
    container: {
        flex: 1,
        justifyContent: 'center',
        alignItems: 'center',
        padding: 16,
        backgroundColor: 'white',
    },
    header: {
        fontSize: 24,
        fontWeight: 'bold',
        marginBottom: 40,
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
        backgroundColor: 'darkgreen',
        borderRadius: 30,
        paddingVertical: 3,
        paddingHorizontal: 22,
    },
    buttonText: {
        color: 'white',
        fontSize: 16,
        padding: 10
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