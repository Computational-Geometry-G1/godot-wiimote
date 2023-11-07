# godot-wiimote

A Wii Remote interface for Godot4 using GDExtension.

This is based on the [godot-cpp template](https://github.com/godotengine/godot-cpp-template), a quickstart template for GDExtension development with Godot 4.0+.

## Contents
* An empty Godot project (`demo/`)
* godot-cpp as a submodule (`godot-cpp/`)
* GitHub Issues template (`.github/ISSUE_TEMPLATE.yml`)
* GitHub CI/CD to publish your library packages when creating a release (`.github/workflows/builds.yml`)
* preconfigured source files for C++ development of the GDExtension (`src/`)

## Building
Ensure dependencies are installed.

this includes making sure [WiiUse](https://github.com/wiiuse/wiiuse) library is installed in the correct location

Wiiuse may also depend on additional things based on your platform.

to build wiiuse (unix):
```
git clone https://github.com/wiiuse/wiiuse.git
cd wiiuse
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLE_SDL=NO -DBUILD_SHARED_LIBS=TRUE
make wiiuse
sudo make install
```

### Linux/Unix
```
scons
```
### Mac
untested

### Windows
untested

