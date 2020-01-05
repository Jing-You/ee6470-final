/******************************************************
 * ArchC Resources implementation file.               *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/
 

#include  "riscv_arch.H"
#include  "riscv_arch_ref.H"

//!/Default constructor.
riscv_arch_ref::riscv_arch_ref(riscv_arch& arch) : ac_arch_ref<riscv_parms::ac_word, riscv_parms::ac_Hword>(arch),
  ac_pc(arch.ac_pc), ac_id(arch.ac_id),
  DM(arch.DM_mport),   RB(arch.RB),   RBF(arch.RBF),   fflags(arch.fflags),   frm(arch.frm),   fcsr(arch.fcsr), intr_reg(arch.intr_reg)  {}
