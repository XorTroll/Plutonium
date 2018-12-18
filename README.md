# Plutonium - an easy-to-use UI framework for Nintendo Switch homebrew

## What is Plutonium?

- Plutonium is a high-level, C++ graphical library with the aim of making UIs in a more user-firendly way.

- It uses libnx and SDL2, so both libraries are required.

- Exactly, these extra libraries are required:

```
-lnx -lfreetype -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lSDL2 -lEGL -lGLESv2 -lglapi -ldrm_nouveau -lpng -ljpeg `sdl2-config --libs` `freetype-config --libs`
```

## Internal structure and performance

- This library uses software-accelerated SDL2 rendering.

- This library's performance is based on WPF's system. The user doesn't directly interact with the rendering, as it's done via a main rendering system and different objects to render.

- Same way WPF does, you can create an UI by making a custom Application class inheriting from `pu::Application` class, or simply creating a variable and adding elements to it.

- The main function to initialize the application is `Show()`.

- Check the [examples](Examples) for a basic usage of the libraries.

- Check the [documentation](https://XorTroll.github.io/Plutonium/) for a more detailed explanation of the library's usage.

## Patreon

If you like my work, you should take a look at my [Patreon](https://patreon.com/xortroll)!