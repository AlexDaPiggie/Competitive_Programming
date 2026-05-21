# Oneko Cat VS Code Extension Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a TypeScript VS Code extension that shows an oneko-inspired cat in the active editor gutter and animates it vertically toward the primary cursor line.

**Architecture:** Keep the time-based movement model in a VS Code-free module with Node unit tests. Put editor activation, commands, settings, sprite decoration creation, and gutter rendering in the extension controller. Bundle original SVG sprites under `assets/` and reference them through extension URIs.

**Tech Stack:** Visual Studio Code Extension API, TypeScript, Node built-in test runner, bundled SVG assets.

---

## File Structure

- Create `package.json`: extension manifest, commands, configuration, scripts, and dev dependencies.
- Create `tsconfig.json`: TypeScript compiler configuration.
- Create `.vscodeignore`: package exclusion rules.
- Create `.vscode/launch.json`: Extension Development Host launch config.
- Create `.vscode/tasks.json`: compile task used by launch config.
- Create `src/animation.ts`: pure movement, retargeting, clamping, and sprite selection logic.
- Create `src/extension.ts`: VS Code activation, controller lifecycle, settings, commands, and gutter decorations.
- Create `src/test/animation.test.ts`: Node unit tests for movement behavior.
- Create `assets/cat-sit.svg`: original sitting sprite.
- Create `assets/cat-run-up-1.svg`: original upward running frame 1.
- Create `assets/cat-run-up-2.svg`: original upward running frame 2.
- Create `assets/cat-run-down-1.svg`: original downward running frame 1.
- Create `assets/cat-run-down-2.svg`: original downward running frame 2.

---

### Task 1: Scaffold The Extension Project

**Files:**
- Create: `package.json`
- Create: `tsconfig.json`
- Create: `.vscodeignore`
- Create: `.vscode/launch.json`
- Create: `.vscode/tasks.json`

- [ ] **Step 1: Create `package.json`**

Create `package.json` with this content:

```json
{
  "name": "oneko-cat-gutter",
  "displayName": "Oneko Cat Gutter",
  "description": "Shows an oneko-inspired cat in the active editor gutter and lets it follow the cursor line.",
  "version": "0.0.1",
  "publisher": "local",
  "engines": {
    "vscode": "^1.90.0"
  },
  "categories": [
    "Other"
  ],
  "activationEvents": [
    "onStartupFinished",
    "onCommand:onekoCat.enable",
    "onCommand:onekoCat.disable",
    "onCommand:onekoCat.toggle"
  ],
  "main": "./out/extension.js",
  "contributes": {
    "commands": [
      {
        "command": "onekoCat.enable",
        "title": "Oneko Cat: Enable"
      },
      {
        "command": "onekoCat.disable",
        "title": "Oneko Cat: Disable"
      },
      {
        "command": "onekoCat.toggle",
        "title": "Oneko Cat: Toggle"
      }
    ],
    "configuration": {
      "title": "Oneko Cat",
      "properties": {
        "onekoCat.enabled": {
          "type": "boolean",
          "default": true,
          "description": "Enable the oneko-inspired gutter cat."
        },
        "onekoCat.speedLinesPerSecond": {
          "type": "number",
          "default": 8,
          "minimum": 1,
          "description": "How many editor lines per second the cat moves while following the cursor."
        },
        "onekoCat.catScale": {
          "type": "number",
          "default": 1,
          "minimum": 0.5,
          "maximum": 2,
          "description": "Scale factor for the cat gutter icon."
        }
      }
    }
  },
  "scripts": {
    "compile": "tsc -p ./",
    "watch": "tsc -watch -p ./",
    "test": "npm run compile && node --test out/test/*.test.js",
    "vscode:prepublish": "npm run compile"
  },
  "devDependencies": {
    "@types/node": "^20.14.8",
    "@types/vscode": "^1.90.0",
    "typescript": "^5.5.2"
  }
}
```

- [ ] **Step 2: Create `tsconfig.json`**

Create `tsconfig.json` with this content:

