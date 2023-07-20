#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Interpreter state
struct BFState {
  // The array and the size of the array.
  size_t array_len;
  uint8_t* array;

  // Pointer to the current position, points into array..array+array_len.
  uint8_t* cur;
};

int brainfuck(struct BFState* state, const char* program) {
    int loopCounter = 0;
    const char* start = program;
    while(*start != 0 && state->cur<state->array+state->array_len && state->cur>=state->array ){
        switch (*start) {
            case '+':++*(state->cur);
                start++;
                break;
            case '-': --*(state->cur);
                start++;
                break;
            case '>':
                if(state->cur==state->array+state->array_len-1){
                    return -1;
                }
                (state ->cur)++;

                start++;
                break;
            case '<':
                if(state->cur==state->array){
                    return -1;
                }
                (state->cur)--;
                start++;
                break;
            case '[':
                if(*(state->cur) != 0){
                    start++;
                    break;
                }
                loopCounter = 1;
                start++;
                while(loopCounter !=0 && *start != 0){
                    if(*start=='['){
                        loopCounter++;
                    }else if(*start == ']'){
                        loopCounter--;
                    }
                    start++;
                }
            if(*start!=0){
                start--;
            }
                break;
            case ']':
                if(*(state->cur) == 0){
                    start++;
                    break;
                }

                    loopCounter = -1;

                if(start == program){
                    return -1;
                }
                start--;
                while( loopCounter !=0&& start >= program ){
                    if(*start == '['){
                        loopCounter++;
                    }else if(*start == ']'){
                        loopCounter--;
                    }
                    start--;
                }
                start++;
                break;
            default:
                start++;
                break;
        }
    }
    if(*start != 0 || loopCounter != 0 ) {
        return -1;
    }
    return 0;
}