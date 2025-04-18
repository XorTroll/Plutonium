# Changelog history

## Changelog for [next release]:

- Added support for scrolling layout background images: by changing the X value, the background is shifted while it "reappears" on the other side, allowing for some cool effects

- `pu::ui::render::LoadImage` is now `pu::ui::render::LoadImageFromFile`, and a new `pu::ui::render::LoadImageFromBuffer` was added as a wrapper to load images directly from existing data/memory.

- Text rendering and clamping were properly done now, so that newlines still wrap the text (thus actually introduce a new line when rendering) and reaching the screensize no longer causes it to wrap (since this effect conflicted with the clamping system). 
