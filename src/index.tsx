import {
  requireNativeComponent,
  UIManager,
  Platform,
  ViewStyle,
} from 'react-native';

const LINKING_ERROR =
  `The package 'signd-reactnative-sdk' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo managed workflow\n';

type SigndReactnativeSdkProps = {
  color: string;
  style: ViewStyle;
};

const ComponentName = 'SigndReactnativeSdkView';

export const SigndReactnativeSdkView =
  UIManager.getViewManagerConfig(ComponentName) != null
    ? requireNativeComponent<SigndReactnativeSdkProps>(ComponentName)
    : () => {
        throw new Error(LINKING_ERROR);
      };
