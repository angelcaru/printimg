# printimg
`printimg` is a set of command-line tools for manipulating images.

## Provided utilities
- `pim` prints images to the terminal in an ANSI-encoded fashion. It supports reading images from the filesystem or using piped image data.
- `kpim` prints images to the terminal using the [Kitty Graphics Protocol](https://sw.kovidgoyal.net/kitty/graphics-protocol/). It supports reading images from the filesystem or using piped image data.
- `rim` reads images from the filesystem and allows you to pipe them into another program.
- `wim` writes piped image data to the filesystem
- `istats` prints metadata of a piped image. Currently that is only the resolution

- `blank` creates a new image with a specified resolution and, optionally, a background color.

- `rect` draws a rectangle
- `line` draws a line
- `circle` draws a circle
- `crop` crops an image
- `resz` resizes an image
- `iover`: overlay an image on top of another one: `rim C_Logo.png | iover 100 100 100 100 grass.png | pim`
- `imul`: multiply two images (aka apply a mask): `rim C_Logo.png | imul mask.png | pim`
  - If you want to generate a mask also using printimg you can use `wim -`: `rim C_Logo.png | imul <(blank 860 1008 '#ff0000' | circle 200 200 200 '#ffffff' | wim -) | pim`

## Examples
`blank 400 400 #ff0000 | rect 100 100 100 100 #00ff00 | pim` <br>
Create a 400x400 image filled with red, with a green rectangle at (100, 100)

`istats C_Logo.png` <br>
`rim C_Logo.png | istats` <br>
Get resolution of `C_Logo.png`

`rim C_Logo.png | rect 100 100 100 100 #ff0000 | pim` <br>
Read `C_Logo.png`, draw a red 100-pixel square at coordinates (100, 100), and print it.

`rim C_Logo.png | rect 100 100 100 100 #ff0000 | wim out.png` <br>
Same as the above command, but writes the result to `out.png`. Note that no matter the file extension, it will be encoded in a PNG format. Also note that, although `pim` prints images in a reduced resolution, the manipulations are done at full scale, as can be observed by using a traditional image viewer. If you don't want to lose resolution and your terminal supports the Kitty Graphics Protocol, you can use `kpim` instead of `pim`

## Compiling
```console
$ cc -o nob nob.c
$ ./nob --parallelize
```

