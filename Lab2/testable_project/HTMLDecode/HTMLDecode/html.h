#pragma once


std::string ReadInput();
std::string DecodeStringIfHtmlCode(std::string symbolCode);
std::string HtmlDecode(std::string const& html);
void WriteOutput(std::string const& outputString);
