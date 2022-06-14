import * as React from 'react';

import { StyleSheet, View } from 'react-native';
import SigndProvider from 'signd-reactnative-sdk';

export default function App() {
  return (
    <View style={styles.container}>
      <SigndProvider />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
