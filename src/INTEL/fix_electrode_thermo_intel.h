/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/ Sandia National Laboratories
   LAMMPS development team: developers@lammps.org

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
   Contributing author: Shern Tee (UQ)
------------------------------------------------------------------------- */

#ifdef FIX_CLASS

// clang-format off
FixStyle(electrode/thermo/intel, FixElectrodeThermoIntel)
// clang-format on

#else

#ifndef LMP_FIX_ELECTRODE_THERMO_INTEL_H
#define LMP_FIX_ELECTRODE_THERMO_INTEL_H

#include "fix_electrode_thermo.h"
#include "pppm_electrode_intel.h"

namespace LAMMPS_NS {

class FixElectrodeThermoIntel : public FixElectrodeThermo {
 public:
  FixElectrodeThermoIntel(class LAMMPS *lmp, int narg, char **arg) : FixElectrodeThermo(lmp, narg, arg) {}
  inline void init() final override {
    _intel_kspace = dynamic_cast<PPPMElectrodeIntel*>(force->kspace_match("pppm/electrode/intel", 0));
    if (_intel_kspace == nullptr) error->all(FLERR, "pppm/electrode/intel is required by fix electrode/thermo/intel");

    intelflag = true;
    FixElectrodeThermo::init();
  }
  inline void intel_pack_buffers() final override {
    _intel_kspace->pack_buffers_q();
  }

 private:
  PPPMElectrodeIntel * _intel_kspace;
};

}    // namespace LAMMPS_NS

#endif
#endif
