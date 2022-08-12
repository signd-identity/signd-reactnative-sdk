import { NativeModules } from 'react-native';
import {
  ProgressBarStyle,
  SigndOptions,
  SigndResult,
  VerificationResult,
  ActionButtonStyle
} from './types';
const { SigndReactnativeSdk } = NativeModules;

export interface SigndInterface {
  initialize(config: SigndOptions): Promise<void>;
  start(sessionToken: string): Promise<SigndResult>;
}

export default SigndReactnativeSdk as SigndInterface;

export { VerificationResult, SigndResult, ProgressBarStyle, ActionButtonStyle };
