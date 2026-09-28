Student numbers and Names:
Ruben van der Vyver 25007786
Ronin Sydney 25056507
Mohammed Lutchka 25588304

## Prerequisites
| Tool | Minimum version |
| Docker Desktop (or Docker Engine + CLI) | 24.x |
| Docker Compose v2 plugin (`docker compose`) | 2.x |
No local C++ compiler is needed – everything is built inside Docker.

## Build and run(Docker)
From the repository root:
```bash
docker compose up --build
```
This single command:
1. Builds the image from the `Dockerfile` (compiles the code with `make`, `-std=c++11`).
2. Creates and starts the `campusguard` container.
3. Streams the application output to your terminal.
4. Exits when the simulation finishes.
Clean up afterwards:
```bash
docker compose down
```
To force a completely fresh build
```bash
docker compose down --rmi local
docker compose up --build
```
The image can also be built on its own with `docker build -t campusguard .`.
---
## Valgrind and GDB (inside Docker)
The `debug` service uses an image that contains the `-g` build of the
executable plus Valgrind and GDB.
**Valgrind (memory errors and leaks):**
```bash
docker compose run --rm debug valgrind --leak-check=full --show-leak-kinds=all ./campusguard
```
**GDB (interactive debugging):**
```bash
docker compose run --rm debug gdb ./campusguard
```
**Open a shell in the debug container:**
```bash
docker compose run --rm debug bash
```
## Building and running locally (without Docker)
If you have `g++` with C++11 support installed:
```bash
make
./campusguard
make clean
```
Doc link will go here:
https://docs.google.com/document/d/1FBif-YWDJR6rnpdB8hDAH7-27kXObTOEc7LOSh8vBCQ/edit?usp=sharing
