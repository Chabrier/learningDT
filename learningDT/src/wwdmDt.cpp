/*
 * Copyright (c) 2015-2015 INRA http://www.inra.fr
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/*
 * @@tagdynamic@@
 * @@tagdepends: vle.discrete-time @@endtagdepends
 */

#include <vle/DiscreteTimeDbg.hpp>
#include <vle/devs/DynamicsDbg.hpp>

#include <iostream>

namespace vle {
namespace discrete_time {
namespace learningDT {

class wwdmDt : public DiscreteTimeDyn
{
public:
    wwdmDt(const vle::devs::DynamicsInit& init,
            const vle::devs::InitEventList& events)
        : DiscreteTimeDyn(init, events)
    {
        Eb.init(this, "Eb", events);
        Eimax.init(this, "Eimax", events);
        K.init(this, "K", events);
        Lmax.init(this, "Lmax", events);
        A.init(this, "A", events);
        B.init(this, "B", events);
        TI.init(this, "TI", events);

        PAR.init(this, "PAR", events);
        Tmean.init(this, "Tmean", events);
        Tr.init(this, "Tr", events);

        Tmin.init(this, "Tmin", events);
        Tmax.init(this, "Tmax", events);
        RG.init(this, "RG", events);

        ST.init(this, "ST", events);
        LAI.init(this, "LAI", events);
        U.init(this, "U", events);

        ST.init_value(0);
        LAI.init_value(0);
        U.init_value(0);

        Tr.init_value((1 / B()) * std::log(1 + std::exp(A() * TI())));
    }

    virtual ~wwdmDt()
    {
    }

    void compute(const vle::devs::Time& t)
    {
        PAR = 0.5 * 0.01 * RG();

        Tmean = std::max(0.0, (Tmin() + Tmax()) / 2);

        ST = ST(-1) + Tmean();

        LAI = std::max(0.0, Lmax() * ((1 / (1 + std::exp(-A() * (ST() - TI())))) -
                                      std::exp(B() * (ST() - Tr()))));

        U = U(-1) + Eb() * Eimax() * (1 - std::exp(-K() * LAI())) * PAR();
    }

    //params
    Var Eb;
    Var Eimax;
    Var K;
    Var Lmax;
    Var A;
    Var B;
    Var TI;
    // Intermediate
    Var PAR;
    Var Tmean;
    Var Tr;
    // external
    Var Tmin;
    Var Tmax;
    Var RG;
    // internal
    Var ST;
    Var LAI;
    Var U;
};

}}}


DECLARE_DYNAMICS_DBG(vle::discrete_time::learningDT::wwdmDt)
