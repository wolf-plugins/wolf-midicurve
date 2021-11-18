# Wolf MidiCurve
[![Build Status](https://img.shields.io/github/workflow/status/wolf-plugins/wolf-midicurve/Wolf%20MidiCurve%20CI.svg?logo=github)](https://github.com/wolf-plugins/wolf-midicurve/actions?query=workflow%3A%22Wolf+MidiCurve+CI%22)

Wolf MidiCurve is a MIDI remapping plugin. It can be built as an LV2 or VST plugin and as a standalone Jack application.

## Build manually

First, clone the repo (note the "--recursive" argument):

```
git clone --recursive https://github.com/wolf-plugins/wolf-midicurve.git
cd wolf-midicurve
```

Then, run:

```
make
```

All plugin builds will then be placed in the bin folder. Copy them to their appropriate place so that your plugin host can find them, and you're done :)

## Updating

This project uses git submodules. Thus, to update your local copy of the repo, you need to run the following commands:
```
git pull
git submodule update --init --recursive
```
You should then be able to build the plugin with the most recent changes.
