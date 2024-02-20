
#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"
#include <string.h>
#define MAX_REGISTERS 5
#define STRING_BUFFER_LENGTH 20
static int lbl;

int registersInitialized = 0;

int registerId = 11;
void printTabs(int indentLevel)
{
    for (int i = 0; i < indentLevel; i++)
    {
        printf("\t");
    }
}

struct asciiToReg
{
    int registerId;
    int asciiValue;
};

struct asciiToReg asciiToRegArray[MAX_REGISTERS];

void initializeRegisters()
{
    for (int i = 0; i < MAX_REGISTERS; i++)
    {
        asciiToRegArray[i].registerId = i + registerId;
        asciiToRegArray[i].asciiValue = -1;
    }
}

int getVariableRegister(int asciiCode)
{
    for (int i = 0; i < 5; i++)
    {
        if (asciiToRegArray[i].asciiValue == asciiCode)
        {
            return asciiToRegArray[i].registerId;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (asciiToRegArray[i].asciiValue == -1)
        {
            asciiToRegArray[i].asciiValue = asciiCode;
            return asciiToRegArray[i].registerId;
        }
    }
    return -1;
}

void operandToValue(char *outString, struct nodeTypeTag *opernad)
{

    if (opernad->type == typeId)
    {
        int regId = getVariableRegister(opernad->id.i + 'a');
        // set first to %r regId
        char regIdStr[12];
        sprintf(regIdStr, "  %d", regId);
        regIdStr[0] = '%';
        regIdStr[1] = 'r';
        strcpy(outString, regIdStr);
    }
    else if (opernad->type == typeCon)
    {
        char valueStr[12];
        sprintf(valueStr, "$%d", opernad->con.value);
        strcpy(outString, valueStr);
    }
    else
    {
        strcpy(outString, "%r10");
    }
}

int ex(nodeType *p)
{
    int lbl1, lbl2;
    if (!p)
        return 0;

    if (registersInitialized == 0)
    {
        initializeRegisters();
        registersInitialized = 1;
    }

    switch (p->type)
    {
        char first[STRING_BUFFER_LENGTH];
        char last[STRING_BUFFER_LENGTH];
        char saveTo[STRING_BUFFER_LENGTH];
    // type constant
    case typeCon:
        // print p->con.value type and  id as assembly comments
        break;
    case typeId:
        // print p->id.i type and  id as assembly comments
        break;
    case typeOpr:
        switch (p->opr.oper)
        {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            switch (p->opr.op[0]->id.i)
            {
            case GE:
                printf("\tjl\tL%03d\n", lbl2 = lbl++);
                break;
            case LE:
                printf("\tjg\tL%03d\n", lbl2 = lbl++);
                break;
            case 60: // smaller
                printf("\tjge\tL%03d\n", lbl2 = lbl++);
                break;
            case 62: // greater
                printf("\tjle\tL%03d\n", lbl2 = lbl++);
                break;
            case EQ:
                printf("\tjne\tL%03d\n", lbl2 = lbl++);
                break;
            case NE:
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                break;
            default:
                break;
            }
            // printf("\tjz\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);

            if (p->opr.nops > 2)
            {
                /* if else */
                switch (p->opr.op[0]->id.i)
                {

                case GE:
                    printf("\tjl\tL%03d\n", lbl1 = lbl++);
                    break;
                case LE:
                    printf("\tjg\tL%03d\n", lbl1 = lbl++);
                    break;
                case 60: // smaller
                    printf("\tjge\tL%03d\n", lbl1 = lbl++);
                    break;
                case 62: // greater
                    printf("\tjle\tL%03d\n", lbl1 = lbl++);
                    break;
                case EQ:
                    printf("\tjnz\tL%03d\n", lbl1 = lbl++);
                    break;
                case NE:
                    printf("\tjz\tL%03d\n", lbl1 = lbl++);
                    break;
                default:
                    break;
                }
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            }
            else
            {
                /* if */
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:

            ex(p->opr.op[0]);
            char reg[STRING_BUFFER_LENGTH];
            operandToValue(reg, p->opr.op[0]);
            printf("\tpush %s\n", reg);
            printf("\tmovq  %s, %%rsi \n", reg);
            printf("\tlea format(%%rip), %%rdi\n");
            printf("\txor  %%eax,%%eax\n");
            printf("\tcall printf\n");
            printf("\tpop %s\n", reg);
            break;
        case '=':
            ex(p->opr.op[1]); // Evaluate the right operand
            operandToValue(saveTo, p->opr.op[0]);
            if (p->opr.op[1]->type == typeOpr)
            {
                printf("\tmovq %%r10, %s\n", saveTo);
            }
            else
            {
                operandToValue(first, p->opr.op[1]);
                printf("\tmovq %s, %s\n", first, saveTo);
            }
            break;
        case UMINUS:
            char first[STRING_BUFFER_LENGTH] = "";
            operandToValue(first, p->opr.op[0]);
            printf("\tmovq %s, %%r8\n", first);
            printf("\tneg %%r8\n");
            printf("\tmovq %%r8, %%r10\n");
            break;
        case FACT:
            lbl1 = lbl++;
            lbl2 = lbl++;
            operandToValue(first, p->opr.op[0]);
            printf("\tmovq %s, %%rcx\n", first);
            printf("\tmovq $1, %%rax\n");
            printf("L%03d:\n", lbl1);
            printf("\tcmpq $1, %%rcx\n");
            printf("\tjle\tL%03d\n", lbl2);
            printf("\timulq %%rcx, %%rax\n");
            printf("\tdecq %%rcx\n");
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            printf("\tmovq %%rax, %%r10\n");
            break;
        case LNTWO:
            ex(p->opr.op[0]);
            printf("\tlntwo\n");
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch (p->opr.oper)
            {
            case GCD:
                printf("\tgcd\n");
                break;

            case '+':
                char firstadd[STRING_BUFFER_LENGTH] = "";
                char lastadd[STRING_BUFFER_LENGTH] = "";
                operandToValue(firstadd, p->opr.op[0]);
                operandToValue(lastadd, p->opr.op[1]);
                printf("\tadd %s, %s\n", firstadd, lastadd);
                break;
            case '-':
                char firstsub[STRING_BUFFER_LENGTH] = "";
                char lastsub[STRING_BUFFER_LENGTH] = "";
                operandToValue(firstsub, p->opr.op[0]);
                operandToValue(lastsub, p->opr.op[1]);
                printf("\tsubq %s, %s\n", lastsub, firstsub);
                printf("\tmovq %s, %%r10\n", firstsub);
                break;
            case '*':
                char firstmulti[STRING_BUFFER_LENGTH] = "";
                char lastmulti[STRING_BUFFER_LENGTH] = "";
                operandToValue(firstmulti, p->opr.op[0]);
                operandToValue(lastmulti, p->opr.op[1]);
                printf("\timul %s, %s\n", lastmulti, firstmulti);
                printf("\tmovq %s, %%r10\n", firstmulti);

                break;
            case '/':
                char firstDiv[STRING_BUFFER_LENGTH] = "";
                char lastDiv[STRING_BUFFER_LENGTH] = "";
                printf("\tmovq $0, %%rdx \n");
                operandToValue(firstDiv, p->opr.op[0]);
                operandToValue(lastDiv, p->opr.op[1]);
                if (p->opr.op[0]->type == typeCon)
                {
                    printf("\tmovq %s, %%rcx\n", firstDiv);
                    // set firstDiv to %rcx
                    firstDiv[0] = '%';
                    firstDiv[1] = 'r';
                    firstDiv[2] = 'c';
                    firstDiv[3] = 'x';
                    firstDiv[4] = '\0';
                }
                if (p->opr.op[1]->type == typeCon)
                {
                    printf("\tmovq %s, %%rbx\n", lastDiv);

                    lastDiv[0] = '%';
                    lastDiv[1] = 'r';
                    lastDiv[2] = 'b';
                    lastDiv[3] = 'x';
                    lastDiv[4] = '\0';
                }

                printf("\tmovq %s, %%rax\n", firstDiv);
                printf("\tidivq %s\n", lastDiv);
                printf("\tmovq %%rax, %%r10\n");
                break;

            case '<':
            case '>':
            case LE:
            case GE:
            
            case NE:
            case EQ:
                char firstG[STRING_BUFFER_LENGTH] = "";
                char lastG[STRING_BUFFER_LENGTH] = "";
                operandToValue(firstG, p->opr.op[0]);
                operandToValue(lastG, p->opr.op[1]);
                printf("\tcmp %s, %s\n", lastG, firstG);
                break;
            }
        }
    }
    return 0;
}
