# Plutonium - an easy-to-use UI framework for Nintendo Switch homebrew

## What is Plutonium?

Plutonium is a high-level, C++ graphical library with the aim of making UIs in a more user-firendly way.

It uses libnx and SDL2, so both libraries are required.

To be more exact, this libraries should be installed via pacman:

```
-lnx -lfreetype -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lSDL2 -lEGL -lGLESv2 -lglapi -ldrm_nouveau -lpng -ljpeg `sdl2-config --libs` `freetype-config --libs`
```

## Internal structure and performance

Plutonium uses software-accelerated SDL2 rendering.

Plutonium's performance is based on WPF's system. The user doesn't directly interact with the rendering, as it's done via a main rendering system and different objects to render.

Same way WPF does, you can create an UI by making a custom Application class inheriting from `pu::Application` class, or simply creating a variable and adding elements to it.

The main function to initialize the application is `Show()`.

Check the [examples](Examples) for a basic usage of the libraries. In case you want to see a really powerful app which really shows what Plutonium is capable of, take a look at [Goldleaf](https://github.com/XorTroll/Goldleaf).

Check the [documentation](https://XorTroll.github.io/Plutonium/) for a more detailed explanation of the library's usage.

## Using this libraries

On the [releases](https://github.com/XorTroll/Plutonium/releases) page you have all the released versions. All of them are zipped files, containing `include` and `lib` directories.

To link them to a devkitPro libnx project, on the `LIBDIRS` variable of the Makefile add the folder containing the two folders mentioned above. (if you set `plutonium`, place the other two folders as `plutonium/include` and `plutonium/lib`)

Include the main header:

```cpp
#include <pu/Plutonium>
```

And don't forget to add the libraries mentioned in the first section!

## Building

Clone the repository, go into `Plutonium` directory and run `make`.

You will need devkitPro, libnx and all the libraries mentioned above installed via pacman.

## Support

If you would like to be more informed about my projects' status and support, you should check [H&H](https://discord.gg/3KpFyaH), my Discord server. It's a simple server for Homebrew and Hacking, focused on my projects. If you would like to be a beta-tester, you might be interested on the nightly building system we have there for testers.

If you like my work, you should take a look at my [Patreon](https://patreon.com/xortroll) page. For those who support me, you will be credited on my projects, and you'll gain some nice extras on H&H!