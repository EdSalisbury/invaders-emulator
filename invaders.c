//
// Created by Ed Salisbury on 3/26/20.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct condition_codes
{
    uint8_t z:1;
    uint8_t s:1;
    uint8_t p:1;
    uint8_t cy:1;
    uint8_t ac:1;
    uint8_t pad:3;
} condition_codes;

typedef struct state8080
{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    uint8_t *memory;
    struct condition_codes cc;
    uint8_t int_enable;
} state8080;

void unimplemented(state8080* state)
{
    printf("Error: Unimplemented instruction\n");
    exit(1);
}

int emulate8080(state8080* state)
{
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        default:
            unimplemented(state);
            break;
    }
    state->pc+=1;
}

int main(int argc, char **argv) {
    unsigned char *buffer;
    long filesize = 0;
    long ptr = 0;

    char* filename = "roms/invaders";
    FILE *in = fopen(filename, "rb");
    if (in == NULL) {
        printf("Error: Could not open file %s", filename);
        return (2);
    }

    fseek(in, 0L, SEEK_END);
    filesize = ftell(in);
    rewind(in);

    buffer = (unsigned char *) malloc(filesize + 1);
    fread(buffer, sizeof(unsigned char), filesize, in);
    fclose(in);

    while (ptr < filesize) {
        emulate8080(buffer[ptr]);
        ptr++;
    }

    free(buffer);
    return 0;
}