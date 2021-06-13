#pragma once
#include "IPerson.h"

template <typename Base>
class CPersonImpl : public Base
{
public:
    CPersonImpl() = default;
    CPersonImpl(std::string const& name, std::string const& surname, std::string const& middleName, std::string const& address) 
        : m_name(name)
        , m_surname(surname)
        , m_middleName(middleName)
        , m_address(address)
    {};
    std::string GetName() const
    {
        return m_name;
    }
    std::string GetSurname() const
    {
        return m_surname;
    }
    std::string GetMiddleName() const
    {
        return m_middleName;
    }
    std::string GetAddress() const
    {
        return m_address;
    }

private:
    std::string m_name = "";
    std::string m_surname = "";
    std::string m_middleName = "";
    std::string m_address = "";
};
