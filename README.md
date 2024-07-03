`git clone --recursive git@github.com:kubaau/dizidler.git`

## Requires

### Windows

- [boost](https://www.boost.org/users/download/)
- [DOSBox](https://www.dosbox.com/download.php?main=1)
- [GLEW](https://glew.sourceforge.net/)
- [SDL2](https://github.com/libsdl-org/SDL/releases)
- [SDL2_image](https://github.com/libsdl-org/SDL_image/releases)
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases)

### Ubuntu

`sudo apt install dosbox libboost-dev libglew-dev libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev`

### The Settlers 2 Gold Edition game files

Run `cpassets.sh` from the `assets` folder, passing paths to your S2 folder and DOSBox exe. e.g.

```
cd assets
./cpassets.sh ~/S2 dosbox # Ubuntu
./cpassets.sh /c/S2 "/c/Program Files (x86)/DOSBox-0.74-3/DOSBox.exe" # Windows
```
