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
        paddingLeft: 8,
        marginBottom: 16,
        width: '100%',
        borderRadius: 8,
        letterSpacing: 4,
        justifyContent: 'center',
        alignItems: 'center',
        textAlign: 'center',
    },
    roundedButton: {
        backgroundColor: 'black',
        borderRadius: 100,
    },
});