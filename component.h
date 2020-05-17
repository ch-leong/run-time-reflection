#pragma once
#include "variable.h"

class Component
{
public:
    inline Component*  GetParent() { return m_Parent; }
    inline void        SetParent(Component* parent) { m_Parent = parent; }
    inline auto const& GetVariables() const { return m_Variables; }
    VariableBase* GetVariable(std::string const& name) const;
    template <typename T>
    Variable<T>* AddVariable(Variable<T>& variable)
    {
        // If already exist.
        if (GetVariable(variable.GetName()) != nullptr)
            return nullptr;

        VariableBase::AddVariables(m_Variables, variable);
        return Variable<T>(GetVariable(variable.GetName()));
    }
    bool RemoveVariable(std::string const& name);

protected:
    template <typename ... Ts>
    Component(Component* parent = nullptr, Ts ... params)
        : m_Parent(parent)
        , m_Variables()
    {
        VariableBase::AddVariables(m_Variables, params ...);
    }
    virtual ~Component();

    Component* m_Parent;
    std::vector<std::unique_ptr<VariableBase>> m_Variables;
};

class Transform : public Component
{
public:
    Transform(std::string const& name);
    virtual ~Transform() {}
};

struct Vector3
{
    float x, y, z;
};
