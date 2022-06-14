import {
  SigndResult,
  VerificationResult,
  ProgressBarStyle,
  SigndInterface,
} from '../';
import { mock } from 'jest-mock-extended';

test('SignD initialize function', async () => {
  const mockedSigndModule = mock<SigndInterface>();
  await mockedSigndModule.initialize({
    scheme: 'signd',
    host: 'session',
    apiUrl: 'https://api.dev.signd.io',
    progressBarStyle: ProgressBarStyle.Linear,
  });

  expect(mockedSigndModule.initialize).toBeCalledTimes(1);
});

test('SignD start function', async () => {
  const mockedSigndModule = mock<SigndInterface>();
  mockedSigndModule.start.mockReturnValue(
    Promise.resolve({
      result: VerificationResult.ProcessFinished,
      sessionToken: '123456789',
    })
  );
  const { result, sessionToken }: SigndResult = await mockedSigndModule.start(
    '123456789'
  );
  expect(mockedSigndModule.start).toBeCalledTimes(1);
  expect(result).toBe(VerificationResult.ProcessFinished);
  expect(sessionToken).toBe('123456789');
});
