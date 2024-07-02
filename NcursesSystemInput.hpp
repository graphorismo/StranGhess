#pragma once

#include "SystemInterfaces.hpp"

class NcursesSystemInput : public SystemInputInterface
{
public:
    char16_t GetPressedSymbol() override;
};