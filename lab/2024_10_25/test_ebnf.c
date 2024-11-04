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


// 토큰 타입 정의
typedef enum {
    TOKEN_NUMBER,    // 숫자
    TOKEN_PLUS,      // +
    TOKEN_MINUS,     // -
    TOKEN_MULTIPLY,  // *
    TOKEN_DIVIDE,    // /
    TOKEN_LPAREN,    // (
    TOKEN_RPAREN,    // )
    TOKEN_END,       // 문자열 끝
    TOKEN_ERROR      // 에러
} TokenType;

// 토큰 구조체
typedef struct {
    TokenType type;  // 토큰의 타입
    int value;       // 숫자인 경우 그 값
} Token;

// 파서 구조체
typedef struct {
    const char* input;    // 입력 문자열
    int position;        // 현재 위치
    Token current_token; // 현재 토큰
} Parser;

// 새로운 토큰 생성
Token create_token(TokenType type, int value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

// 다음 토큰 읽기
Token get_next_token(Parser* p) {
    // 공백 건너뛰기
    while (p->input[p->position] == ' ') {
        p->position++;
    }

    // 입력 끝 체크
    if (p->input[p->position] == '\0') {
        return create_token(TOKEN_END, 0);
    }

    // 숫자 처리
    if (isdigit(p->input[p->position])) {
        int value = 0;
        while (isdigit(p->input[p->position])) {
            value = value * 10 + (p->input[p->position] - '0');
            p->position++;
        }
        return create_token(TOKEN_NUMBER, value);
    }

    // 연산자 처리
    char current = p->input[p->position++];
    switch (current) {
        case '+': return create_token(TOKEN_PLUS, 0);
        case '-': return create_token(TOKEN_MINUS, 0);
        case '*': return create_token(TOKEN_MULTIPLY, 0);
        case '/': return create_token(TOKEN_DIVIDE, 0);
        case '(': return create_token(TOKEN_LPAREN, 0);
        case ')': return create_token(TOKEN_RPAREN, 0);
        default:  return create_token(TOKEN_ERROR, 0);
    }
}

// 파서 초기화
Parser* create_parser(const char* input) {
    Parser* p = malloc(sizeof(Parser));
    p->input = input;
    p->position = 0;
    p->current_token = get_next_token(p);
    return p;
}

// 토큰 타입 출력 (디버깅용)
void print_token(Token token) {
    const char* type_names[] = {
        "NUMBER", "PLUS", "MINUS", "MULTIPLY", 
        "DIVIDE", "LPAREN", "RPAREN", "END", "ERROR"
    };
    printf("Token { type: %s", type_names[token.type]);
    if (token.type == TOKEN_NUMBER) {
        printf(", value: %d", token.value);
    }
    printf(" }\n");
}

// factor 파싱
int parse_factor(Parser* p) {
    Token token = p->current_token;
    int result;

    if (token.type == TOKEN_NUMBER) {
        result = token.value;
        p->current_token = get_next_token(p);
        return result;
    }
    
    if (token.type == TOKEN_LPAREN) {
        p->current_token = get_next_token(p);
        result = parse_expression(p);
        
        if (p->current_token.type == TOKEN_RPAREN) {
            p->current_token = get_next_token(p);
            return result;
        } else {
            printf("Error: Expected closing parenthesis\n");
            exit(1);
        }
    }

    printf("Error: Unexpected token\n");
    exit(1);
}

// term 파싱
int parse_term(Parser* p) {
    int result = parse_factor(p);
    
    while (p->current_token.type == TOKEN_MULTIPLY || 
           p->current_token.type == TOKEN_DIVIDE) {
        Token token = p->current_token;
        p->current_token = get_next_token(p);
        
        if (token.type == TOKEN_MULTIPLY) {
            result *= parse_factor(p);
        } else {
            int divisor = parse_factor(p);
            if (divisor != 0) {
                result /= divisor;
            } else {
                printf("Error: Division by zero\n");
                exit(1);
            }
        }
    }
    
    return result;
}

// expression 파싱
int parse_expression(Parser* p) {
    int result = parse_term(p);
    
    while (p->current_token.type == TOKEN_PLUS || 
           p->current_token.type == TOKEN_MINUS) {
        Token token = p->current_token;
        p->current_token = get_next_token(p);
        
        if (token.type == TOKEN_PLUS) {
            result += parse_term(p);
        } else {
            result -= parse_term(p);
        }
    }
    
    return result;
}

// 수식 계산
int calculate(const char* input) {
    Parser* p = create_parser(input);
    int result = parse_expression(p);
    
    if (p->current_token.type != TOKEN_END) {
        printf("Error: Unexpected characters at end of input\n");
        free(p);
        exit(1);
    }
    
    free(p);
    return result;
}

// 테스트 및 토큰 출력 함수
void test_expression(const char* input) {
    printf("\nTesting: %s\n", input);
    printf("Tokens:\n");
    
    Parser* p = create_parser(input);
    while (p->current_token.type != TOKEN_END && 
           p->current_token.type != TOKEN_ERROR) {
        print_token(p->current_token);
        p->current_token = get_next_token(p);
    }
    
    printf("Result: %d\n", calculate(input));
    free(p);
}

int main() {
    test_expression("3 + 4 * 2");
    test_expression("(3 + 4 * 2");
    test_expression("10 / 2 + 3");
    return 0;
}