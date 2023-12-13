Links: [[Colour Images]]
Tags:
___
# Colour Applications
## Skin Detection
Skin detection can be done with pixel analysis
(Saturation >= 0.2) AND (0.5 < Luminance/Saturation < 3.0) AND (Hue <= 28$\degree$ OR Hue >= 330$\degree$)
This is not an entirely accurate way to identify skin as it is quite crude.

## Red Eye Detection
(Luminance >= 0.25) AND (Saturation >= 0.25) AND (0.5 < Luminance/Saturation < 1.5) AND (Hue <= 14$\degree$ OR Hue >= 324$\degree$)
Good starting point for indentification of red-eye


___
Created: 2023-12-11