```json
{
  "compilerOptions": {
    "module": "commonjs",
    "target": "ES2022",
    "lib": [
      "ES2022"
    ],
    "outDir": "out",
    "rootDir": "src",
    "strict": true,
    "sourceMap": true,
    "esModuleInterop": true,
    "skipLibCheck": true
  },
  "include": [
    "src"
  ]
}
```

- [ ] **Step 3: Create `.vscodeignore`**

Create `.vscodeignore` with this content:

```text
.vscode/**
src/**
docs/**
node_modules/**
*.map
tsconfig.json
```

- [ ] **Step 4: Create `.vscode/launch.json`**

Create `.vscode/launch.json` with this content:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Run Extension",
      "type": "extensionHost",
      "request": "launch",
      "args": [
        "--extensionDevelopmentPath=${workspaceFolder}"
      ],
      "outFiles": [
        "${workspaceFolder}/out/**/*.js"
      ],
      "preLaunchTask": "npm: compile"
    }
  ]
}
```

- [ ] **Step 5: Create `.vscode/tasks.json`**

Create `.vscode/tasks.json` with this content:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "type": "npm",
      "script": "compile",
      "group": "build",
      "problemMatcher": "$tsc",
      "label": "npm: compile"
    }
  ]
}
```

- [ ] **Step 6: Install dependencies**

Run:

```powershell
npm install
```

Expected: `node_modules/` and `package-lock.json` are created without dependency resolution errors.

- [ ] **Step 7: Compile the empty project and verify the expected failure**

Run:

```powershell
npm run compile
```

Expected: FAIL because `src/extension.ts` does not exist yet. A TypeScript message similar to `No inputs were found in config file` is acceptable at this point.

- [ ] **Step 8: Commit scaffold files**

Run:

```powershell
git add package.json package-lock.json tsconfig.json .vscodeignore .vscode/launch.json .vscode/tasks.json
git commit -m "chore: scaffold oneko cat extension"
```

Expected: commit succeeds with only scaffold files staged.

---

### Task 2: Add Tested Animation Logic

**Files:**
- Create: `src/animation.ts`
- Create: `src/test/animation.test.ts`

- [ ] **Step 1: Write the failing animation tests**

Create `src/test/animation.test.ts` with this content:

```ts
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
```

- [ ] **Step 2: Run tests and verify failure**

Run:

```powershell
npm test
```

Expected: FAIL because `src/animation.ts` does not exist and TypeScript cannot resolve `../animation`.

- [ ] **Step 3: Implement `src/animation.ts`**

Create `src/animation.ts` with this content:

```ts
export type CatDirection = 'idle' | 'up' | 'down';

export type SpriteKind =
  | 'sit'
  | 'run-up-1'
  | 'run-up-2'
  | 'run-down-1'
  | 'run-down-2';

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

  if (Math.abs(remaining) <= epsilon || elapsedMs <= 0 || speedLinesPerSecond <= 0) {
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
  if (lineCount <= 0) {
    return 0;
  }

  return Math.min(Math.max(line, 0), lineCount - 1);
}

function advanceFrame(
  frameIndex: 0 | 1,
  frameElapsedMs: number
): { frameIndex: 0 | 1; frameElapsedMs: number } {
  let nextFrameIndex = frameIndex;
  let nextFrameElapsedMs = frameElapsedMs;

  while (nextFrameElapsedMs >= frameDurationMs) {
    nextFrameIndex = nextFrameIndex === 0 ? 1 : 0;
    nextFrameElapsedMs -= frameDurationMs;
  }

  return {
    frameIndex: nextFrameIndex,
    frameElapsedMs: nextFrameElapsedMs
  };
}
```

- [ ] **Step 4: Run tests and verify pass**

Run:

```powershell
npm test
```

Expected: PASS for all six animation tests.

- [ ] **Step 5: Commit animation logic**

Run:

```powershell
git add src/animation.ts src/test/animation.test.ts
git commit -m "feat: add cat motion model"
```

