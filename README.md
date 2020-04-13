# Plutonium - an easy-to-use UI framework for Nintendo Switch homebrew

## What is Plutonium?

Plutonium is a high-level, C++ graphics library with the aim of making Nintendo Switch homebrew UIs in a more user-firendly way.

It uses libnx and SDL2, so both libraries are required.

To be more exact, this libraries should be installed via pacman:

```
switch-sdl2 switch-sdl2_ttf switch-sdl2_image switch-sdl2_gfx switch-sdl2_mixer switch-mesa switch-glad switch-glm switch-libdrm_nouveau switch-libwebp switch-libpng switch-freetype switch-bzip2 switch-libjpeg-turbo switch-opusfile switch-libopus
```

## Internal structure and performance

Plutonium internally uses SDL2 for UI rendering.

Plutonium's API is based on WPF/WinForms's system. The user doesn't directly interact with the rendering, as it's done via a main rendering system and different objects to render.

Check the [basic example](Example) for a basic usage of the libraries. In case you want to see a really powerful app which really shows what Plutonium is capable of, take a look at [Goldleaf](https://github.com/XorTroll/Goldleaf), [uLaunch](https://github.com/XorTroll/uLaunch) or many other homebrew apps made using this libraries.

Check the [documentation](https://XorTroll.github.io/Plutonium/) for a more detailed explanation of the library's usage.

## Using this libraries

On the [releases](https://github.com/XorTroll/Plutonium/releases) page you have all the released versions. All of them are zipped files, containing `include` and `lib` directories.

### Simple project layout

This is how a regular Plutonium project would (more or less) have its Makefile and project layout using Plutonium:

- Makefile

```Makefile
...

LIBS := -lpu -lfreetype -lSDL2_mixer -lopusfile -lopus -lmodplug -lmpg123 -lvorbisidec -logg -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lSDL2 -lEGL -lGLESv2 -lglapi -ldrm_nouveau -lwebp -lpng -ljpeg `sdl2-config --libs` `freetype-config --libs` -lnx
LIBDIRS := $(PORTLIBS) $(LIBNX) $(CURDIR)/Plutonium

...
```

- Project directory

```txt
Project
 |
 |-- Makefile
 |-- source
 |-- include
 |-- Plutonium
      |
      |-- include
      |-- lib
```

## Building

Clone the repository, cd into `Plutonium` directory and run `make`.

You will need devkitPro, libnx and all the libraries mentioned above installed via pacman.

## Support

If you would like to be more informed about my projects' status and support, you should check [my Discord server](https://discord.gg/3KpFyaH). It's a simple server for Nintendo homebrew and hacking stuff, focused on my projects. If you would like to take part in testing .

If you like my work, you should take a look at my [Patreon](https://patreon.com/xortroll) page!
