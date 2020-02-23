# catimage

Cat images to the terminal using ANSI escape sequences.

![catimage 2](https://user-images.githubusercontent.com/6997990/75120575-5eded880-5695-11ea-9017-56872cde6105.png)

## Usage

**catimage** prints the images of the files provided as arguments (or from stdin if none is provided). The ANSI escape sequences for 24-bit color are used in combonation with the half block character to simulate square pixels. The image is scalled down to fit into the terminal size. 

### Options

- `-n`: scale down by image by nearest neighbor (less smooth image)
- `-f`: fit image only by width
- `-s`: show images one by one (press enter to continue)
- `-i`: ignore missing or unsupported files
- `-w INTEGER`, `-h INTEGER`: set the max width or height

![catimage 1](https://user-images.githubusercontent.com/6997990/75120574-5dadab80-5695-11ea-9292-105bece8cd0b.png)

## Install

```
git clone https://github.com/MaanooAk/catimage.git
cd catimage
sudo make install
```

Build dependencies: `make`, `gcc`, `wget`, `xxd`
