import assert from 'node:assert/strict';
import test from 'node:test';
import {
  advanceMotion,
  createMotionState,
  renderedLine,
  resetMotion,
  setTargetLine,
  spriteForState
} from '../animation';

test('moves toward the target at the configured lines per second', () => {
  const initial = setTargetLine(createMotionState(0), 8, 20);
  const moved = advanceMotion(initial, 500, 8, 20);

  assert.equal(moved.currentLine, 4);
  assert.equal(moved.targetLine, 8);
  assert.equal(moved.direction, 'down');
  assert.equal(renderedLine(moved, 20), 4);
});

test('snaps to the target and sits when the remaining distance fits in the frame', () => {
  const initial = setTargetLine(createMotionState(0), 8, 20);
  const moved = advanceMotion(initial, 1000, 8, 20);

  assert.equal(moved.currentLine, 8);
  assert.equal(moved.direction, 'idle');
  assert.equal(spriteForState(moved), 'sit');
});

test('retargets immediately from the current floating position', () => {
  const firstTarget = setTargetLine(createMotionState(0), 8, 20);
  const halfway = advanceMotion(firstTarget, 500, 8, 20);
  const retargeted = setTargetLine(halfway, 2, 20);
  const moved = advanceMotion(retargeted, 125, 8, 20);

  assert.equal(retargeted.currentLine, 4);
  assert.equal(retargeted.targetLine, 2);
  assert.equal(moved.currentLine, 3);
  assert.equal(moved.direction, 'up');
});

test('clamps target and rendered lines to document bounds', () => {
  const tooLow = setTargetLine(createMotionState(0), -4, 5);
  const tooHigh = setTargetLine(createMotionState(0), 40, 5);
  const currentTooHigh = resetMotion(20, 5);

  assert.equal(tooLow.targetLine, 0);
  assert.equal(tooHigh.targetLine, 4);
  assert.equal(renderedLine(currentTooHigh, 5), 4);
});

test('reset places the cat at the new active editor cursor line', () => {
  const state = resetMotion(12, 30);

  assert.equal(state.currentLine, 12);
  assert.equal(state.targetLine, 12);
  assert.equal(state.direction, 'idle');
});

test('selects vertical running sprites based on direction and frame index', () => {
  const down = advanceMotion(setTargetLine(createMotionState(0), 10, 20), 200, 8, 20);
  const up = advanceMotion(setTargetLine(createMotionState(10), 0, 20), 200, 8, 20);

  assert.equal(spriteForState(down), 'run-down-2');
  assert.equal(spriteForState(up), 'run-up-2');
});
