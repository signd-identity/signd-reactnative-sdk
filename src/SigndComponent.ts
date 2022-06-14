import { NativeModules } from 'react-native';
const { SigndModule } = NativeModules;
interface SigndInterface {
  initialize(name: string, location: string): void;
  start(name: string, location: string): void;
}
export default SigndModule as SigndInterface;
