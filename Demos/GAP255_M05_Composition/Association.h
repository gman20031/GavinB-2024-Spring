#pragma once

#include <string>

class Programmer;

class Designer
{
    Programmer* m_pTeamProgrammer;  // ctor and/or setter and/or function parameter

public:
    void DesignSomething() {}
    void MakeProgress()
    {
        // ask programmer if you can do something
        if(m_pTeamProgrammer.CanIDoSomething() == true)
            // design something
            DesignSomething();
    }
};

class Programmer
{
public:
    void ProgramSomething() {}
    bool CanIDoThing(std::string thing)
    {
        return false;
    }
};

void Example()
{

}