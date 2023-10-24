#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl;

int ex(nodeType *p)
{
    int lbl1, lbl2;

    if (!p)
        return 0;
    switch (p->type)
    {
    case typeCon:
        printf("\tmov\trax, %d\n", p->con.value);
        break;
    case typeId:
        printf("\tmov\trax, [rbp-%d]\n", (p->id.i + 1) * 4); // Assuming each variable occupies 4 bytes on the stack
        break;
    case typeOpr:
        switch (p->opr.oper)
        {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            printf("\ttest\trax, rax\n");
            printf("\tjz\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2)
            {
                /* if else */
                printf("\ttest\trax, rax\n");
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            }
            else
            {
                /* if */
                printf("\ttest\trax, rax\n");
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:
            ex(p->opr.op[0]);
            //move rax to rsi
            printf("\tmov\trsi, rax\n");
            printf("\tmov\trdi, 1\n"); // stdout file descriptor
            printf("\tmov\trsi, rsp\n"); // pointer to the string to be printed
            printf("\tmov\tdl, 4\n"); // length of the string to be printed
            printf("\tmov\trax, 0x2000004\n"); // write syscall number
            printf("\tsyscall\n"); // call the syscall
            printf("\tadd\trsp, 8\n"); // remove the string from the stack
            break;
        case '=':
            ex(p->opr.op[1]);
            printf("\tmov\t[rbp-%d], rax\n", (p->opr.op[0]->id.i + 1) * 4);
            break;
        case UMINUS:
            ex(p->opr.op[0]);
            printf("\tneg\trax\n");
            break;
        case FACT:
            ex(p->opr.op[0]);
            printf("\tcall\tfact\n"); // Assuming a factorial function exists
            break;
        case LNTWO:
            ex(p->opr.op[0]);
            printf("\tcall\tlntwo\n"); // Assuming a log base 2 function exists
            break;
        default:
            ex(p->opr.op[0]);
            printf("\tpush\trax\n");
            ex(p->opr.op[1]);
            printf("\tpop\trbx\n");
            switch (p->opr.oper)
            {
            case GCD:
                printf("\tcall\tgcd\n"); // Assuming a gcd function exists
                break;
            case '+':
                printf("\tadd\trax, rbx\n");
                break;
            case '-':
                printf("\tsub\trax, rbx\n");
                break;
            case '*':
                printf("\timul\trax, rbx\n");
                break;
            case '/':
                printf("\tidiv\trbx\n");
                break;
            case '<':
                printf("\tcmp\trax, rbx\n");
                printf("\tsetl\tal\n");
                printf("\tmovzx\trax, al\n");
                break;
            case '>':
                printf("\tcmp\trax, rbx\n");
                printf("\tsetg\tal\n");
                printf("\tmovzx\trax, al\n");
                break;
            case GE:
                printf("\tcmp\trax, rbx\n");
                printf("\tsetge\tal\n");
                printf("\tmovzx\trax, al\n");
                break;
            case LE:
                printf("\tcmp\trax, rbx\n");
                printf("\tsetle\tal\n");
                printf("\tmovzx\trax, al\n");
                break;
            case NE:
                printf("\tcmp\trax, rbx\n");
                printf("\tsetne\tal\n");
                printf("\tmovzx\trax, al\n");
                break;
            case EQ:
                printf("\tcmp\trax, rbx\n");
                printf("\tsete\tal\n");
                printf("\tmovzx\trax, al\n");
                break;
            }
        }
    }
    return 0;
}
