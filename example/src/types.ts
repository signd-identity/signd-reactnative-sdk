export enum VerificationResult {
  ProcessCancelled = 'ProcessCanceled',
  ProcessFailed = 'ProcessFailed',
  ProcessFinished = 'ProcessFinished',
  ProcessInProgress = 'ProcessInProgress',
}

export enum ProgressBarStyle {
  Default = 'Default',
  Linear = 'Linear',
}

export enum ActionButtonStyle {
  Rounded = 'Rounded',
  Round = 'Round',
}

export interface SigndOptions {
  scheme: string;
  host: string;
  apiUrl: string;
  showLastScreen?: boolean;
  showFirstScreen?: boolean;
  showBackButton?: boolean;
  showCloseButton?: boolean;
  showFooter?: boolean;
  progressBarStyle?: ProgressBarStyle;
  actionButtonStyle?: ActionButtonStyle; // iOS only
  regularFontFileName?: string; // iOS only
  boldFontFileName?: string; // iOS only
  scanExampleAnimationFileName?: string; // iOS only
  doneAnimationFileName?: string; // iOS only
  primaryColor?: string; // iOS only
  secondaryColor?: string; // iOS only
  textPrimary?: string; // iOS only
  textSecondary?: string; // iOS only
  textHint?: string; // iOS only
  primaryBackgroundColor?: string; // iOS only
  secondaryBackgroundColor?: string; // iOS only
}

export interface SigndResult {
  result: string;
  sessionToken: string;
}
