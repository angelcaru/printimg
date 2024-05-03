# printimg
`printimg` is a set of command-line tools for manipulating images.

## Provided utilities
- `pim` prints images to the terminal in an ANSI-encoded fashion. It supports reading images from the filesystem or using piped image data.
- `rim` reads images from the filesystem and allows you to pipe them into another program.
- `wim` writes piped image data to the filesystem
- `istats` prints metadata of a piped image. Currently that is only the resolution

- `rect` draws a rectangle
- `circle` draws a circle
- `crop` crops an image

## Examples
`rim C_Logo.png | istats` <br>
Get resolution of `C_Logo.png`

`rim C_Logo.png | rect 100 100 100 100 #ff0000 | pim` <br>
Read `C_Logo.png`, draw a red 100-pixel square at coordinates (100, 100), and print it.

`rim C_Logo.png | rect 100 100 100 100 #ff0000 | wim out.png` <br>
Same as the above command, but writes the result to `out.png`. Note that no matter the file extension, it will be encoded in a PNG format. Also note that, although `pim` prints images in a reduced resolution, the manipulations are done at full scale, as can be observed by using a traditional image viewer.

## Compiling
```console
$ cc -o nob src/nob.c
$ ./nob
```

