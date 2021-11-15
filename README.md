# Wolf Mapper
[![Build Status](https://img.shields.io/github/workflow/status/wolf-plugins/wolf-mapper/Wolf%20Mapper%20CI.svg?logo=github)](https://github.com/wolf-plugins/wolf-mapper/actions?query=workflow%3A%22Wolf+Mapper+CI%22)

![Wolf Mapper](https://raw.githubusercontent.com/wolf-mapper/wolf-mapper/master/docs/images/screenshot.png)

Wolf Mapper is a MIDI remapping plugin. It can be built as an LV2 or VST plugin and as a standalone Jack application.

## Build manually

First, clone the repo (note the "--recursive" argument):

```
git clone --recursive https://github.com/wolf-plugins/wolf-mapper.git
cd wolf-mapper
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
