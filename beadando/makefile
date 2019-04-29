all:
	gcc -Iinclude/ src/callbacks.c src/camera.c src/init.c src/main.c src/scene.c src/utils.c src/model.c src/draw.c -lSOIL -lglut32 -lopengl32 -lglu32 -lm -o cow.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/callbacks.c src/camera.c src/init.c src/main.c src/scene.c src/utils.c -lobj -lGL -lSOIL -lGLU -lglut -lm -o cow -Wall -Wextra -Wpedantic
