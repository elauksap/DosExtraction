/* C++11 */

/**
 * @file   paramList.cc
 * @author Pasquale Claudio Africa <pasquale.africa@gmail.com>
 * @date   2014
 *
 * This file is part of the "DosExtraction" project.
 *
 * @copyright Copyright © 2014 Pasquale Claudio Africa. All rights reserved.
 * @copyright This project is released under the GNU General Public License.
 *
 */

#include "paramList.h"

using namespace constants;

ParamList::ParamList(const RowVectorXr & list)
{
    assert( list.size() == PARAMS_NO );
    
    assert( list( 0) >  0   );
    assert( list( 1) >  0.0 );
    assert( list( 2) >  0.0 );
    assert( list( 3) >  0.0 );
    assert( list( 4) >  0.0 );
    assert( list( 8) >= 0.0 );
    assert( list( 9) >= 0.0 );
    assert( list(10) >= 0.0 );
    assert( list(11) >= 0.0 );
    assert( list(13) >= 0.0 );
    assert( list(14) >= 0.0 );
    assert( list(16) >= 0.0 );
    assert( list(17) >= 0.0 );
    assert( list(21) >  0   );
    assert( list(22) >  0   );
    assert( list(23) >  0   );
    assert( list(24) >  0   );
    assert( list(25) <  0   );
    assert( list(26) >  0   );
    
    simulationNo_ = list( 0)       ;
    t_semic_      = list( 1)       ;
    t_ins_        = list( 2)       ;
    eps_semic_    = list( 3) * EPS0;
    eps_ins_      = list( 4) * EPS0;
    T_            = list( 5)       ;
    Wf_           = list( 6) * Q   ;
    Ea_           = list( 7) * Q   ;
    N0_           = list( 8)       ;
    sigma_        = list( 9) * KB_T;
    N0_2_         = list(10)       ;
    sigma_2_      = list(11) * KB_T;
    shift_2_      = list(12)       ;
    N0_3_         = list(13)       ;
    sigma_3_      = list(14) * KB_T;
    shift_3_      = list(15)       ;
    N0_4_         = list(16)       ;
    sigma_4_      = list(17) * KB_T;
    shift_4_      = list(18)       ;
    N0_exp_       = list(19)       ;
    lambda_exp_   = list(20) * KB_T;
    A_semic_      = list(21)       ;
    C_sb_         = list(22)       ;
    nNodes_       = list(23)       ;
    nSteps_       = list(24)       ;
    V_min_        = list(25)       ;
    V_max_        = list(26)       ;
}
