// ============================================================
//  sylinthui.h — C/C++ header for SylinthUI v0.1.0
// ============================================================

#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct SylinthHandle SylinthHandle;
    typedef void (*SylinthEventCallback)(const char* event_name, const char* payload);

    // ── Lifecycle ─────────────────────────────────────────────────

    /** Create a window with an exact pixel size. */
    SylinthHandle* sylinth_create(
        const char* title,
        unsigned int width,
        unsigned int height,
        const char* url,
        int          transparent
    );

    /**
     * Create a window sized as a percentage of the primary monitor.
     * width_pct / height_pct: 0.0 – 100.0
     *
     * Example — 80% of the screen in both axes:
     *   sylinth_create_percent("My App", 80.0f, 80.0f, url, 0);
     */
    SylinthHandle* sylinth_create_percent(
        const char* title,
        float       width_pct,
        float       height_pct,
        const char* url,
        int         transparent
    );

    void sylinth_destroy(SylinthHandle* handle);

    // ── Event registration ────────────────────────────────────────

    /**
     * Register a C callback for a named event.
     *
     * Built-in events:
     *   "sylinth:ready"   — WebView finished loading
     *   "sylinth:close"   — close was requested
     *   "sylinth:focus"   — focus changed  {"focused": true/false}
     */
    void sylinth_on(SylinthHandle* handle, const char* event_name, SylinthEventCallback cb);
    void sylinth_off(SylinthHandle* handle, const char* event_name);

    // ── Pre-run config (call BEFORE sylinth_run) ──────────────────

    /** 1 = visible (default), 0 = start hidden */
    void sylinth_set_initially_visible(SylinthHandle* handle, int visible);

    /** 1 = interactive (default), 0 = click-through */
    void sylinth_set_initially_interactive(SylinthHandle* handle, int interactive);

    /** Exact pixel position */
    void sylinth_set_initial_position(SylinthHandle* handle, int x, int y);

    /**
     * Position by alignment string.
     * alignx / aligny: "start" | "center" | "end"
     */
    void sylinth_set_initial_position_aligned(SylinthHandle* handle, const char* alignx, const char* aligny);

    /**
     * Corner style (Windows 11+).
     * style: "default" | "none" | "round" | "small"
     */
    void sylinth_set_initial_corners(SylinthHandle* handle, const char* style);

    /** 1 = always on top, 0 = normal (default) */
    void sylinth_set_initially_on_top(SylinthHandle* handle, int on_top);

    /** 1 = focus locked, 0 = normal (default) */
    void sylinth_set_initially_focus_locked(SylinthHandle* handle, int locked);

    /**
     * 0 = resize locked (default), 1 = resizable.
     * When locked the user cannot resize by dragging the window edge.
     */
    void sylinth_set_initially_resizable(SylinthHandle* handle, int resizable);

    // ── Runtime controls (call AFTER sylinth_run is running) ──────

    /** Show (1) or hide (0) the window. */
    void sylinth_set_visible(SylinthHandle* handle, int visible);

    /** 1 = interactive, 0 = click-through. */
    void sylinth_set_interactive(SylinthHandle* handle, int interactive);

    /** Move to exact pixel coordinates. */
    void sylinth_set_position(SylinthHandle* handle, int x, int y);

    /** Move using alignment strings: "start" | "center" | "end" */
    void sylinth_set_position_aligned(SylinthHandle* handle, const char* alignx, const char* aligny);

    /** Change corner style: "default" | "none" | "round" | "small" */
    void sylinth_set_corners(SylinthHandle* handle, const char* style);

    /** 1 = always on top (HWND_TOPMOST), 0 = normal. */
    void sylinth_set_always_on_top(SylinthHandle* handle, int on_top);

    /**
     * 1 = focus locked (steals focus back when lost), 0 = unlocked.
     * Use while a menu is open; unlock when menu closes.
     */
    void sylinth_set_focus_lock(SylinthHandle* handle, int locked);

    /** 0 = resize locked, 1 = resizable. Can be toggled at runtime. */
    void sylinth_set_resizable(SylinthHandle* handle, int resizable);

    /** Resize to exact pixels at runtime. */
    void sylinth_resize(SylinthHandle* handle, unsigned int width, unsigned int height);

    /**
     * Resize to a percentage of the current monitor at runtime.
     * width_pct / height_pct: 0.0 – 100.0
     */
    void sylinth_resize_percent(SylinthHandle* handle, float width_pct, float height_pct);

    // ── Run ───────────────────────────────────────────────────────

    /** Start the window event loop on an internal OS thread. Returns immediately to the caller. */
    void sylinth_run(SylinthHandle* handle);

    // ── Info ──────────────────────────────────────────────────────

    const char* sylinth_version();

    // ── Emit to JS ───────────────────────────────────────────────

    /**
     * Fire a named event with a JSON payload into the JS page.
     * Safe to call from any thread while the window is running.
     *
     * On the JS side, listen with:
     *   Sylinth.on('eventName', (data) => { ... });
     *
     * Example:
     *   sylinth_emit(ui, "tornadoSpawned", "{\"intensity\":3,\"follow\":true}");
     *   sylinth_emit(ui, "healthUpdated",  "{\"hp\":80,\"max\":100}");
     *   sylinth_emit(ui, "menuClosed",     "{}");
     */
    void sylinth_emit(
        SylinthHandle* handle,
        const char* event_name,
        const char* payload
    );

#ifdef __cplusplus
} // extern "C"
#endif

// ============================================================
//  GTA V mod usage example:
//
//  SylinthHandle* ui = sylinth_create_percent(
//      "TornadoV", 70.0f, 75.0f,          // 70% x 75% of screen
//      "file:///C:/TornadoV/ui/index.html", 0
//  );
//
//  sylinth_set_initial_position_aligned(ui, "center", "center");
//  sylinth_set_initial_corners(ui, "round");
//  sylinth_set_initially_on_top(ui, 1);    // always above GTA V
//  sylinth_set_initially_visible(ui, 0);   // start hidden
//  sylinth_set_initially_interactive(ui, 0);
//
//  sylinth_on(ui, "sylinth:ready", on_ready);
//  sylinth_on(ui, "sylinth:close", on_close);
//
//  // On F5 keypress:
//  void toggle_menu() {
//      g_open = !g_open;
//      sylinth_set_visible(ui, g_open);
//      sylinth_set_interactive(ui, g_open);
//      sylinth_set_focus_lock(ui, g_open); // lock while open, release when closed
//  }
//
//  sylinth_run(ui);
//  sylinth_destroy(ui);
// ============================================================