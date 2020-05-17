#pragma once
#include "variable.h"

class Component
{
public:
    inline Component*  GetParent() { return m_Parent; }
    inline void        SetParent(Component* parent) { m_Parent = parent; }
    inline auto const& GetVariables() const { return m_Variables; }

    // Currently linear. Well if use a different container, will be different.
    VariableBase* GetVariable(std::string const& name) const;

    // Also linear.
    template <typename T>
    Variable<T>* AddVariable(Variable<T>& variable)
    {
        // If already exist.
        if (GetVariable(variable.GetName()) != nullptr)
            return nullptr;

        VariableBase::AddVariables(m_Variables, variable);
        return Variable<T>(GetVariable(variable.GetName()));
    }

    // Linear~
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
    std::vector<std::unique_ptr<VariableBase>> m_Variables; // Can be different container, but need to change in class Variable.
};

class Transform : public Component
{
public:
    Transform(std::string const& name);
    virtual ~Transform() {}
};

// Sample user-class.
struct Vector3
{
    float x, y, z;
};
