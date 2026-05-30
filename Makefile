all: build run

build:
	gcc ./TestHost/*.c -o "./TestHost/dev.exe" -lraylib -lgdi32 -lwinmm
	gcc ./TestScreen/*.c -o "./TestScreen/dev.exe" -lraylib -lgdi32 -lwinmm

run:
	TestHost/dev
