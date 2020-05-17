#pragma once
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iterator>
#include "string.h"

class VariableBase
{
public:
    VariableBase(std::string const& type, std::string const& name)
        : m_Type(type)
        , m_Name(name)
    {}

    virtual void       GetValue(void* value) = 0;
    virtual void*      GetValueAddress() = 0;
    std::string const& GetType() const { return m_Type; }
    std::string const& GetName() const { return m_Name; }

    static void AddVariables(std::vector<std::unique_ptr<VariableBase>>&)
    {
    }
    template <typename T, typename ... Ts>
    static void AddVariables(std::vector<std::unique_ptr<VariableBase>>& variables, T const& first, Ts const& ... rest)
    {
        variables.push_back(std::make_unique<T>(first));
        AddVariables(variables, rest ...);
    }

private:
    std::string m_Type;
    std::string m_Name;
};

std::vector<std::string> TokenizeString(std::string const& string);

template <typename T>
class Variable : public VariableBase
{
public:
    template <typename ... Params>
    Variable(std::string const& name, Params ... params)
        : VariableBase(TokenizeString(typeid(T).name()).back(), name)
        , m_Value(params ...)
    {}

    void GetValue(void* value) override { *((T*)value) = m_Value; }
    void* GetValueAddress() override { return &m_Value; }
private:
    T m_Value;
};
