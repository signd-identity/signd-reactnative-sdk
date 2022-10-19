import React from 'react';
import { useEffect, useState } from 'react';
import {
  Alert,
  Button,
  Linking,
  StyleSheet,
  TextInput,
  View,
} from 'react-native';
import SigndModule, {
  SigndResult,
  VerificationResult,
  ProgressBarStyle
} from 'signd-reactnative-sdk';


const Home: React.FC = () => {
  const [sessionTokenText, onSessionTokenTextChange] = useState('');

  async function launchSigndSdk(token: string) {
    // Change values according to your configuration
    await SigndModule.initialize({
                scheme: 'admiralpay',
                host: 'hostsigndintegration://test',
                apiUrl: 'https://api.integration.signd.io'
              });
    const { result, sessionToken }: SigndResult = await SigndModule.start(
      token
    );

    switch (result) {
      case VerificationResult.ProcessCancelled: {
        break;
      }
      case VerificationResult.ProcessFailed: {
        break;
      }
      case VerificationResult.ProcessInProgress: {
        break;
      }
      case VerificationResult.ProcessFinished: {
        break;
      }
    }

    console.log('Verification process finished; sessionToken: ' + sessionToken);
    console.log('Result: ' + result);
    Alert.alert('SignD SDK', 'Verification process finished: ' + result);
  }

  const startSignd = async () => {
    // @ts-ignore
    if (sessionTokenText.length === 0) {
      Alert.alert('SignD SDK', 'Session token must not be empty');
      return;
    }

    await launchSigndSdk(sessionTokenText);
  };

  useEffect(() => {
    const extractLaunchUrl = async () => {
      Linking.addEventListener('url', (data: any) => {
        console.log('extractLaunchUrl - url ' + data.url);
        // Example url: signd://session?sessionToken=xyz
        const deepLink: boolean = data.url.startsWith(
          'signdintegration://session?sessionToken'
        );
        const sessionToken = data.url.split('sessionToken=').pop();
        if (deepLink && sessionToken) {
          launchSigndSdk(sessionToken);
        }
      });

      const url = (await Linking.getInitialURL()) ?? undefined;
      const sessionToken = url?.split('sessionToken=').pop();

      if (sessionToken) {
        Alert.alert(
          'SignD SDK',
          'extractLaunchUrl - App opened with URL: ' + url
        );
        launchSigndSdk(sessionToken);
      }
    };

    extractLaunchUrl();
  }, []);

  return (
    <View>
      <TextInput
        style={styles.input}
        onChangeText={onSessionTokenTextChange}
        value={sessionTokenText}
      />
      <Button onPress={() => startSignd()} title="Launch SignD" />
    </View>
  );
};

const styles = StyleSheet.create({
  input: {
    height: 40,
    width: 200,
    margin: 12,
    borderWidth: 1,
    padding: 10,
  },
});

export default Home;