Expected: commit succeeds with animation source and tests.

---

### Task 3: Add Original SVG Cat Sprites

**Files:**
- Create: `assets/cat-sit.svg`
- Create: `assets/cat-run-up-1.svg`
- Create: `assets/cat-run-up-2.svg`
- Create: `assets/cat-run-down-1.svg`
- Create: `assets/cat-run-down-2.svg`

- [ ] **Step 1: Create sitting sprite**

Create `assets/cat-sit.svg` with this content:

```xml
<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 16 16" shape-rendering="crispEdges">
  <path fill="#ffffff" d="M5 3h1V2h1v2h2V2h1v1h1v2h1v5h-1v2h-1v1H6v-1H5v-2H4V5h1z"/>
  <path fill="#111111" d="M6 2h1v2H6zm3 0h1v2H9zM5 4h6v1H5zm-1 1h1v5H4zm7 0h1v5h-1zM6 7h1v1H6zm3 0h1v1H9zM7 9h2v1H7zm-2 1h1v2H5zm5 0h1v2h-1zm-4 2h4v1H6zM3 12h2v1H3zm8 0h2v1h-2z"/>
</svg>
```

- [ ] **Step 2: Create upward running frame 1**

Create `assets/cat-run-up-1.svg` with this content:

```xml
<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 16 16" shape-rendering="crispEdges">
  <path fill="#ffffff" d="M5 2h1V1h1v2h2V1h1v1h1v2h1v6h-1v2H9v1H6v-1H4v-2H3V4h2z"/>
  <path fill="#111111" d="M6 1h1v2H6zm3 0h1v2H9zM5 3h6v1H5zM3 4h1v6H3zm8 0h1v6h-1zM6 6h1v1H6zm3 0h1v1H9zM7 8h2v1H7zm-3 2h2v2H4zm6 0h2v2h-2zm-5 3h2v1H5zm4-1h2v1H9z"/>
</svg>
```

- [ ] **Step 3: Create upward running frame 2**

Create `assets/cat-run-up-2.svg` with this content:

```xml
<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 16 16" shape-rendering="crispEdges">
  <path fill="#ffffff" d="M5 2h1V1h1v2h2V1h1v1h1v2h1v6h-1v2H9v1H6v-1H4v-2H3V4h2z"/>
  <path fill="#111111" d="M6 1h1v2H6zm3 0h1v2H9zM5 3h6v1H5zM3 4h1v6H3zm8 0h1v6h-1zM6 6h1v1H6zm3 0h1v1H9zM7 8h2v1H7zm-2 2h2v2H5zm5 0h2v2h-2zM3 12h2v1H3zm9 1h2v1h-2z"/>
</svg>
```

- [ ] **Step 4: Create downward running frame 1**

Create `assets/cat-run-down-1.svg` with this content:

```xml
<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 16 16" shape-rendering="crispEdges">
  <path fill="#ffffff" d="M5 4h1V3h1v2h2V3h1v1h1v2h1v6h-1v1H9v1H6v-1H4v-1H3V6h2z"/>
  <path fill="#111111" d="M6 3h1v2H6zm3 0h1v2H9zM5 5h6v1H5zM3 6h1v6H3zm8 0h1v6h-1zM6 8h1v1H6zm3 0h1v1H9zM7 10h2v1H7zm-3 2h2v1H4zm6 0h2v1h-2zM5 14h2v1H5zm9-2h1v1h-1z"/>
</svg>
```

- [ ] **Step 5: Create downward running frame 2**

Create `assets/cat-run-down-2.svg` with this content:

```xml
<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 16 16" shape-rendering="crispEdges">
  <path fill="#ffffff" d="M5 4h1V3h1v2h2V3h1v1h1v2h1v6h-1v1H9v1H6v-1H4v-1H3V6h2z"/>
  <path fill="#111111" d="M6 3h1v2H6zm3 0h1v2H9zM5 5h6v1H5zM3 6h1v6H3zm8 0h1v6h-1zM6 8h1v1H6zm3 0h1v1H9zM7 10h2v1H7zm-2 2h2v1H5zm5 0h2v1h-2zM2 13h2v1H2zm10 1h2v1h-2z"/>
</svg>
```

