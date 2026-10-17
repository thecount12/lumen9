/* lumen9 - main.c loop architecture blueprint */
#include "flux9.h"
#include "tokenizer.h"
#include "loader.h"

int main(int argc, char **argv) {
    /* Phase 1: Direct Memory Initialization */
    ModelWeights weights = lumen9_load_weights("model.bin");
    Tokenizer tok = lumen9_load_tokenizer("vocab.tok");
    
    /* Allocate the unified flux9 execution arena */
    Flux9VM vm;
    flux9_init_arena(&vm, 64 * 1024); /* Clean 64KiB cache lines */
    
    uint16_t current_token = tok.start_token;
    
    printf("lumen9 boot sequence complete. Generating:\n");
    
    /* Phase 2: The Autoregressive Inference Loop */
    while (current_token != tok.end_token) {
        
        /* 1. Embed the token into flux9 input regions */
        lumen9_embed_into_arena(&vm, current_token, &weights);
        
        /* 2. Run the compiled flux9 bytecode layers */
        flux9_run(&vm); 
        
        /* 3. Sample the next token directly from the output matrix register (T0) */
        current_token = lumen9_sample_argmax(&vm.registers[0]);
        
        /* 4. Stream the text character directly to stdout */
        printf("%s", tok.strings[current_token]);
        fflush(stdout);
    }
    
    return 0;
}


