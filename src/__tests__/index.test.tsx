import {
  SigndResult,
  VerificationResult,
  ProgressBarStyle,
  SigndInterface,
} from '../';
import { mock } from 'jest-mock-extended';

test('SignD initialize function', async () => {
  const mockedSigndReactnativeSdk = mock<SigndInterface>();
  await mockedSigndReactnativeSdk.initialize({
    scheme: 'signd',
    host: 'session',
    apiUrl: 'https://api.dev.signd.io',
    progressBarStyle: ProgressBarStyle.Linear,
  });

  expect(mockedSigndReactnativeSdk.initialize).toBeCalledTimes(1);
});

test('SignD start function', async () => {
  const mockedSigndReactnativeSdk = mock<SigndInterface>();
  mockedSigndReactnativeSdk.start.mockReturnValue(
    Promise.resolve({
      result: VerificationResult.ProcessFinished,
      sessionToken: '123456789',
    })
  );
  const { result, sessionToken }: SigndResult = await mockedSigndReactnativeSdk.start(
    '123456789'
  );
  expect(mockedSigndReactnativeSdk.start).toBeCalledTimes(1);
  expect(result).toBe(VerificationResult.ProcessFinished);
  expect(sessionToken).toBe('123456789');
});
