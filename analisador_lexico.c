#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "analisador_lexico.h"

static FILE *fonte;
static int linha = 1;

void abrir_arquivo(const char *nome) {
    fonte = fopen(nome, "r");
    if(!fonte) {
        perror("Erro ao abrir arquivo fonte");
        exit(1);
    }
}

void fechar_arquivo() {
    if(fonte) fclose(fonte);
}

int proximo_char() {
    int c = fgetc(fonte);
    if(c == '\n') linha++;
    return c;
}

void retroceder_char(int c) {
    if(c != EOF) {
        ungetc(c, fonte);
        if(c == '\n') linha--;
    }
}

int palavra_reservada(const char *lexema, TAtomo *tipo) {
    struct { const char *palavra; TAtomo token; } tabela[] = {
        {"and", TK_AND}, {"begin", TK_BEGIN}, {"char", TK_CHAR}, {"else", TK_ELSE},
        {"end", TK_END}, {"float", TK_FLOAT}, {"for", TK_FOR}, {"if", TK_IF},
        {"int", TK_INT}, {"not", TK_NOT}, {"or", TK_OR}, {"prg", TK_PRG},
        {"read", TK_READ}, {"repeat", TK_REPEAT}, {"return", TK_RETURN},
        {"subrot", TK_SUBROT}, {"then", TK_THEN}, {"until", TK_UNTIL},
        {"var", TK_VAR}, {"void", TK_VOID}, {"while", TK_WHILE}, {"write", TK_WRITE}
    };

    for(int i = 0; i < sizeof(tabela)/sizeof(tabela[0]); i++) {
        if(strcmp(lexema, tabela[i].palavra) == 0) {
            *tipo = tabela[i].token;
            return 1;
        }
    }
    return 0;
}

TInfoAtomo obter_atomo(void) {
    TInfoAtomo atomo;
    atomo.tipo = TK_ERROR;

    int c;

    // Para ignorar espaços e comentários
    while((c = proximo_char()) != EOF) {
        if(c == ' ' || c == '\n' || c == '\t'){
            continue;
        }

        if(c == '{') {
            while((c = proximo_char()) != EOF && c != '}'){
                continue;
            }
        }
        break;
    }

    atomo.linha = linha;

    if(c == EOF) {
        atomo.tipo = TK_EOF;
        return atomo;
    }

    // Identificadores ou palavras reservadas
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
        char palavra[256];
        int i = 0;
        palavra[i++] = c;
        while((c = proximo_char()),((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' )){
            palavra[i++] = c;
        }
        palavra[i] = '\0';
        retroceder_char(c);

        if(palavra_reservada(palavra, &atomo.tipo)) {
            return atomo;
        } else {
            atomo.tipo = TK_IDENT;
            strcpy(atomo.valor.str, palavra);
            return atomo;
        }
    }

    // Números
    if(isdigit(c)) {
        char num[256];
        int i = 0;
        int Float = 0;
        num[i++] = c;
        while((c = proximo_char()),(isdigit(c) || c == '.')) {
            if(c == '.') Float = 1;
            num[i++] = c;
        }
        num[i] = '\0';
        retroceder_char(c);

        if(Float) {
            atomo.tipo = TK_FLOAT_CONST;
            atomo.valor.real = atof(num);
        } else {
            atomo.tipo = TK_INT_CONST;
            atomo.valor.inteiro = atoi(num);
        }
        return atomo;
    }

    // Strings
    if(c == '"') {
        char buffer[256];
        int i = 0;
        while((c = proximo_char()) != '"' && c != EOF) {
            buffer[i++] = c;
        }
        buffer[i] = '\0';
        atomo.tipo = TK_STRING_CONST;
        strcpy(atomo.valor.str, buffer);
        return atomo;
    }

    // Caracteres
    if(c == '\'') {
        c = proximo_char();
        atomo.tipo = TK_CHAR_CONST;
        atomo.valor.caractere = c;
        proximo_char();
        return atomo;
    }

    if(c == '<') {
        int c2 = proximo_char();
        if(c2 == '-'){
            atomo.tipo = TK_ASSIGN;
            return atomo;
        }
        if(c2 == '='){
            atomo.tipo = TK_LTE;
            return atomo;
        }

        retroceder_char(c2);
        atomo.tipo = TK_LT; return atomo;
    }

    if(c == '>') {
        int c2 = proximo_char();
        if(c2 == '='){
            atomo.tipo = TK_GTE;
            return atomo;
        }
        retroceder_char(c2);
        atomo.tipo = TK_GT;
        return atomo;
    }

    if(c == '=') {
        int c2 = proximo_char();
        if(c2 == '='){
            atomo.tipo = TK_EQ;
            return atomo;
        }
        retroceder_char(c2);
    }
    
    if(c == '!') {
        int c2 = proximo_char();
        if(c2 == '='){
            atomo.tipo = TK_NEQ;
            return atomo;
        }
        retroceder_char(c2);
    }

    
    switch(c) {
        case '+': atomo.tipo = TK_PLUS; break;
        case '-': atomo.tipo = TK_MINUS; break;
        case '*': atomo.tipo = TK_MUL; break;
        case '/': atomo.tipo = TK_DIV; break;
        case ';': atomo.tipo = TK_SEMI; break;
        case ',': atomo.tipo = TK_COMMA; break;
        case '.': atomo.tipo = TK_DOT; break;
        case '(': atomo.tipo = TK_LPAREN; break;
        case ')': atomo.tipo = TK_RPAREN; break;
        case '[': atomo.tipo = TK_LBRACKET; break;
        case ']': atomo.tipo = TK_RBRACKET; break;
        default: atomo.tipo = TK_ERROR; break;
    }

    return atomo;
}
