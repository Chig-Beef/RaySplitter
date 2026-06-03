# Ray Splitter
Ray Splitter allows the use of multiple screens.
You, the programmer, only write one program.
Ray Splitter handles the multi-process code.
Interfaces on top of [raylib](https://github.com/raysan5/raylib).

## How It Works
Each time you create a new screen, Ray Splitter starts a new process.
That new process starts a raylib window, waiting for commands.
When you run a drawing function in the main program, it is stored in a queue.
Once the frame is finished, a function is called to flush the queues of each screen.
Each screen runs through the queue, converting each command given into a text format.
This text is sent to the specific sub-process via stdin.
The sub-process parses the text to determine the correct function to run.
The sub-process draws to its window.

## Current Drawbacks
No input capturing from any windows.

## Coverage
### rcore
5 out of 214 funcs have been implemented.
2.34% coverage.

### rshapes
42 out of 69 funcs have been implemented.
60.87% coverage.

### rtextures
2 out of 115 funcs have been implemented.
1.74% coverage.

### rtext
3 out of 59 funcs have been implemented.
5.08% coverage.

### rmodels
0 out of 74 funcs have been implemented.
0.00% coverage.

### raudio
0 out of 66 funcs have been implemented.
0.00% coverage.

### total
52 out of 597 funcs have been implemented.
8.71% coverage.
