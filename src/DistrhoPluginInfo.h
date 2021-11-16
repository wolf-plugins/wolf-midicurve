#pragma once

#define DISTRHO_PLUGIN_NAME  "Wolf MidiCurve"
#define DISTRHO_PLUGIN_BRAND "Wolf Plugins"
#define DISTRHO_PLUGIN_URI   "https://github.com/wolf-plugins/wolf-midicurve"

#define DISTRHO_PLUGIN_HAS_UI          1

#define DISTRHO_PLUGIN_NUM_INPUTS       0
#define DISTRHO_PLUGIN_NUM_OUTPUTS      0
#define DISTRHO_PLUGIN_WANT_PROGRAMS    0
#define DISTRHO_PLUGIN_USES_MODGUI      0
#define DISTRHO_UI_USE_NANOVG           1
#define DISTRHO_PLUGIN_WANT_STATE       1
#define DISTRHO_PLUGIN_WANT_FULL_STATE  0
#define DISTRHO_PLUGIN_WANT_MIDI_INPUT  1
#define DISTRHO_PLUGIN_WANT_MIDI_OUTPUT 1

#define DISTRHO_PLUGIN_LV2_CATEGORY "lv2:MIDIPlugin"

/*
 * See https://lv2plug.in/ns/lv2core#hardRTCapable
 * I believe this plugin is not hard rt-capable, because the amount of time for a run() call depends on the plugin state.
 */
#define DISTRHO_PLUGIN_IS_RT_SAFE      0
