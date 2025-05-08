# Changelog history

## Changelog for [next release]:

- Added support for scrolling layout background images: by changing the X value, the background is shifted while it "reappears" on the other side, allowing for some cool effects

- `pu::ui::render::LoadImage` is now `pu::ui::render::LoadImageFromFile`, and a new `pu::ui::render::LoadImageFromBuffer` was added as a wrapper to load images directly from existing data/memory

- Text rendering and clamping were properly done now, so that newlines still wrap the text (thus actually introduce a new line when rendering) and reaching the screensize no longer causes it to wrap (since this effect conflicted with the clamping system)

- Removed `Overlay` class, and merged the logic of `Layout`/`Dialog`/`Toast` into a more general `Layer` class

- Introduced automatic focus handling, similar to Nintendo's UI (when moving through elements using the D-pad or joysticks)

- Removed simulated-touch functionality from `Layout`s (it served basically no useful purpose)

- Input is no longer handled while fading in/out (fixes issues where, if a new layout was loaded mid-fade, things could get messy)

- Abstracted away the text-rending code repeated in many places until now (`TextBlock`, `Toast`, `Button`...) into a new `Text` object containing rendered text, now used by all these elements

- Added a new shadow-rendering function, used by several elements from now on

- Buttons (...)

- `ProgressBar` now supports being movable (so the user can use the joysticks to increment/decrement it, when the element is focused, or even via touchmode regardless if the `ProgressBar` is focused or not)

- Removed `Rectangle` element since it has very little use: rectangles are used in tandem with other rendered stuff, so they should be rendered within those other elements (as it's already done)

- Removed `Toggle` element (...)

- Rendering now works on the base of `Group`s, which serve as nicer ways to align `Element`s (what originally `Container` was meant to be used for, but didn't in the end, which is now removed). Both `Group` and `Element` inherit from `Renderizable`, which has part of the properties that used to be in `Element` (this is due to the fundamental differences between groups and elements)

- Touch handling got drastically improved thanks to two new helper classes:

  - `TouchDetector`, containing the logic of detecting if a given region is held or clicked (essentially button logic)

  - `TouchScroller`, containing the logic for managing scrolling through a region

- Support for rendering within a specific region was added, wrapping `SDL_SetRenderClipRect` in `PushRenderRegion` and `PopRenderRegion` functions

- Added `Separator` element, specially useful in long groups

- Finally grouped default UI/element values in a global `Style` object, with even more tuneable properties, that allows to define the global style of an application!

- Introduced a helper `ColorVariation` class to interpolate smoothly between two different colors

- Improved the `Color::FromHex` conversion, splitting it into two compile-time constexpr functions and a run-time function which performs further sanity checks.