- [ ] **Step 6: Verify current tests still pass**

Run:

```powershell
npm test
```

Expected: PASS for all animation tests.

- [ ] **Step 7: Commit sprite assets**

Run:

```powershell
git add assets/cat-sit.svg assets/cat-run-up-1.svg assets/cat-run-up-2.svg assets/cat-run-down-1.svg assets/cat-run-down-2.svg
git commit -m "feat: add oneko style cat sprites"
```

Expected: commit succeeds with only SVG asset files staged.

---

### Task 4: Implement VS Code Gutter Rendering

**Files:**
- Create: `src/extension.ts`

- [ ] **Step 1: Write the extension controller**

Create `src/extension.ts` with this content:

```ts
import * as vscode from 'vscode';
import {
  CatMotionState,
  SpriteKind,
  advanceMotion,
  createMotionState,
  renderedLine,
  resetMotion,
  setTargetLine,
  spriteForState
} from './animation';

interface OnekoConfig {
  readonly enabled: boolean;
  readonly speedLinesPerSecond: number;
  readonly catScale: number;
}

const spriteFiles: Record<SpriteKind, string> = {
  sit: 'cat-sit.svg',
  'run-up-1': 'cat-run-up-1.svg',
  'run-up-2': 'cat-run-up-2.svg',
  'run-down-1': 'cat-run-down-1.svg',
  'run-down-2': 'cat-run-down-2.svg'
};

export function activate(context: vscode.ExtensionContext): void {
  const controller = new OnekoCatController(context);
  context.subscriptions.push(controller);
}

export function deactivate(): void {
}

class OnekoCatController implements vscode.Disposable {
  private readonly disposables: vscode.Disposable[] = [];
  private decorations = new Map<SpriteKind, vscode.TextEditorDecorationType>();
  private activeEditor: vscode.TextEditor | undefined;
  private motion: CatMotionState = createMotionState(0);
  private timer: NodeJS.Timeout | undefined;
  private lastTick = 0;
  private config: OnekoConfig;

  public constructor(private readonly context: vscode.ExtensionContext) {
    this.config = readConfig();
    this.recreateDecorations();
    this.registerCommands();
    this.registerEditorEvents();
    this.activateEditor(vscode.window.activeTextEditor, true);
  }

  public dispose(): void {
    this.stopTimer();
    this.clearAllDecorations();
    for (const decoration of this.decorations.values()) {
      decoration.dispose();
    }
    this.decorations.clear();
    vscode.Disposable.from(...this.disposables).dispose();
  }

  private registerCommands(): void {
    this.disposables.push(
      vscode.commands.registerCommand('onekoCat.enable', async () => {
        await vscode.workspace.getConfiguration('onekoCat').update('enabled', true, vscode.ConfigurationTarget.Global);
        this.applyConfigChange();
      }),
      vscode.commands.registerCommand('onekoCat.disable', async () => {
        await vscode.workspace.getConfiguration('onekoCat').update('enabled', false, vscode.ConfigurationTarget.Global);
        this.applyConfigChange();
      }),
      vscode.commands.registerCommand('onekoCat.toggle', async () => {
        const enabled = vscode.workspace.getConfiguration('onekoCat').get<boolean>('enabled', true);
        await vscode.workspace.getConfiguration('onekoCat').update('enabled', !enabled, vscode.ConfigurationTarget.Global);
        this.applyConfigChange();
      })
    );
  }

  private registerEditorEvents(): void {
    this.disposables.push(
      vscode.window.onDidChangeActiveTextEditor((editor) => this.activateEditor(editor, true)),
      vscode.window.onDidChangeTextEditorSelection((event) => {
        if (event.textEditor !== this.activeEditor || event.selections.length === 0) {
          return;
        }

        this.motion = setTargetLine(this.motion, event.selections[0].active.line, event.textEditor.document.lineCount);
        this.ensureTimer();
        this.render();
      }),
      vscode.workspace.onDidChangeTextDocument((event) => {
        if (!this.activeEditor || event.document !== this.activeEditor.document) {
          return;
        }

        this.motion = setTargetLine(this.motion, this.motion.targetLine, this.activeEditor.document.lineCount);
        this.render();
      }),
      vscode.workspace.onDidChangeConfiguration((event) => {
        if (event.affectsConfiguration('onekoCat')) {
          this.applyConfigChange();
        }
      })
    );
  }

  private activateEditor(editor: vscode.TextEditor | undefined, resetToCursor: boolean): void {
    this.activeEditor = isRenderableEditor(editor) ? editor : undefined;

    if (!this.config.enabled || !this.activeEditor) {
      this.hide();
      return;
    }

    if (resetToCursor) {
      this.motion = resetMotion(this.activeEditor.selection.active.line, this.activeEditor.document.lineCount);
    }

    this.render();
    this.ensureTimer();
  }

  private applyConfigChange(): void {
    const previousScale = this.config.catScale;
    this.config = readConfig();

    if (this.config.catScale !== previousScale) {
      this.recreateDecorations();
    }

    if (!this.config.enabled) {
      this.hide();
      return;
    }

    this.activateEditor(vscode.window.activeTextEditor, true);
  }

  private recreateDecorations(): void {
    this.clearAllDecorations();
    for (const decoration of this.decorations.values()) {
      decoration.dispose();
    }

    this.decorations = new Map(
      Object.entries(spriteFiles).map(([kind, fileName]) => {
        const iconPath = vscode.Uri.joinPath(this.context.extensionUri, 'assets', fileName);
        const decoration = vscode.window.createTextEditorDecorationType({
          gutterIconPath: iconPath,
          gutterIconSize: `${Math.round(16 * this.config.catScale)}px`
        });

        return [kind as SpriteKind, decoration];
      })
    );
  }

  private ensureTimer(): void {
    if (this.timer || !this.config.enabled || !this.activeEditor) {
      return;
    }

    this.lastTick = Date.now();
    this.timer = setInterval(() => this.tick(), 33);
  }

  private stopTimer(): void {
    if (this.timer) {
      clearInterval(this.timer);
      this.timer = undefined;
    }
  }

  private tick(): void {
    if (!this.config.enabled || !this.activeEditor) {
      this.hide();
      return;
    }

    const now = Date.now();
    const elapsedMs = now - this.lastTick;
    this.lastTick = now;
    this.motion = advanceMotion(
      this.motion,
      elapsedMs,
      this.config.speedLinesPerSecond,
      this.activeEditor.document.lineCount
    );
    this.render();

    if (this.motion.direction === 'idle') {
      this.stopTimer();
    }
  }

  private render(): void {
    if (!this.config.enabled || !this.activeEditor || this.activeEditor.document.lineCount <= 0) {
      this.hide();
      return;
    }

    const line = renderedLine(this.motion, this.activeEditor.document.lineCount);
    const range = new vscode.Range(line, 0, line, 0);
    const activeSprite = spriteForState(this.motion);

    for (const [sprite, decoration] of this.decorations) {
      this.activeEditor.setDecorations(decoration, sprite === activeSprite ? [range] : []);
    }
  }

  private hide(): void {
    this.stopTimer();
    this.clearAllDecorations();
  }

  private clearAllDecorations(): void {
    if (!this.activeEditor) {
      return;
    }

    for (const decoration of this.decorations.values()) {
      this.activeEditor.setDecorations(decoration, []);
    }
  }
}

function readConfig(): OnekoConfig {
  const config = vscode.workspace.getConfiguration('onekoCat');

  return {
    enabled: config.get<boolean>('enabled', true),
    speedLinesPerSecond: Math.max(1, config.get<number>('speedLinesPerSecond', 8)),
    catScale: Math.min(2, Math.max(0.5, config.get<number>('catScale', 1)))
  };
}

function isRenderableEditor(editor: vscode.TextEditor | undefined): editor is vscode.TextEditor {
  if (!editor || editor.document.lineCount <= 0) {
    return false;
  }

  const blockedSchemes = new Set(['debug', 'output', 'vscode-notebook-cell', 'walkThrough']);
  return !blockedSchemes.has(editor.document.uri.scheme);
}
```

