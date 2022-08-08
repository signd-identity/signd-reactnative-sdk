import {
  SigndResult,
  VerificationResult,
  ProgressBarStyle,
  SigndInterface,
} from '../';
import { mock } from 'jest-mock-extended';

test('SignD initialize function', async () => {
  const mockedSingdReactNativeSdk = mock<SigndInterface>();
  await mockedSingdReactNativeSdk.initialize({
    scheme: 'signd',
    host: 'session',
    apiUrl: 'https://api.dev.signd.io',
    progressBarStyle: ProgressBarStyle.Linear,
  });

  expect(mockedSingdReactNativeSdk.initialize).toBeCalledTimes(1);
});

test('SignD start function', async () => {
  const mockedSingdReactNativeSdk = mock<SigndInterface>();
  mockedSingdReactNativeSdk.start.mockReturnValue(
    Promise.resolve({
      result: VerificationResult.ProcessFinished,
      sessionToken: '123456789',
    })
  );
  const { result, sessionToken }: SigndResult = await mockedSingdReactNativeSdk.start(
    '123456789'
  );
  expect(mockedSingdReactNativeSdk.start).toBeCalledTimes(1);
  expect(result).toBe(VerificationResult.ProcessFinished);
  expect(sessionToken).toBe('123456789');
});
