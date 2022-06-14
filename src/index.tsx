import { NativeModules } from 'react-native';
import { SigndOptions, SigndResult, VerificationResult } from './types';
const { SigndModule } = NativeModules;

interface SigndInterface {
  initialize(config: SigndOptions): Promise<void>;
  start(sessionToken: string): Promise<SigndResult>;
}

export default SigndModule as SigndInterface;

export { VerificationResult, SigndResult };
