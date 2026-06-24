# Plasma Shader Animation with CPP

This is a modification of the code posted by [@tsoding](https://x.com/tsoding) at https://x.com/tsoding/status/1989446257882829223

The original gist code can be downloaded from https://gist.github.com/rexim/ef86bf70918034a5a57881456c0a0ccf

## Compliling and Running

First intall SDL3 & SDL2 by running:

```shell
brew install sdl3
brew install sdl2
```

To compile use the following command (also included in the `compile.sh` script):

```shell
clang -O3 sdl2-shader.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lm -o shader
clang -O3 sdl3-shader.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL3 -lm -o sdl3-shader
```