- [ ] **Step 2: Compile and fix type errors if the exact VS Code types require adjustment**

Run:

```powershell
npm run compile
```

Expected: PASS. If TypeScript rejects `gutterIconSize` as a pixel string for the installed `@types/vscode`, change `gutterIconSize: `${Math.round(16 * this.config.catScale)}px`` to `gutterIconSize: 'contain'` and keep the rest of the implementation unchanged.

- [ ] **Step 3: Run unit tests**

Run:

```powershell
npm test
```

Expected: PASS for all animation tests.

- [ ] **Step 4: Commit extension integration**

Run:

```powershell
git add src/extension.ts
git commit -m "feat: render cat in active editor gutter"
```

Expected: commit succeeds with `src/extension.ts` staged.

---

### Task 5: Add Tests For Enablement State Helpers

**Files:**
- Modify: `src/animation.ts`
- Modify: `src/test/animation.test.ts`

- [ ] **Step 1: Add pure enablement helpers to the tests**

In `src/test/animation.test.ts`, change the import from `../animation` to include `nextEnabledState`:

```ts
import {
  advanceMotion,
  createMotionState,
  nextEnabledState,
  renderedLine,
  resetMotion,
  setTargetLine,
  spriteForState
} from '../animation';
```

Append this test to `src/test/animation.test.ts`:

