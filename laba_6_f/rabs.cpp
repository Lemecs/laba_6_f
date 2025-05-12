#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#define TASK_5

#ifdef TASK_1

#define MAX_LEN 1000

void findLongestWord(char* str, char* longestWord) {
    int maxLen = 0, currentLen = 0;
    int i = 0, start = 0, longestStart = 0;

    while (str[i] != '\0') {
        // Если текущий символ — буква
        if ((str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= 'a' && str[i] <= 'z')) {
            if (currentLen == 0) {
                start = i;  // начало слова
            }
            currentLen++;
        }
        else {
            // Конец слова
            if (currentLen > maxLen) {
                maxLen = currentLen;
                longestStart = start;
            }
            currentLen = 0;
        }
        i++;
    }

    // Проверка на случай, если строка заканчивается словом
    if (currentLen > maxLen) {
        maxLen = currentLen;
        longestStart = start;
    }

    // Копируем самое длинное слово в буфер
    for (i = 0; i < maxLen; i++) {
        longestWord[i] = str[longestStart + i];
    }
    longestWord[maxLen] = '\0'; // завершающий ноль
}

int main() {
    char* locale = setlocale(LC_ALL, "");
    char input[MAX_LEN];
    char longestWord[MAX_LEN];

    printf("Введите строку: ");
    fgets(input, MAX_LEN, stdin);

    findLongestWord(input, longestWord);
    printf("Самое длинное слово: %s\n", longestWord);

    return 0;
}
#endif // TASK_1

#ifdef TASK_2

#define MAX_LEN 1024

/**
 * count_words_len — подсчитать в строке s количество слов длины target_len
 * @param s           — входная строка (нулевой терминатор)
 * @param target_len  — искомая длина слова
 * @return            — количество слов длины target_len
 */
int count_words_len(const char* s, int target_len) {
    int count = 0;         // итоговый счётчик слов
    int curr_len = 0;      // длина текущего слова
    char c;

    // проходим по всей строке посимвольно
    while ((c = *s++) != '\0') {
        // если символ не разделитель — увеличиваем длину текущего слова
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            curr_len++;
        }
        else {
            // встретили разделитель: если предыдущее слово нужной длины — считаем
            if (curr_len == target_len) {
                count++;
            }
            curr_len = 0;  // начинаем новый "слово"
        }
    }

    // проверяем последнее слово (если строка не закончилась разделителем)
    if (curr_len == target_len) {
        count++;
    }

    return count;
}

int main() {
    char* locale = setlocale(LC_ALL, "");
    char buffer[MAX_LEN];
    int target;

    // ввод строки
    printf("Введите строку (не более %d символов):\n", MAX_LEN - 1);
    fgets(buffer, sizeof(buffer), stdin);
    // удаляем возможный символ '\n' в конце строки
    size_t len = 0;
    while (buffer[len] != '\0') {
        if (buffer[len] == '\n') {
            buffer[len] = '\0';
            break;
        }
        len++;
    }

    // ввод целевого размера
    printf("Введите необходимую длину слова (целое число):\n");
    scanf("%d", &target);


    // подсчёт и вывод результата
    int result = count_words_len(buffer, target);
    printf("В введённой строке слов длины %d: %d\n", target, result);

    return EXIT_SUCCESS;
}
#endif

#ifdef TASK_3
#define MAX_LEN 1024

/**
 * count_words_end_char — подсчитать в строке s количество слов,
 * оканчивающихся символом target_char
 * @param s           — входная строка (нулевой терминатор)
 * @param target_char — искомый конечный символ слова
 * @return            — количество слов, заканчивающихся target_char
 */
int count_words_end_char(const char* s, char target_char) {
    int count = 0;      // итоговый счётчик
    int curr_len = 0;   // длина текущего слова
    char last_char = '\0';
    char c;

    while ((c = *s++) != '\0') {
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            // внутри слова: обновляем длину и последний символ
            curr_len++;
            last_char = c;
        }
        else {
            // разделитель: если было слово и его последний символ совпадает
            if (curr_len > 0 && last_char == target_char) {
                count++;
            }
            curr_len = 0;
            last_char = '\0';
        }
    }
    // проверка последнего слова, если строка не закончилась разделителем
    if (curr_len > 0 && last_char == target_char) {
        count++;
    }
    return count;
}

int main(void) {
    char* locale = setlocale(LC_ALL, "");
    char buffer[MAX_LEN];
    char target;

    // ввод строки
    printf("Введите строку (максимум %d символов):\n", MAX_LEN - 1);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Ошибка ввода строки.\n");
        return EXIT_FAILURE;
    }
    // удаляем символ '\n' в конце, если есть
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
    }

    // ввод целевого символа
    printf("Введите символ, которым должны заканчиваться слова:\n");
    if (scanf(" %c", &target) != 1) {
        fprintf(stderr, "Ошибка ввода символа.\n");
        return EXIT_FAILURE;
    }

    int result = count_words_end_char(buffer, target);
    printf("В строке слов, оканчивающихся на '%c': %d\n", target, result);
    return EXIT_SUCCESS;
}

