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
