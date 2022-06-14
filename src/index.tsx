import { NativeModules } from 'react-native';
import {
  ProgressBarStyle,
  SigndOptions,
  SigndResult,
  VerificationResult,
} from './types';
const { SigndModule } = NativeModules;

export interface SigndInterface {
  initialize(config: SigndOptions): Promise<void>;
  start(sessionToken: string): Promise<SigndResult>;
}

export default SigndModule as SigndInterface;

export { VerificationResult, SigndResult, ProgressBarStyle };
