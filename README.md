# mgl

**M**ay**GL**. MGL is the updated version of MayGL. mgl is a game engine build ontop of SDL2 and OpenGL.

# build and install

To build mgl simpily run

```
cd mgl
make
```

This will create a file called `libmgl.dylib` inside the `mgl/bin/` directory. To include in your project add `mgl/include/` to your header search paths
and `mgl/bin/libmgl.dylib` to your linking stage.

**THIS IS FOR MAC ONLY**. In order to get this working on windows or linux, replace mgl/lib/SDL2.framework with a relevent build of SDL2.

# Mac linking issues

Mac has issues with linking dylibs to a projects due to rpaths. In order to fix this when linking, use the follow flags:
```
-Lpath/to/mgl/bin/ -lmgl -rpath "$(shell pwd)"/path/to/mgl/bin/
```
Include this line to your linker flags (for a Makefile). This line includes mgl as a libary and adds the path to `mgl/bin/` to the list of rpaths

# Usage

**MAKEFILE UNDER CONSTRUCTION**