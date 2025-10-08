#pragma once

enum Result {
    TIE = 1,
    FIRSTWINNER = 2,
    SECONDWINNER = 3
};

namespace trainer
{
    Network train();
}
