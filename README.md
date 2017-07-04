make try this later
http://www.geeks3d.com/20101029/shader-library-pixelation-post-processing-effect-glsl/


ffmpeg -i babies.mp4 -vf scale=-2:384 -y babies384.mp4
for i in *.mp4; do ffmpeg -i "$i" -vf scale=384:-2 -y `basename "$i" .mp4`384.mp4 ; done

