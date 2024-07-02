#pragma once

#include <memory>

#include "SystemInputInterface.hpp"
#include "SystemOutputInterface.hpp"

struct SystemInterfaces
{
    std::shared_ptr<SystemInputInterface> sysInput;
    std::shared_ptr<SystemOutputInterface> sysOutput;
};