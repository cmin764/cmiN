#include <cstdio>
#include <cstring>
#include <cctype>

char buffer[128], output[128];

int identify()
{
    bool java, cpp;
    java = cpp = 0;
    if (buffer[0] == '_' || buffer[strlen(buffer) - 1] == '_' || isupper(buffer[0])) {
        return 3;
    }
    for (char* pch = buffer; *pch && !(java && cpp); pch++) {
        if (*pch == '_') {
            cpp = 1;
        } else if (isupper(*pch)) {
            java = 1;
        }
    }
    if (java && cpp) {
        return 3;
    } else if (java) {
        return 1;
    } else if (cpp) {
        return 2;
    }
    return 0;
}

void to_java()
{
    char* pch;
    int i;
    for (pch = buffer, i = 0; *pch; pch++, i++) {
        if (*pch == '_') {
            pch++;
            output[i] = toupper(*pch);
        } else {
            output[i] = *pch;
        }
    }
    output[i] = 0;
}

void to_cpp()
{
    char* pch;
    int i;
    for (pch = buffer, i = 0; *pch; pch++, i++) {
        if (isupper(*pch)) {
            output[i++] = '_';
            output[i] = tolower(*pch);
        } else {
            output[i] = *pch;
        }
    }
    output[i] = 0;
}

int main()
{
    int id;
    while (!feof(stdin)) {
        scanf("%s", buffer);
        if (feof(stdin)) {
            break;
        }
        id = identify();
        if (id == 0) {
            strcpy(output, buffer);
        } else if (id == 1) {
            to_cpp();
        } else if (id == 2) {
            to_java();
        } else {
            strcpy(output, "Error!");
        }
        printf("%s\n", output);
    }
    return 0;
}