#endif

#ifdef TASK_4
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/**
 * my_strlen — вычисление длины строки, аналог strlen
 */
size_t my_strlen(const char* s) {
    const char* p = s;
    while (*p) p++;
    return (size_t)(p - s);
}

/**
 * match_at — проверяет, начинается ли в строке s подстрока needle
 * аналог strstr для точного совпадения с начала
 */
int match_at(const char* s, const char* needle, size_t needle_len) {
    size_t i;
    for (i = 0; i < needle_len; i++) {
        if (s[i] != needle[i]) return 0;
    }
    return 1;
}

/**
 * replace_child — заменить все вхождения "child" на "children" в строке s
 * @param s — входная строка
 * @return  — новая строка с заменами (нужно освободить вызовом free)
 */
char* replace_child(const char* s) {
    const char* needle = "child";
    const char* replacement = "children";
    size_t needle_len = my_strlen(needle);
    size_t repl_len = my_strlen(replacement);

    // подсчет вхождений
    size_t orig_len = my_strlen(s);
    size_t count = 0;
    size_t i = 0;
    while (i + needle_len <= orig_len) {
        if (match_at(s + i, needle, needle_len)) {
            count++;
            i += needle_len;
        }
        else {
            i++;
        }
    }

    // вычисляем размер новой строки
    size_t new_len = orig_len + count * (repl_len - needle_len);
    char* result = (char*)malloc(new_len + 1);
    if (!result) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }

    // построение новой строки
    size_t src_idx = 0, dst_idx = 0;
    while (src_idx < orig_len) {
        if (src_idx + needle_len <= orig_len &&
            match_at(s + src_idx, needle, needle_len)) {
            // копируем replacement
            for (size_t k = 0; k < repl_len; k++) {
                result[dst_idx++] = replacement[k];
            }
            src_idx += needle_len;
        }
        else {
            // копируем один символ
            result[dst_idx++] = s[src_idx++];
        }
    }
    result[dst_idx] = '\0';

    return result;
}

int main(void) {
    char* locale = setlocale(LC_ALL, "");

    const char* text = "The child plays with another child.";
    char* modified = replace_child(text);
    printf("Cтарая: %s\n", text);
    printf("Новая: %s\n", modified);
    free(modified);
    return 0;
}


#endif // TASK_4

#ifdef TASK_5
/**
 * my_strlen — вычисление длины строки, аналог strlen
 */
size_t my_strlen(const char* s) {
    const char* p = s;
    while (*p) p++;
    return (size_t)(p - s);
}

/**
 * int_to_str — конвертирует целое k в строку, возвращает указатель на static буфер
 */
const char* int_to_str(int k) {
    static char buf[32];
    snprintf(buf, sizeof(buf), "%d", k);
    return buf;
}

/**
 * compress_sequence — сжатие повторяющихся символов:
 * последовательности длины >1 заменяются на x(k)
 * @param s — входная строка
 * @return — новая строка с заменами (нужно free)
 */
char* compress_sequence(const char* s) {
    size_t orig_len = my_strlen(s);
    if (orig_len == 0) {
        char* empty = malloc(1);
        empty[0] = '\0';
        return empty;
    }

    // Предварительный подсчёт длины результирующей строки
    size_t new_len = 0;
    size_t i = 0;
    while (i < orig_len) {
        char c = s[i];
        size_t j = i + 1;
        while (j < orig_len && s[j] == c) j++;
        size_t run = j - i;
        if (run > 1) {
            const char* num = int_to_str((int)run);
            new_len += 1 + 1 + my_strlen(num) + 1; // c(k)
        }
        else {
            new_len += 1;
        }
        i = j;
    }

    char* result = malloc(new_len + 1);
    if (!result) { fprintf(stderr, "Ошибка выделения памяти\n"); exit(EXIT_FAILURE); }

    // Построение результирующей строки
    size_t dst = 0;
    i = 0;
    while (i < orig_len) {
        char c = s[i];
        size_t j = i + 1;
        while (j < orig_len && s[j] == c) j++;
        size_t run = j - i;
        if (run > 1) {
            result[dst++] = c;
            result[dst++] = '(';
            const char* num = int_to_str((int)run);
            for (size_t k = 0; num[k] != '\0'; k++) {
                result[dst++] = num[k];
            }
            result[dst++] = ')';
        }
        else {
            result[dst++] = c;
        }
        i = j;
    }
    result[dst] = '\0';
    return result;
}

int main(void) {
    char* locale = setlocale(LC_ALL, "");

    const char* text = "aaabbcdddddde";
    char* compressed = compress_sequence(text);
    printf("Input: %s\n", text);
    printf("Compressed: %s\n", compressed);
    free(compressed);
    return 0;
}
#endif // TASK_5
