#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
EBNF 문법:
expression = term {("+" | "-") term} ;
term = factor {("*" | "/") factor} ;
factor = number | "(" expression ")" ;
number = digit {digit} ;
digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
*/

//토큰 타입 정의
typedef enum
{
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
    TOKEN_ERROR,
} TokenType;

typedef struct
{
    TokenType type;//토큰의 타입
    int value;//숫자인 경우 그 값
} Token;

typedef struct
{
    const char *input;//입력 문자열
    int position;//현재 위치
    Token current_token;//현재 토큰
} Parser;

Token create_token(TokenType type, int value)
{
    Token token;

    token.type = type;
    token.value = value;
    return (token);
}

Token get_next_token(Parser *p)
{
    int value = 0;
    while (p->input[p->position] == ' ')
        p->position++;
    if (p->input[p->position] == '\0')
        return (create_token(TOKEN_END, 0));
    if (isdigit(p->input[p->position]))
    {
        while (isdigit(p->input[p->position]))
        {
            value = value * 10 + (p->input[p->position] - '0');
            p->position++;
        }
        return (create_token(TOKEN_NUMBER, value));
    }

    char current = p->input[p->position++];
    if (current == '+')
        return (create_token(TOKEN_PLUS, 0));
    else if (current == '-')
        return (create_token(TOKEN_MINUS, 0));
    else if (current == '*')
        return (create_token(TOKEN_MULTIPLY, 0));
    else if (current == '/')
        return (create_token(TOKEN_DIVIDE, 0));
    else if (current == '(')
        return (create_token(TOKEN_LPAREN, 0));
    else if (current == ')')
        return (create_token(TOKEN_RPAREN, 0));
    else
        return (create_token(TOKEN_ERROR, 0));
}

Parser *create_parser(const char *input)
{
    Parser *p;

    p = malloc(sizeof(Parser));
    p->input = input;
    p->position = 0;
    p->current_token = get_next_token(p);
    return (p);
}

void print_token(Token token)
{
    const char *type_names[] = {
        "NUMBER", "PLUS", "MINUS", "MULTIPLY",
        "DIVIDE", "LPAREN", "RPAREN", "END", "ERROR"
    };
    printf("Token { type: %s", type_names[token.type]);
    if(token.type == TOKEN_NUMBER)
        printf(", value: %d", token.value);
    printf("}\n");
}

//factor = number | "(" expression ")" ;
int parse_factor(Parser *p)
{
    Token token = p->current_token;
    int result;

    if (token.type == TOKEN_NUMBER)
    {
        result = token.value;
        p->current_token = get_next_token(p);
        return (result);
    }

    if (token.type == TOKEN_LPAREN)
    {
        p->current_token = get_next_token(p);
        result = parse_expression(p);
        if (p->current_token.type == TOKEN_RPAREN)
        {
            p->current_token = get_next_token(p);
            return (result);
        }
        return (result);
    }
    else
        {
            printf("Error: Expected closing parenthesis\n");
            exit(1);
        }
    
    printf("Error: Unexpected token\n");
    exit(1);
}

int parse_term(Parser *p)
{
    int result = parse_factor(p);
    int divisor = 0;
    Token token;

    while (p->current_token.type == TOKEN_MULTIPLY || p->current_token.type == TOKEN_DIVIDE)
    {
        token = p->current_token;
        p->current_token = get_next_token(p);
        if (token.type == TOKEN_MULTIPLY)
            result *= parse_factor(p);
        else
        {
            divisor = parse_factor(p);
            if (divisor != 0)
                result /= divisor;
            else
            {
                printf ("Error: Division by zero\n");
                exit(1);
            }
        }
    }
    return (result);
}

int parse_expression(Parser *p)
{
    int result = parse_term(p);

    while (p->current_token.type == TOKEN_PLUS || p->current_token.type == TOKEN_MINUS)
    {
        Token token = p->current_token;
        p->current_token = get_next_token(p);

        if (token.type == TOKEN_PLUS)
            result += parse_term(p);
        else
            result -= parse_term(p);
    }
    return (result);
}

int calculate(const char *input)
{
    Parser *p = create_parser(input);
    int result = parse_expression(p);

    if (p->current_token.type != TOKEN_END)
    {
        printf("Error: Unexpected characters at end of input\n");
        free(p);
        exit(1);
    }

    free(p);
    return (result);
}

void test_expression(const char *input)
{
    printf("\n Testing: %s\n", input);
    printf("Tokens:\n");

    Parser *p = create_parser(input);
    while (p->current_token.type != TOKEN_END && p->current_token.type != TOKEN_ERROR)
    {
        print_token(p->current_token);
        p->current_token = get_next_token(p);
    }

    printf("Result: %d\n", calculate(input));
    free(p);
}

int main()
{
    test_expression("3 + 4 * 2");
    test_expression("(3 + 4) * 2");
    test_expression("10 / 2 + 2");
    return (0);
}