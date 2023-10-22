from subprocess import call
from pathlib import Path
import os


# AddOption(
# '--git',
# type    = 'string',
# nargs   = 1,
# action  = 'store',
# help    = 'use --git=no-sub-update to disable the submodule update')

## Update the git submodules
# ---------------------------------------------------
# if GetOption('git') != 'no-sub-update':
    # call(["git", "submodule", "update", "--init", "--recursive"])


env = Environment()

project_root = Path.cwd()
wiiuse_dir =  Path("./wiiuse")
builddir =  Path("./build")
if not builddir.exists():
	builddir.mkdir()



# build cmake dependencies (wiiuse)
os.chdir(str(builddir))
call("cmake -DBUILD_EXAMPLE=OFF -DBUILD_EXAMPLE_SDL=OFF -DINSTALL_EXAMPLES=OFF ../wiiuse".split(" "))
call("make".split(" "))
os.chdir(str(project_root))



env.AppendUnique(CPPPATH=['.', wiiuse_dir.joinpath("src")])

env.Append(LIBS = ['bluetooth', builddir.joinpath("src/libwiiuse.a")])

sources = ['src/main.cpp']

env.Program(target='godot-wiimote', source=sources)

# env.SharedLibrary(
