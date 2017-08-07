#include <stdio.h>
#include <stdbool.h>
#include <mem.h>

#define MAX_LONG 1005
#define STACK_SIZE 501

char alphabet[29] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                     'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                     'u', 'v', 'w', 'x', 'y', 'z', '/', '<', '>'},
        stack[STACK_SIZE][STACK_SIZE], parsed_xml[STACK_SIZE][STACK_SIZE];

bool cmp(const char *a, const char *b) {
    for (int i = 0; i < strlen(a); ++i)
        if ((((i + 1) < strlen(b)) && (a[i] != b[i + 1])) || ((strlen(b) - strlen(a)) != 1))
            return false;
    return true;
}

bool checkSyntax(const char *xml, int len) {
    bool open_bracket = false, letters_exist = false;
    for (int i = 0; i < len; ++i) {
        if (!open_bracket) {
            open_bracket = xml[i] == '<';
            if (!open_bracket)
                return false;
            letters_exist = false;
        } else {
            if (xml[i] == '<')
                return false;
            else if (xml[i] == '>') {
                open_bracket = false;
                if (!letters_exist)
                    return false;
            } else if ((xml[i] == '/') && ((i - 1) >= 0) && (xml[i - 1] != '<'))
                return false;
             letters_exist = ((xml[i] <= 122) && (xml[i] >= 97));
        }
    }
    return true;
}

bool checkNames(int size_p) {
    int size_s = 0;
    if ((size_p % 2) != 0)
        return false;
    for (int i = 0; i < size_p; ++i) {
        if (parsed_xml[i][0] != '/')
            strcpy(stack[size_s++], parsed_xml[i]);
        else if ((size_s > 0) && (parsed_xml[i][0] == '/') && (cmp(stack[size_s - 1], parsed_xml[i])))
            size_s--;
        else
            return false;
    }
    if (size_s != 0)
        return false;
    return true;
}

int parse(const char *xml, int len) {
    int size_p = 0;
    bool open_bracket = false;
    for (int i = 0; i < len; ++i)
        if (!open_bracket)
            open_bracket = xml[i] == '<';
        else
            for (int j = i, k = 0; j < len; ++j, ++k)
                if (xml[j] != '>')
                    parsed_xml[size_p][k] = xml[j];
                else {
                    parsed_xml[size_p++][k] = '\0';
                    open_bracket = false;
                    break;
                }
    return size_p;
}

char xml[MAX_LONG], saved_letter;

int main() {
    freopen("xml.in", "r", stdin);  //xml.in  input.txt
    freopen("xml.out", "w", stdout);//xml.out output.txt

    gets(xml);
    int len = strlen(xml);
    for (int i = 0; i < len; ++i) {
        saved_letter = xml[i];
        for (int j = 0; j < 29; ++j) {
            xml[i] = alphabet[j];
            if ((checkSyntax(xml, len)) && (checkNames(parse(xml, len)))) {
                    printf("%s", xml);
                    return 0;
                }
        }
        xml[i] = saved_letter;
    }
}