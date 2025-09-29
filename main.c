#include <stdio.h>
#include "analisador_lexico.c"

const char* nome_token(TAtomo tipo) {
    switch (tipo) {
        case TK_AND: return "AND";
        case TK_BEGIN: return "BEGIN";
        case TK_CHAR: return "CHAR";
        case TK_ELSE: return "ELSE";
        case TK_END: return "END";
        case TK_FLOAT: return "FLOAT";
        case TK_FOR: return "FOR";
        case TK_IF: return "IF";
        case TK_INT: return "INT";
        case TK_NOT: return "NOT";
        case TK_OR: return "OR";
        case TK_PRG: return "PRG";
        case TK_READ: return "READ";
        case TK_REPEAT: return "REPEAT";
        case TK_RETURN: return "RETURN";
        case TK_SUBROT: return "SUBROT";
        case TK_THEN: return "THEN";
        case TK_UNTIL: return "UNTIL";
        case TK_VAR: return "VAR";
        case TK_VOID: return "VOID";
        case TK_WHILE: return "WHILE";
        case TK_WRITE: return "WRITE";

        case TK_IDENT: return "IDENT";
        case TK_INT_CONST: return "INT_CONST";
        case TK_FLOAT_CONST: return "FLOAT_CONST";
        case TK_CHAR_CONST: return "CHAR_CONST";
        case TK_STRING_CONST: return "STRING_CONST";

        case TK_ASSIGN: return "ASSIGN";
        case TK_PLUS: return "PLUS";
        case TK_MINUS: return "MINUS";
        case TK_MUL: return "MUL";
        case TK_DIV: return "DIV";
        case TK_EQ: return "EQ";
        case TK_NEQ: return "NEQ";
        case TK_GT: return "GT";
        case TK_LT: return "LT";
        case TK_GTE: return "GTE";
        case TK_LTE: return "LTE";

        case TK_LPAREN: return "LPAREN";
        case TK_RPAREN: return "RPAREN";
        case TK_LBRACKET: return "LBRACKET";
        case TK_RBRACKET: return "RBRACKET";
        case TK_SEMI: return "SEMI";
        case TK_COMMA: return "COMMA";
        case TK_DOT: return "DOT";

        case TK_EOF: return "EOF";
        case TK_ERROR: return "ERROR";
        default: return "???";
    }
}

int main() {
    abrir_arquivo("exemplo.lpd");

    TInfoAtomo token;
    do {
        token = obter_atomo();
        printf("Linha %d: %-15s", token.linha, nome_token(token.tipo));

        switch (token.tipo) {
            case TK_IDENT:
            case TK_STRING_CONST:
                printf(" -> %s", token.valor.str);
                break;
            case TK_INT_CONST:
                printf(" -> %d", token.valor.inteiro);
                break;
            case TK_FLOAT_CONST:
                printf(" -> %f", token.valor.real);
                break;
            case TK_CHAR_CONST:
                printf(" -> '%c'", token.valor.caractere);
                break;
            default:
                break;
        }

        printf("\n");
    } while (token.tipo != TK_EOF && token.tipo != TK_ERROR);

    fechar_arquivo();
    return 0;
}
