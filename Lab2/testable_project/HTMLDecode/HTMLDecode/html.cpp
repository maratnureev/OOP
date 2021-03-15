#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <regex>
#include "html.h"

using namespace std;

typedef regex_token_iterator<const char*> Iterator;
//TOdO
string DecodeStringIfHtmlCode(string symbolCode)
{
    if (symbolCode == "&lt;")
        return "<";
    if (symbolCode == "&gt;")
        return ">";
    if (symbolCode == "&quot;")
        return "\"";
    if (symbolCode == "&apos;")
        return "'";
    if (symbolCode == "&amp;")
        return "&";
    return symbolCode;
}

string ReadInput()
{
    string inputString;
    getline(cin, inputString);
    return inputString;
}

void WriteOutput(string const& outputString)
{
    cout << outputString;
}

string HtmlDecode(string const& html)
{
    const char* tempHtml = html.c_str();
    vector<string>htmlParts;
    Iterator::regex_type rx("(&lt;)|(&gt;)|(&quot;)|(&amp;)|(&apos;)");
    //TODO заменить strlen yf html.length()
    Iterator next(tempHtml, tempHtml + strlen(tempHtml), rx);
    Iterator end;

    string decodedString;
    next = Iterator(tempHtml, tempHtml + strlen(tempHtml), rx, { -1,0 });
    for (; next != end; ++next)
        decodedString += DecodeStringIfHtmlCode(next->str());

    return decodedString;
}
