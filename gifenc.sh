#!/bin/sh

palette="/tmp/palette.png"

filters="fps=30,scale=128:128:flags=lanczos"

ffmpeg -v info -i $1 -vf "$filters,palettegen" -y $palette
ffmpeg -v info -i $1 -i $palette -lavfi "$filters [x]; [x][1:v] paletteuse" -y $2