```ts
test('updates enabled state for command actions', () => {
  assert.equal(nextEnabledState(false, 'enable'), true);
  assert.equal(nextEnabledState(true, 'disable'), false);
  assert.equal(nextEnabledState(true, 'toggle'), false);
  assert.equal(nextEnabledState(false, 'toggle'), true);
});
```

- [ ] **Step 2: Run tests and verify failure**

Run:

```powershell
npm test
```

Expected: FAIL because `nextEnabledState` is not exported from `src/animation.ts`.

- [ ] **Step 3: Implement enablement helper**

Append this content to `src/animation.ts`:

```ts
export type EnablementAction = 'enable' | 'disable' | 'toggle';

export function nextEnabledState(current: boolean, action: EnablementAction): boolean {
  if (action === 'enable') {
    return true;
  }

  if (action === 'disable') {
    return false;
  }

  return !current;
}
```

- [ ] **Step 4: Run tests**

Run:

```powershell
npm test
```

Expected: PASS for all animation and enablement tests.

- [ ] **Step 5: Commit helper tests**

Run:

```powershell
git add src/animation.ts src/test/animation.test.ts
git commit -m "test: cover cat enablement state"
```

Expected: commit succeeds with test and helper changes.

---

### Task 6: Wire Commands Through The Shared Enablement Helper

**Files:**
- Modify: `src/extension.ts`

- [ ] **Step 1: Update imports**

In `src/extension.ts`, change the import from `./animation` to include `EnablementAction` and `nextEnabledState`:

```ts
import {
  CatMotionState,
  EnablementAction,
  SpriteKind,
  advanceMotion,
  createMotionState,
  nextEnabledState,
  renderedLine,
  resetMotion,
  setTargetLine,
  spriteForState
} from './animation';
```

- [ ] **Step 2: Replace command registration body**

Replace the current `registerCommands` method in `src/extension.ts` with this method:

```ts
  private registerCommands(): void {
    this.disposables.push(
      vscode.commands.registerCommand('onekoCat.enable', () => this.updateEnabledFromCommand('enable')),
      vscode.commands.registerCommand('onekoCat.disable', () => this.updateEnabledFromCommand('disable')),
      vscode.commands.registerCommand('onekoCat.toggle', () => this.updateEnabledFromCommand('toggle'))
    );
  }
```

