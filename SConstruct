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



# build cmake dependencies (wiiuse)




env.Append(LIBS = ['wiiuse','bluetooth'])

sources = ['src/main.cpp']

env.Program(target='godot-wiimote', source=sources)

# env.SharedLibrary(
