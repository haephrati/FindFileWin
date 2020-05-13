#include <cstdio>
#include <cstdlib>
#include "FindFile.h"

static void Fail(const char* msg)
{
    std::printf("FAIL %s\n", msg);
    std::exit(1);
}

int main()
{
    FindFileOptions_t opts{};
    opts.recursive = true;
    opts.returnFolders = false;
    opts.filter = L"*.cpp";
    if (!opts.recursive)
        Fail("rec");
    if (opts.returnFolders)
        Fail("folders");
    if (opts.filter != L"*.cpp")
        Fail("filter");
    std::printf("OK FindFileTests\n");
    return 0;
}
