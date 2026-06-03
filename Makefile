all: build run

build:
	gcc ./TestHost/*.c ./RaySplitter/*.c -o "./TestHost/dev.exe" -lraylib -lgdi32 -lwinmm
	gcc ./TestScreen/*.c ./RaySplitter/*.c -o "./TestScreen/dev.exe" -lraylib -lgdi32 -lwinmm

run:
	TestHost/dev
