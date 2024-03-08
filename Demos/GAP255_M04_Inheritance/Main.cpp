#include <conio.h>
#include <iostream>

#include "Animal.h"
#include "Cat.h"
#include "Dog.h"

#define PERFORM_EVIL_CASTING 0

int main()
{
    Dog fido;
    Cat felix;          // { 100, 50, 0, 100 };
    //Animal genericAnimal;     // can't exist if Animal has a pure virtual
    Animal* pPet = nullptr;

    std::cout << "(C)at or (D)og?\n";
    char input = _getch();
    switch (input)
    {
        case 'd': pPet = &fido; break;
        case 'c': pPet = &felix; break;
    }

#if PERFORM_EVIL_CASTING

    // Cats can climb trees. How do we allow them to do that here?
    //pPets[1]->ClimbTree();

    // Static casting - assumes that it is actually a Cat, and allows
    // conversion to a Cat* to access Cat functions. However, only use
    // it if your code can guarantee that it is always a Cat.
    Cat* pStaticCat = static_cast<Cat*>(pPet);
    pStaticCat->PerformSpecialAbility();  // if this is a Dog, it's undefined behavior

    // Dynamic casting - attempts to cast using the actual state of the
    // program while it's running; checks if it succeeds, and returns
    // nullptr if it wasn't a Cat.
    Cat* pDynamicCat = dynamic_cast<Cat*>(pPet);

    // if it was a Cat, it won't be null
    bool wasACat = (pDynamicCat != nullptr);
    if (wasACat)
        pDynamicCat->PerformSpecialAbility();

#endif

    // testing enemy functionality
    std::cout << "An enemy appears.\n";

    // Can't do this because we don't to treat them as separate
    //fido.Bark();
    //felix.ClimbTree();

    // Instead we want to use the pPet pointer.
    // How can we make the dog bark and the cat climb the tree?
    pPet->OnEncounterEnemy();


    Animal* pPets[]{ &fido, &felix };

    for (size_t i = 0; i < std::size(pPets); ++i)
    {
        pPets[i]->Sleep(10);
        pPets[i]->Hunt(1);
        pPets[i]->Eat(0.15f);
        pPets[i]->Play(2);
        pPets[i]->Sleep(9);
    }

    
    



    return 0;
}