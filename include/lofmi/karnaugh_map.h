#pragma once

#include "lofmi/common.h"
#include "lofmi/truth_table.h"
#include "lofmi/gray_code.h"

namespace Lofmi
{
class KarnaughMap
{
public:
    KarnaughMap(const TruthTable& tt);
    friend std::ostream& operator<<(std::ostream& os, const KarnaughMap& km);
    
private:
    std::vector<GrayCode> rows;
    std::vector<GrayCode> cols;
    BoolMatrix map;

    void FillGraySequence(std::vector<GrayCode>& sequence);
    void FillMap(const TruthTable& tt);
};

} // namespace Lofmi
