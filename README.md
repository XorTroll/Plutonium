# Plutonium - C++ UI library for libnx (using SDL2)

- If you came here looking for `CustomUI`, this is it's evolution, with a way more rich UI.

## What is Plutonium?

- Plutonium is a high-level, C++ graphical libraries to make UIs.

- It uses libnx and SDL2, so both libraries are required.

- Exactly, these extra libraries are required: `-lnx -lfreetype -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lpng -ljpeg`

## Internal structure and performance

- This library uses software-accelerated SDL2 rendering.

- This library's performance is based on WPF's system. The user doesn't directly interact with the rendering, as it's done by elements, same way WPF works with `FrameworkElement` and `Window` objects, Plutonium has `pu::element::Element` and `pu::Application`.

- Same way WPF does, you can create an UI by making a custom Application class inheriting from `pu::Application` class, or simply creating a variable and adding elements to it.

- The main function to initialize the application is `Show()`.

- Check the examples (soon) for more detailed information.

- Documentation is also coming soon.