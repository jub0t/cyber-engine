#include "./include/cyber.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#define STR(s) ((CsStr){s, strlen(s)})

void print(CsVM *vm, CsStr str)
{
    printf("[DEBUG]: %.*s\n", (int)str.len, str.buf);
}

std::string read_file(std::string path)
{
    std::string line;
    std::ifstream file(path);
    std::string out;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            out.append(line + "\n");
        }

        file.close();
    }

    return out;
}

int main()
{
    CsVM *vm = csCreate();
    csSetPrinter(vm, print);

    std::string master_code = read_file("./game/index.cy");
    const char *code = static_cast<const char *>(master_code.c_str());

    CsStr src = STR(code);
    CsValue val;

    int res = csEval(vm, src, &val);
    if (res == CS_SUCCESS)
    {
        csRelease(vm, val);
    }
    else
    {
        const char *report = csNewLastErrorReport(vm);
        printf("%s\n", report);
    }

    csDestroy(vm);
    return 0;
}
