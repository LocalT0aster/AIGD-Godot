# AI in GameDev Homework

This repository is a **full Godot 4.5.x game project** that uses a C++ GDExtension for core gameplay logic.
The professor‑graded C++ code lives in `src/` (the GDExtension “plugin”), and the actual playable game is in `test_project/`.

**What’s in here**

- `test_project/` — the Godot game project you run/export.
- `src/` — C++ GDExtension code (the professor’s plugin).
- `godot-cpp/` — C++ bindings (git submodule).
- `doc_classes/` — XML docs for the extension.
- `.github/workflows/` — CI pipelines (plugin build, game export, cache clear).

## Requirements

- [GitHub](https://github.com/) account because we are going to be using GitHub Actions for cross platform compilation
- [Git](https://git-scm.com/downloads) installed on your machine and configured correctly so you can push changes to remote
- [Python](https://www.python.org/) latest version and ensure it's available in <b>system environment PATH</b>
- [Scons](https://scons.org/) latest version and ensure it's available in <b>system environment PATH</b>
  - Windows command: `pip install scons`
  - macOS command: `python3 -m pip install scons`
  - Linux command `python3 -m pip install scons`
- C++ compiler
  - Windows: MSVC (Microsoft Visual C++) via Visual Studio or Build Tools.
  - macOS: Clang (included with Xcode or Xcode Command Line Tools).
  - Linux: GCC or Clang (available via package managers).
- [Visual Studio Code](https://code.visualstudio.com/) or any other editor that supports C++ and the `compile_commands.json`

<details>
<summary>what if I don't want to use `compile_commands.json`?</summary>
Here are some include directories, if you are stubbornly choosing not to use compile_commands.json or if for some reason your editor needs it for extra features (Visual Studio Code will NOT need it as long as we use the Clangd extension)

```
${workspaceFolder}/godot-cpp/gdextension/
${workspaceFolder}/godot-cpp/gen/**
${workspaceFolder}/godot-cpp/include/**
${workspaceFolder}/godot-cpp/src/**

${workspaceFolder}/src -> usually where you write all your code
```

</details>

## Quick Start

1. Clone this repo `git clone <url>`.
2. Clone the godot-cpp submodule:
   ```bash
   git submodule update --init --recursive
   ```
3. Configure the repo using setup.py
   ```bash
   python setup.py
   ```
4. Open `test_project/` in Godot and run the game.

## Build the GDExtension

**VS Code task**

- Run the default task `Build GDExtension` with <kbd>Ctrl</kbd>+<kbd>⇧Shift</kbd>+<kbd>B</kbd>
- It compiles the extension for the platfor you are on.

**Manual SCons build**

```bash
# Optional: generate compile_commands.json
scons compiledb=yes

# Debug build (for development)
scons target=template_debug

# Release build (for exports)
scons target=template_release
```

Artifacts go to `bin/` and are referenced by `test_project/<PLUGIN_NAME>/<PLUGIN_NAME>.gdextension`.

## Setup Tool (`setup.py`)

Run the interactive helper to keep project metadata consistent:

```bash
python setup.py
```

Options include:

- Change targeted Godot version
- Change build profile
- Rename plugin
- Compile debug build
- Generate missing XML docs

## Running the Game Locally

### Simple way

Download the artifact of the branch you need at **[Releases](https://github.com/LocalT0aster/AIGD-Godot/releases)**

### Run with Godot editor

1. Build the GDExtension (debug for editor, release for exports).
2. Open `test_project/` in Godot.
3. Run (`F5`) from the editor.

## CI / Pipelines

### Build GDExtension (CI)

Workflow: **Build GDExtension Cross Platform Plugin**
File: `.github/workflows/build-plugin.yml`

Inputs:

- `build_type`: `release_only`, `debug`, or `both`
- `precision`: `single`, `double`, or `both`
- `lto`: `none` or `auto`
- `use_cache`: `true`/`false`

### Build & Export Game (CI)

Workflow: **Build Godot Project (with GDExtension)**
File: `.github/workflows/build-game.yml`

What it does:

- Builds the GDExtension first.
- Installs it into `test_project/`.
- Exports Win/Linux/mac builds.
- Optionally creates an immutable GitHub Release tagged `<branch>-<shortsha>`.

Inputs:

- `build_type`: `release_only`, `debug`, or `both`
- `precision`: `single`, `double`, or `both`
- `lto`: `none` or `auto`
- `use_cache`: `true`/`false`
- `create_release`: `true`/`false`

Artifact naming:

- `windows_release`, `windows_debug`
- `linux_release`, `linux_debug`
- `mac_release`, `mac_debug`

### Clear CI Cache (CI)

Workflow: **Clear Actions Cache**
File: `.github/workflows/clear-cache.yml`

## How to Run the Pipeline

1. Go to **GitHub Actions**.
2. Choose **Build Godot Project (with GDExtension)**.
3. Click **Run workflow**, set inputs (`build_type`, etc.).
4. Download artifacts or enable `create_release` for a tagged release.

## Notes

- This repo is **game‑oriented**; the GDExtension in `src/` is the professor‑graded component.
- If you change `godot-cpp` versions, consider running the cache clear workflow.
