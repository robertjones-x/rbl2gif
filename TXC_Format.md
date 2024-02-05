## TXC file format

The TXC file accompanies the RBL image file and the GIF thumbnail file to define a template in PRBLM.  All three files must have the same name, with the 
appropriate extension for the file type.  See the Readme.md file for information on creating the RBL file from a GIF and how to format the thumbnail GIF.

### Label Scaling
Template images come in various sizes, but it appears that during load, the vertical dimension is set to run from 0 to 3000 pixels with the horizontal
sized scaled from 0 to a value that maintains the aspect ratio of the image.  All labels are placed using this coordinate system.  In some cases the
top and left coordinates of labels can be negative, depending on the size of the font and length of text.  Labels with small negative values will still
be visible in the UI, but may not print correctly.

### File Format
|Line #| Value Format | Description |
|---|---|---|
|1|integer|template height (print height in mm)|
|2|integer|template width (print width in mm)|
|3|integer|text color [^1]|
|4|integer|background color [^1]|
|5-16|struct|label 1 formatting|
|5|integer|vertical start position [^2]|
|6|integer|horizontal start position [^2]|
|7|integer|label width in pixels [^3]|
|8|integer|label height in pixels [^3]|
|9|integer or float|font size (value from list of available sizes for selected font)|
|10|boolean|bold
|11|boolean|italics
|12|boolean|underline
|13|string|font name (value from list of installed fonts)|
|14|string|label text
|15|boolean|label is visible (the program expects this to be True for the first 5 labels)|
|16|integer|label justification(0=left, 2=center)
|17-28|struct|label 2 formatting, same as label 1|
|29-40|struct|label 3 formatting|
|41-52|struct|label 4 formatting|
|53-64|struct|label 5 formatting|
|65-76|struct|label 6 formatting|
|77-88|struct|label 7 formatting|
|89-100|struct|label 8 formatting|
|101|string|texture file name (files located in \bg directory)|
|102|list of booleans|8 boolean values that control horizontal centering of labels 1 - 8[^4]|
|103-115|struct|label 9 formatting|
|116|blank|trailing blank line [^5]|

[^1]: Text and background colors are a single integer that defines the three RGB color channels by taking the integer value of each channel, from 0 to 255 and using them
in the following formula (Red Channel Value * 1) + (Green Channel Value * 256) + (Blue Channel Value * 65536).  The program does not allow a black background color or white text color.
[^2]: Vertical start position is fixed as set in the TXC file, horizontal start postion will be recalculated when the font, font size, or label text is changed.
[^3]: Label height will recalculate when the font or font size is changed, Label width will recalculate when font, font size, or label text is changed.
[^4]: See the Aguila sample template for an example of non-centered labels.
[^5]: Signature file selection is not saved to the TXC file.
