#include "../../include/minishell.h"

char *replace_whitespace(const char *str) {
    size_t len = ft_strlen(str);
    char *result = ft_strdup(str);  // 원본 문자열 복사
    
    if (!result) return NULL;

    for (size_t i = 0; i < len; i++) {
        if (ft_isspace(result[i])) {  // 화이트 스페이스 문자인지 확인
            result[i] = ' ';       // 공백으로 치환
        }
    }
    return result;
}