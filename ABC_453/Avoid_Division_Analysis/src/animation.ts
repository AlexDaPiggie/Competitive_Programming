export type CatDirection = 'idle' | 'up' | 'down';

export type SpriteKind =
  | 'sit'
  | 'run-up-1'
  | 'run-up-2'
  | 'run-down-1'
  | 'run-down-2';

export type EnablementAction = 'enable' | 'disable' | 'toggle';

export interface CatMotionState {
  readonly currentLine: number;
  readonly targetLine: number;
  readonly direction: CatDirection;
  readonly frameIndex: 0 | 1;
  readonly frameElapsedMs: number;
}

const frameDurationMs = 180;
const epsilon = 0.0001;

export function createMotionState(line: number): CatMotionState {
  return {
    currentLine: line,
    targetLine: line,
    direction: 'idle',
    frameIndex: 0,
    frameElapsedMs: 0
  };
}

export function resetMotion(line: number, lineCount: number): CatMotionState {
  return createMotionState(clampLine(line, lineCount));
}

export function setTargetLine(
  state: CatMotionState,
  targetLine: number,
  lineCount: number
): CatMotionState {
  return {
    ...state,
    targetLine: clampLine(targetLine, lineCount)
  };
}

export function advanceMotion(
  state: CatMotionState,
  elapsedMs: number,
  speedLinesPerSecond: number,
  lineCount: number
): CatMotionState {
  const currentLine = clampLine(state.currentLine, lineCount);
  const targetLine = clampLine(state.targetLine, lineCount);
  const remaining = targetLine - currentLine;

  if (
    Math.abs(remaining) <= epsilon ||
    !Number.isFinite(elapsedMs) ||
    elapsedMs <= 0 ||
    !Number.isFinite(speedLinesPerSecond) ||
    speedLinesPerSecond <= 0
  ) {
    return {
      currentLine,
      targetLine,
      direction: 'idle',
      frameIndex: 0,
      frameElapsedMs: 0
    };
  }

  const direction: CatDirection = remaining < 0 ? 'up' : 'down';
  const maxStep = speedLinesPerSecond * (elapsedMs / 1000);

  if (Math.abs(remaining) <= maxStep + epsilon) {
    return {
      currentLine: targetLine,
      targetLine,
      direction: 'idle',
      frameIndex: 0,
      frameElapsedMs: 0
    };
  }

  const nextLine = currentLine + Math.sign(remaining) * maxStep;
  const frame = advanceFrame(state.frameIndex, state.frameElapsedMs + elapsedMs);

  return {
    currentLine: nextLine,
    targetLine,
    direction,
    frameIndex: frame.frameIndex,
    frameElapsedMs: frame.frameElapsedMs
  };
}

export function renderedLine(state: CatMotionState, lineCount: number): number {
  return clampLine(Math.round(state.currentLine), lineCount);
}

export function spriteForState(state: CatMotionState): SpriteKind {
  if (state.direction === 'up') {
    return state.frameIndex === 0 ? 'run-up-1' : 'run-up-2';
  }

  if (state.direction === 'down') {
    return state.frameIndex === 0 ? 'run-down-1' : 'run-down-2';
  }

  return 'sit';
}

export function clampLine(line: number, lineCount: number): number {
  if (!Number.isFinite(lineCount) || lineCount <= 0) {
    return 0;
  }

  const normalizedLine = Number.isFinite(line) ? line : 0;

  return Math.min(Math.max(normalizedLine, 0), lineCount - 1);
}

export function nextEnabledState(current: boolean, action: EnablementAction): boolean {
  if (action === 'enable') {
    return true;
  }

  if (action === 'disable') {
    return false;
  }

  return !current;
}

function advanceFrame(
  frameIndex: 0 | 1,
  frameElapsedMs: number
): { frameIndex: 0 | 1; frameElapsedMs: number } {
  if (!Number.isFinite(frameElapsedMs) || frameElapsedMs < 0) {
    return {
      frameIndex,
      frameElapsedMs: 0
    };
  }

  const advancedFrames = Math.floor(frameElapsedMs / frameDurationMs);
  const nextFrameIndex = advancedFrames % 2 === 0 ? frameIndex : toggleFrame(frameIndex);
  const nextFrameElapsedMs = frameElapsedMs % frameDurationMs;

  return {
    frameIndex: nextFrameIndex,
    frameElapsedMs: nextFrameElapsedMs
  };
}

function toggleFrame(frameIndex: 0 | 1): 0 | 1 {
  return frameIndex === 0 ? 1 : 0;
}
