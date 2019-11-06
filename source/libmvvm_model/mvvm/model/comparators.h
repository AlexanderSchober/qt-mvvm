// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_MODEL_COMPARATORS_H
#define MVVM_MODEL_COMPARATORS_H

#include <mvvm/core/export.h>

namespace ModelView {

//! Helper class to register variant comparators.

class CORE_EXPORT Comparators
{
public:
    static void registerComparators();
    static bool registered();

private:
    static bool m_is_registered;
};

}  // namespace ModelView

#endif  // MVVM_MODEL_COMPARATORS_H

