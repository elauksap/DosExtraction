/* C++11 */

/**
 * @file   physicalConstants.h
 * @author Pasquale Claudio Africa <pasquale.africa@gmail.com>
 * @date   2014
 *
 * This file is part of the "DosExtraction" project.
 *
 * @copyright Copyright © 2014 Pasquale Claudio Africa. All rights reserved.
 * @copyright This project is released under the GNU General Public License.
 *
 * @brief Physical constants.
 *
 */

#ifndef PHYSICALCONSTANTS_H
#define PHYSICALCONSTANTS_H

#include "typedefs.h"

/**
 * @namespace constants
 *
 * @brief Numerical constants.
 */
namespace constants
{
    const Real     Q = 1.602176620898e-19;    /**< @brief Electron charge @f$ \left[ C \right] @f$. */
    const Real    Q2 = Q * Q             ;    /**< @brief Electron charge squared @f$ \left[ C^2 \right] @f$. */
    const Real   K_B = 1.380648813131e-23;    /**< @brief Boltzmann's constant @f$ \left[ J \cdot K^{-1} \right] @f$. */
    const Real T_REF = 300               ;    /**< @brief Reference temperature, used to normalize disorder parameters @f$ \left[ K \right] @f$. */
    const Real  KB_T = K_B * T_REF       ;    /**< @brief @f$ K_B \cdot T \left[ J \right] @f$. */
    const Real  V_TH = KB_T / Q          ;    /**< @brief Thermall voltage @f$ \left[ V \right] @f$. */
    const Real  EPS0 = 8.854187817620e-12;    /**< @brief Vacuum electrical permittivity @f$ \left[ C \cdot V^{-1} \cdot m^{-1} \right] @f$. */
}

#endif /* PHYSICALCONSTANTS_H */
