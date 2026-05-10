# SylinthUI

[Website](https://blueisatlantic.github.io/blueisatlantic-projects/sylinth.html) | [Discord](https://discord.gg/Zw42bNmhKJ)

SylinthUI is a cross-platform native UI runtime designed for rendering real-time interactive interfaces using platform WebView engines.

It exposes a C-compatible ABI for integration with any programming language that supports calling native C/C++ libraries.

The core system is implemented in Rust, but SylinthUI itself is language-agnostic by design.

---

## Overview

SylinthUI provides a unified runtime for building and controlling UI layers such as control panels, overlays, HUDs, and embedded interface systems.

It is not tied to any specific programming language or application framework.

Instead, it acts as a native UI execution layer that can be embedded into existing software through a stable ABI.

---

## Key Characteristics

- Native runtime UI system
- Language-agnostic integration via C-compatible ABI
- Rust-based core implementation
- Cross-platform WebView rendering backend
- Decoupled UI execution layer
- Real-time overlay support
- Non-blocking UI lifecycle model

---

## Architecture

SylinthUI consists of three primary layers:

### Core Runtime (Rust implementation)
The internal engine responsible for:
- UI lifecycle management
- window and overlay control
- input handling
- event dispatching
- backend abstraction

Rust is used as the implementation language for performance and safety, but it is not exposed as a requirement for integration.

---

### Rendering Layer (WebView Engine)
The UI is rendered using native platform WebView technologies:

- Windows: WebView2 (Edge runtime)
- macOS: WebKit (WKWebView)
- (optional Linux backend depending on implementation)

The UI layer itself is written using standard web technologies:
- HTML
- CSS
- JavaScript

---

## UI Lifecycle

SylinthUI uses a state-based lifecycle model:

- Uninitialized
- Initializing
- Ready
