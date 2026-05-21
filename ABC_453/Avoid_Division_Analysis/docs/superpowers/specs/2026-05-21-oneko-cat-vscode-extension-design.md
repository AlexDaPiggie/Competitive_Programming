# Oneko Cat VS Code Extension Design

## Summary

Build a new Visual Studio Code extension in this folder that displays a small oneko-inspired cat in the editor gutter, next to the line numbers. The cat is visible only in the currently active normal text editor. It appears immediately at the active editor's primary cursor line when the active editor changes, then follows later cursor movement vertically with a slow running animation.

The implementation will use supported VS Code extension APIs. Specifically, the cat will be rendered with editor decorations using `gutterIconPath`, which places it in the glyph margin adjacent to the line-number area.

## Goals

- Create a new TypeScript VS Code extension project in this folder.
- Show the cat automatically when VS Code starts and a normal text editor is active.
- Render the cat in the gutter area to the right of the line-number bar using supported decoration APIs.
- Track only the primary active cursor.
- Animate vertical movement toward the cursor line at a default speed of `8` lines per second.
- Retarget immediately from the cat's current position when the cursor moves during animation.
- Hide the cat when no normal text editor is active.
- Provide enable, disable, and toggle commands.
- Provide settings for enablement, movement speed, and cat scale.

## Non-Goals

- Do not inject into VS Code's internal DOM or CSS.
- Do not place the cat inside the actual line-number DOM.
- Do not track secondary cursors or multiple selections.
- Do not show separate cats in inactive editor panes.
- Do not copy original oneko artwork.

## User Experience

When the extension is enabled, the active text editor shows one small cat in the gutter beside the active cursor line. When the cursor moves to another line, the cat runs vertically toward that line. If the cursor moves again before the cat arrives, the cat changes direction or target immediately from its current animated position.

When the cat reaches the cursor line, it switches to a sitting frame. While moving up it alternates between two running-up frames. While moving down it alternates between two running-down frames.

When the user switches to another text editor, the cat appears immediately at that editor's primary cursor line rather than animating from the previous editor's line. When the active view is not a normal text editor, the decoration is cleared.

## Rendering And Assets

The extension will bundle original SVG sprites inspired by classic oneko:

- `assets/cat-sit.svg`
- `assets/cat-run-up-1.svg`
- `assets/cat-run-up-2.svg`
- `assets/cat-run-down-1.svg`
- `assets/cat-run-down-2.svg`

The sprites should be tiny, high-contrast, and legible in the gutter across light and dark themes. They will be original pixel-art-style assets rather than copies of the original oneko sprites.

Rendering will use `vscode.window.createTextEditorDecorationType` with `gutterIconPath`. Only one active decoration should be applied at a time. The decoration range should target the rounded current cat line in the active editor.

## Architecture

The extension will have a small set of focused responsibilities:

- Activation and command registration in `extension.ts`.
- Configuration reading and change handling.
- Active editor tracking.
- Cursor target tracking.
- Animation state and timing.
- Decoration creation, disposal, and updates.

The cat state should store:

- Active editor identity.
- Current floating line position.
- Target line position.
- Last animation timestamp.
- Current movement direction.
- Current sprite frame index.
- Enabled state.

Line positions should be stored internally as zero-based values to match VS Code APIs. Settings and user-facing behavior can still be described in one-based line terms.

## Animation Model

The animation loop runs only when the extension is enabled and a normal active text editor exists. Each frame computes elapsed time since the previous frame and moves the cat toward the target by:

```text
deltaLines = speedLinesPerSecond * elapsedSeconds
```

If the remaining distance is less than or equal to `deltaLines`, the cat snaps to the target and switches to the sitting frame. Otherwise, the cat advances toward the target and shows the appropriate running-up or running-down frame.

The rendered line is the nearest integer line to the current floating position, clamped to the document's valid line range. Cursor changes update the target line immediately. Active editor changes reset the current and target line to the new editor's primary cursor line.

## Commands

The extension will contribute these commands:

- `onekoCat.enable`: `Oneko Cat: Enable`
- `onekoCat.disable`: `Oneko Cat: Disable`
- `onekoCat.toggle`: `Oneko Cat: Toggle`

Disabling the extension feature clears the current gutter decoration immediately. Enabling it restores the cat in the active text editor at the current primary cursor line.

## Settings

The extension will contribute these configuration keys:

- `onekoCat.enabled`: boolean, default `true`.
- `onekoCat.speedLinesPerSecond`: number, default `8`, minimum `1`.
- `onekoCat.catScale`: number, default `1`, minimum `0.5`, maximum `2`.

Configuration changes should apply without requiring a VS Code restart. If `onekoCat.enabled` changes, the runtime state should update immediately. If speed changes during movement, the next animation frame should use the new speed.

## Error Handling And Edge Cases

- If no active text editor exists, clear decorations and stop visible updates.
- If the active editor is undefined or not a normal text document editor, hide the cat.
- If the target line is outside the document after edits, clamp it to the document's valid line range.
- If the document has zero lines according to an unexpected API state, clear the decoration.
- Dispose old decoration types when switching sprites or deactivating to avoid leaking VS Code resources.
- Avoid running unnecessary timers when the cat is idle, disabled, or hidden.

## Testing

Unit tests should cover the logic that does not require VS Code rendering:

- Movement toward a target at `8` lines per second.
- Retargeting during movement from the current floating position.
- Clamping line positions to document bounds.
- Immediate reset on active editor change.
- Enable, disable, and toggle state transitions.
- Sprite direction selection for sitting, running up, and running down.

Manual verification should run the extension in the VS Code Extension Development Host and check:

- The cat appears automatically in the active text editor.
- The cat is in the gutter next to the line numbers.
- It appears at the cursor line immediately after editor switches.
- It follows cursor line changes vertically at the configured speed.
- It hides outside normal text editors.
- Commands and settings take effect without restarting VS Code.
