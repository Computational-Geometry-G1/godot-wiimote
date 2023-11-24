# godot-wiimote

A Wii Remote interface for Godot4 using GDExtension.

This is based on the [godot-cpp template](https://github.com/godotengine/godot-cpp-template), a quickstart template for GDExtension development with Godot 4.0+.

This project targets the latest verison of godot (4.1).

This repository was primarily created to perform wii remote head tracking using IR data from a static wii remote. While supporting additional functions of the wiimote are preferred, I am not familiar enough with godot to know what the best way to do this is - contributions are absolutely welcome!

## Contents
* An Godot project for demonstrating the functionality (`demo/`)
* godot-cpp as a submodule (`godot-cpp/`) to integrate with the WiiUse C++ library
* GitHub CI/CD confirm build functionality and upload library packages when creating a release (`.github/workflows/builds.yml`)
* source code for C++ GDExtension (`src/`)


## Dependencies 
In order to build, you must ensure dependencies are installed/available on your system.

### Wiiuse
Ensure the [WiiUse](https://github.com/wiiuse/wiiuse) library is installed in a location that can be found by your system

Wiiuse may also depend on additional things based on your platform, see the wiiuse README for more detailed, platform-specific instructions.

#### Building wiiuse (unix)
```
git clone https://github.com/wiiuse/wiiuse.git
cd wiiuse
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLE_SDL=NO -DBUILD_SHARED_LIBS=TRUE
make wiiuse
sudo make install
```

## Building
The build process should be realtively straghtforward since this project adheres to the typical GDExtension convention of using `scons` as a build system. For most platforms, the build process should just involve running the `scons` command.

## Setting up the extension in a fresh project
To add the extension to a godot 4.1+ project, open the project and import the .zip file [TBD, see #6] or the `.gdextension` file using the import button on the AssetLib tab of Godot.

## Usage
A minimal example of how to use the extension can be found in the [`demo`](./demo/) directory

When you start the demo by pressing the play button you will see the godot engine logo for longer than you may be used to (about 5 seconds) - as soon as you see this, hit the 1+2 buttons on your wii remote to make it discoverable. If it successfully discovers and connects to your remote, youll get a little vibration/buzz (like a real wii does) and the player 1 light on the wiimote will turn on.

If you successfully connect to a wiimote, then it should be looking for IR sensor data (such as from the sensor bar, or really any two IR sources spaced about that far apart - two candles may work in a pinch) to change the position of the camera (like [Johnny Lee's wiimote head tracking demo](https://www.youtub.com/watch/Jd3-eiid-Uw?t=155))


## Developer Documentation

For internal/development documentation see [`docs/index.md`](./docs/index.md)
