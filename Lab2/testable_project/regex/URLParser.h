#pragma once


bool ParseURL(std::string const& url, std::string& protocol, int& port, std::string& host, std::string& document);
void WriteURLParts(std::string const& url, std::string& protocol, int& port, std::string& host, std::string& document);
