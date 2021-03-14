#include <fstream>
#include "html.h"

int main()
{
    std::string html = ReadInput();
    std::string decodedHtml = HtmlDecode(html);
    WriteOutput(decodedHtml);
}
