#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

typedef enum {
    // Palavras reservadas
    TK_AND, TK_BEGIN, TK_CHAR, TK_ELSE, TK_END, TK_FLOAT, TK_FOR,
    TK_IF, TK_INT, TK_NOT, TK_OR, TK_PRG, TK_READ, TK_REPEAT,
    TK_RETURN, TK_SUBROT, TK_THEN, TK_UNTIL, TK_VAR, TK_VOID,
    TK_WHILE, TK_WRITE,

    // Identificadores e constantes
    TK_IDENT, TK_INT_CONST, TK_FLOAT_CONST, TK_CHAR_CONST, TK_STRING_CONST,

    // Operadores
    TK_ASSIGN,   // <-
    TK_PLUS,     // +
    TK_MINUS,    // -
    TK_MUL,      // *
    TK_DIV,      // /
    TK_EQ,       // ==
    TK_NEQ,      // !=
    TK_GT,       // >
    TK_LT,       // <
    TK_GTE,      // >=
    TK_LTE,      // <=

    // Delimitadores
    TK_LPAREN,   // (
    TK_RPAREN,   // )
    TK_LBRACKET, // [
    TK_RBRACKET, // ]
    TK_SEMI,     // ;
    TK_COMMA,    // ,
    TK_DOT,      // .
    TK_LBRACE,   // {
    TK_RBRACE,   // }

    // Fim de arquivo e erros
    TK_EOF,
    TK_ERROR
} TAtomo;

typedef union {
    char str[256];   // para strings e identificadores
    int inteiro;     // para constantes inteiras
    float real;      // para constantes reais
    char caractere;  // para constantes char
} TLexema;

typedef struct {
    TAtomo tipo;
    TLexema valor;
    int linha;
} TInfoAtomo;


void abrir_arquivo(const char *nome);
void fechar_arquivo(void);
TInfoAtomo obter_atomo(void);

#endif
