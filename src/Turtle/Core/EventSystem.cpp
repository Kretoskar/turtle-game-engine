#include "Turtle/Core/EventSystem.h"

Turtle::Dispatcher* Turtle::Dispatcher::_instance = nullptr;

void Turtle::Dispatcher::Init()
{
    Turtle::Dispatcher::_instance = new Turtle::Dispatcher();
}

void Turtle::Dispatcher::Cleanup()
{
    delete Turtle::Dispatcher::_instance;
}

void Turtle::Dispatcher::Subscribe(TurtleString Type, std::function<void(void*)>&& Func)
{
    _observers[Type].push_back(Func);
}

void Turtle::Dispatcher::Post(TurtleString Type, void* Payload) const
{
    if (_observers.find(Type) == _observers.end())
    {
        return;
    }

    auto&& observers = _observers.at(Type);

    for (auto&& observer : observers)
    {
        observer(Payload);
    }
}