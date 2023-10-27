# godot-wiimote

A Wii Remote interface for Godot4 using GDExtension

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
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLE_SDL=NO
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

