#include <stdio.h>
#include "analisador_lexico.h"

const char* nome_token(TAtomo tipo) {
    switch (tipo) {
        case TK_AND: return " é um AND";
        case TK_BEGIN: return " é um BEGIN";
        case TK_CHAR: return " é um CHAR";
        case TK_ELSE: return " é um ELSE";
        case TK_END: return " é um END";
        case TK_FLOAT: return " é um FLOAT";
        case TK_FOR: return " é um FOR";
        case TK_IF: return " é um IF";
        case TK_INT: return " é um INT";
        case TK_NOT: return " é um NOT";
        case TK_OR: return " é um OR";
        case TK_PRG: return " é um PRG";
        case TK_READ: return " é um READ";
        case TK_REPEAT: return " é um REPEAT";
        case TK_RETURN: return " é um RETURN";
        case TK_SUBROT: return " é um SUBROT";
        case TK_THEN: return " é um THEN";
        case TK_UNTIL: return " é um UNTIL";
        case TK_VAR: return " é um VAR";
        case TK_VOID: return " é um VOID";
        case TK_WHILE: return " é um WHILE";
        case TK_WRITE: return " é um WRITE";

        case TK_IDENT: return " é um IDENT";
        case TK_INT_CONST: return " é um INT_CONST";
        case TK_FLOAT_CONST: return " é um FLOAT_CONST";
        case TK_CHAR_CONST: return " é um CHAR_CONST";
        case TK_STRING_CONST: return " é um STRING_CONST";

        case TK_ASSIGN: return " é um ASSIGN";
        case TK_PLUS: return " é um PLUS";
        case TK_MINUS: return " é um MINUS";
        case TK_MUL: return " é um MUL";
        case TK_DIV: return " é um DIV";
        case TK_EQ: return " é um EQ";
        case TK_NEQ: return " é um NEQ";
        case TK_GT: return " é um GT";
        case TK_LT: return " é um LT";
        case TK_GTE: return " é um GTE";
        case TK_LTE: return " é um LTE";

        case TK_LPAREN: return " é um LPAREN";
        case TK_RPAREN: return " é um RPAREN";
        case TK_LBRACKET: return " é um LBRACKET";
        case TK_RBRACKET: return " é um RBRACKET";
        case TK_SEMI: return " é um SEMI";
        case TK_COMMA: return " é um COMMA";
        case TK_DOT: return " é um DOT";

        case TK_EOF: return " é um EOF";
        case TK_ERROR: return " é um ERROR";
        default: return " é um ???";
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
                printf(" --> %s", token.valor.str);
                break;
            case TK_INT_CONST:
                printf(" --> %d", token.valor.inteiro);
                break;
            case TK_FLOAT_CONST:
                printf(" --> %f", token.valor.real);
                break;
            case TK_CHAR_CONST:
                printf(" --> '%c'", token.valor.caractere);
                break;
            default:
                break;
        }

        printf("\n");
    } while (token.tipo != TK_EOF && token.tipo != TK_ERROR);

    fechar_arquivo();
    return 0;
}
