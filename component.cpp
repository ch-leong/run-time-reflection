#include "component.h"

Component::~Component()
{
}

VariableBase* Component::GetVariable(std::string const& name) const
{
    for (auto const& variable : m_Variables)
    {
        if (name == variable->GetName())
        {
            return variable.get();
        }
    }
    return nullptr;
}

bool Component::RemoveVariable(std::string const& name)
{
    for (auto variable = m_Variables.begin(); variable != m_Variables.end(); ++variable)
    {
        if ((*variable)->GetName() == name)
        {
            m_Variables.erase(variable);
            return true;
        }
    }
    return false;
}

Transform::Transform(std::string const& name)
    : Component(nullptr
        , Variable<std::string>("Name", name)
        , Variable<unsigned>("ID")
        , Variable<Vector3>("Position")
        , Variable<Vector3>("Scale")
    )
{
}