- [ ] **Step 3: Add command helper method**

Add this method inside `OnekoCatController` after `registerCommands`:

```ts
  private async updateEnabledFromCommand(action: EnablementAction): Promise<void> {
    const enabled = vscode.workspace.getConfiguration('onekoCat').get<boolean>('enabled', true);
    const nextEnabled = nextEnabledState(enabled, action);
    await vscode.workspace.getConfiguration('onekoCat').update('enabled', nextEnabled, vscode.ConfigurationTarget.Global);
    this.applyConfigChange();
  }
```

- [ ] **Step 4: Run tests and compile**

Run:

```powershell
npm test
```

Expected: PASS for all tests and TypeScript compilation.

- [ ] **Step 5: Commit command helper wiring**

Run:

```powershell
git add src/extension.ts
git commit -m "refactor: share cat enablement command logic"
```

Expected: commit succeeds with `src/extension.ts` staged.

---

### Task 7: Manual Extension Verification

**Files:**
- Modify only if manual verification reveals a defect in existing files.

- [ ] **Step 1: Compile before launching**

Run:

```powershell
npm run compile
```

Expected: PASS.

- [ ] **Step 2: Launch the Extension Development Host**

Open this folder in VS Code, then run the `Run Extension` launch configuration from the Run and Debug panel.

Expected: A second VS Code window opens as the Extension Development Host.

- [ ] **Step 3: Verify automatic active-editor rendering**

In the Extension Development Host, create or open a text file with at least 20 lines.

Expected: The cat appears in the gutter next to the active cursor line without running a command.

- [ ] **Step 4: Verify cursor following**

Move the cursor from line 1 to line 15.

Expected: The cat runs downward through the gutter toward line 15 at about `8` lines per second, then switches to the sitting sprite.

- [ ] **Step 5: Verify immediate retargeting**

While the cat is moving downward, move the cursor to line 3.

Expected: The cat changes target from its current visible position and runs upward toward line 3.

- [ ] **Step 6: Verify active editor switching**

Open a second text editor, place its cursor on line 8, and focus that editor.

Expected: The cat appears immediately on line 8 in the newly active editor. The previous editor no longer shows the cat.

- [ ] **Step 7: Verify hide behavior**

Focus a non-text view such as the Welcome page or Settings UI.

Expected: The cat is not visible.

- [ ] **Step 8: Verify commands**

Run `Oneko Cat: Disable`, then `Oneko Cat: Enable`, then `Oneko Cat: Toggle` from the command palette.

Expected: Disable clears the cat immediately. Enable restores it at the active cursor line. Toggle switches between those states.

- [ ] **Step 9: Verify settings**

Set `onekoCat.speedLinesPerSecond` to `16` and move the cursor across many lines.

Expected: The cat moves about twice as fast as the default. Set `onekoCat.catScale` to `1.5`.

Expected: The gutter icon size changes without restarting VS Code.

- [ ] **Step 10: Commit verification fixes or record clean verification**

If manual verification required code fixes, run:

```powershell
npm test
git add src package.json package-lock.json assets .vscode .vscodeignore tsconfig.json
git commit -m "fix: polish oneko cat extension behavior"
```

Expected: tests pass and the commit contains only files changed to fix manual verification issues.

If no fixes were needed, run:

```powershell
git status --short
```

Expected: no implementation files are modified.

---

## Self-Review

- Spec coverage: The plan covers a new TypeScript VS Code extension, glyph margin rendering, active-editor-only behavior, immediate active-editor reset, primary cursor tracking, time-based movement at `8` lines per second, immediate retargeting, hiding outside renderable editors, original bundled SVG sprites, commands, settings, and verification.
- Placeholder scan: No unresolved placeholders are present.
- Type consistency: The animation module exports `CatMotionState`, `SpriteKind`, `advanceMotion`, `createMotionState`, `renderedLine`, `resetMotion`, `setTargetLine`, `spriteForState`, `EnablementAction`, and `nextEnabledState`; the extension imports those names consistently.
