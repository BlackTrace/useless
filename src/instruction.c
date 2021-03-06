#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "ops.h"
#include "vm.h"

#define ocode(o1, o2, o3, o4) ((o4 << 12) | (o3 << 8) | (o2 << 4) | o1)

// this file contains the code for all operations, when each operation
// is called the state of the cpu, the ram arr, and the operand type is
// passed in. the 16 bit operand type is a bit field representing what
// types of the operands the instruction is called with.
//
// TYPE BIT FIELD 
//  _______________ _______________ _______________ _______________     
// |               |               |               |               |
// | 0 | R | M | L | 0 | R | M | L | 0 | R | M | L | 0 | R | M | L |
// |_______________|_______________|_______________|_______________|
//     operand 1       operand 2       operand 3       operand 4
//
// L = literal   - this means we want to use the operand literally -> val
// M = memory    - this means we want to access ram at the operand -> ram[val]
// R = reference - this means we want to double access ram (deref) -> ram[ram[ind]]
//
// to convert the constants L, M, R to this format the ocode macro is used

int nop(cpu_t *cpu, int *ram, uint16_t type) {
    return 1;
}

int mv(cpu_t *cpu, int *ram, uint16_t type) {

    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] = val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] = ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] = ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] = val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] = ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] = ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

int vadd(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] += val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] += ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] += ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] += val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] += ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] += ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

int vsub(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] -= val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] -= ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] -= ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] -= val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] -= ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] -= ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

int vmul(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] *= val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] *= ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] *= ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] *= val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] *= ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] *= ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

int vdiv(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] /= val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] /= ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] /= ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] /= val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] /= ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] /= ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

int vmod(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] %= val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] %= ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] %= ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] %= val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] %= ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] %= ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

int eq(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] == val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] == ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] == ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] == val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] == ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] == ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int neq(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] != val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] != ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] != ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] != val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] != ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] != ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int lt(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] < val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] < ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] < ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] < val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] < ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] < ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int lte(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] <= val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] <= ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] <= ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] <= val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] <= ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] <= ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int gt(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] > val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] > ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] > ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] > val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] > ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] > ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int gte(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] >= val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] >= ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] >= ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] >= val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] >= ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] >= ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int hopt(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 
    if (!cpu->flg) return 1;

    switch (type) {
        case (ocode(L, 0, 0, 0)):
        case (ocode(M, 0, 0, 0)):
            cpu->pc = val - 1;
            break;

        case (ocode(R, 0, 0, 0)):
            cpu->pc = ram[val] - 1;
            break;

        
        default:
            return 0;
    }

    return 1;
}

int hopf(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 
    if (cpu->flg) return 1;

    switch (type) {
        case (ocode(L, 0, 0, 0)):
        case (ocode(M, 0, 0, 0)):
            cpu->pc = val - 1;
            break;

        case (ocode(R, 0, 0, 0)):
            cpu->pc = ram[val] - 1;
            break;

        
        default:
            return 0;
    }

    return 1;
}

int hop(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, 0, 0, 0)):
        case (ocode(M, 0, 0, 0)):
            cpu->pc = val - 1;
            break;

        case (ocode(R, 0, 0, 0)):
            cpu->pc = ram[val] - 1;
            break;

        
        default:
            return 0;
    }

    return 1;
}

int printn(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, 0, 0, 0)):
            printf("%d", val);
            break;

        case (ocode(M, 0, 0, 0)):
            printf("%d", ram[val]);
            break;

        case (ocode(R, 0, 0, 0)):
            printf("%d", ram[ram[val]]);
            break;
        
        default:
            return 0;
    }
    
    fflush(stdout);
    return 1;
}

int print(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, 0, 0, 0)):
            putchar(val);
            break;

        case (ocode(M, 0, 0, 0)):
            putchar(ram[val]);
            break;

        case (ocode(R, 0, 0, 0)):
            putchar(ram[ram[val]]);
            break;
        
        default:
            return 0;
    }

    fflush(stdout);

    return 1;
}

int push(cpu_t *cpu, int *ram, uint16_t type) {

    int val = ram[++cpu->pc]; 

    ram[SP] -= 1;

    switch (type) {
        case (ocode(L, 0, 0, 0)):
            ram[ram[SP]] = val;
            break;

        case (ocode(M, 0, 0, 0)):
            ram[ram[SP]] = ram[val];
            break;

        case (ocode(R, 0, 0, 0)):
            ram[ram[SP]] = ram[ram[val]];
            break;
        
        default:
            return 0;
    }
    
    return 1;
}

int pop(cpu_t *cpu, int *ram, uint16_t type) {

    int val = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, 0, 0, 0)):
            break; 

        case (ocode(M, 0, 0, 0)):
            ram[val] = ram[ram[SP]];
            break;

        case (ocode(R, 0, 0, 0)):
            ram[ram[val]] = ram[ram[SP]];
            break;
        
        default:
            return 0;
    }
    
    ram[SP] += 1;
    return 1;
}

int smv(cpu_t *cpu, int *ram, uint16_t type) {
    int off = ram[++cpu->pc]; 
    int loc = ram[++cpu->pc]; 
    int bp  = ram[BP] + 1;
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            break;

        case (ocode(M, M, 0, 0)):
            off = ram[off];
            break;

        case (ocode(R, M, 0, 0)):
            off = ram[ram[off]];
            break;
        
        case (ocode(L, R, 0, 0)):
            loc = ram[loc];
            break;

        case (ocode(M, R, 0, 0)):
            off = ram[off];
            loc = ram[loc];
            break;

        case (ocode(R, R, 0, 0)):
            off = ram[ram[off]];
            loc = ram[loc];
            break;

        default:
            return 0;
    }
    
    ram[loc] = ram[bp + off];

    return 1;
}

int call(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 

    ram[SP] -= 1;
    ram[ram[SP]] = cpu->pc + 1;

    ram[SP] -= 1;
    ram[ram[SP]] = ram[BP];

    ram[BP] = ram[SP];

    switch (type) {
        case (ocode(M, 0, 0, 0)):
            cpu->pc = val - 1;
            break;
        
        case (ocode(R, 0, 0, 0)):
            cpu->pc = ram[val] - 1;
            break;

        default:
            return 0;
    }

    return 1;
}

int ret(cpu_t *cpu, int *ram, uint16_t type) {
    int old_bp = ram[ram[BP]];
    int r_addr = ram[ram[BP] + 1];

    ram[SP] = ram[BP] + 2;
    ram[BP] = old_bp;

    cpu->pc = r_addr - 1;
    return 1;
}

int vexit(cpu_t *cpu, int *ram, uint16_t type) {
    return 0;
}
