all: main 
main: main.c
    compile:
        gcc main.c -o main
clean: 
    rm main
