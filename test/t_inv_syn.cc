/// \file
/// Unit test for invariant synthesis

#include <ilang/util/fs.h>
#include <ilang/ila/instr_lvl_abs.h>
#include <ilang/ilang++.h>
#include <ilang/vtarget-out/vtarget_gen.h>
#include <ilang/vtarget-out/inv-syn/inv_syn_cegar.h>

#include "unit-include/config.h"
#include "unit-include/pipe_ila.h"
#include "unit-include/memswap.h"
#include "unit-include/util.h"

namespace ilang {


typedef std::vector<std::string> P;
// Z3, ABC, FREQHORN
// ABC w. different configurations
// FREQHORN w. different configurations
// SMT IN?
// smt-target-gen


// will not execute any external tools
TEST(TestVlgVerifInvSyn, SimpleCntCegar) {
  auto ila_model = CntTest::BuildModel();

  VerilogVerificationTargetGenerator::vtg_config_t cfg;
  cfg.InvariantSynthesisReachableCheckKeepOldInvariant = false;
  cfg.CosaAddKeep = false;
  cfg.VerificationSettingAvoidIssueStage = true;
  cfg.YosysSmtFlattenDatatype = false; // let's test flatten datatype also
  cfg.YosysSmtFlattenHierarchy = true;

  auto dirName = os_portable_append_dir( std::string(ILANG_TEST_SRC_ROOT) , 
    P({ "unit-data","inv_syn","cnt2"}) );
  auto outDir  = os_portable_append_dir( std::string(ILANG_TEST_SRC_ROOT) , 
    P({"unit-data","inv_syn","cnt2-cex"}) );

  InvariantSynthesizerCegar vg(
      {},                          // no include
      {os_portable_append_dir(dirName , P({"verilog", "opposite.v" }))} , //
      "opposite",                // top_module_name
      os_portable_append_dir(dirName , P({ "rfmap","vmap.json" })), // variable mapping
      os_portable_append_dir(dirName , P({ "rfmap","cond-noinv.json" })),
      outDir, ila_model.get(),
      VerilogVerificationTargetGenerator::backend_selector::COSA,
      VerilogVerificationTargetGenerator::synthesis_backend_selector::Z3,
      cfg);

  EXPECT_FALSE(vg.in_bad_state());

  vg.GenerateVerificationTarget();
  EXPECT_FALSE(vg.RunVerifAuto("INC", "", true));
  vg.ExtractVerificationResult();
  vg.GenerateSynthesisTarget(); // you will need fp engine
  EXPECT_FALSE(vg.RunSynAuto(true));
  vg.ExtractSynthesisResult(); // very weired, it throw away something in arg
  EXPECT_FALSE(vg.in_bad_state());

  vg.GenerateInvariantVerificationTarget();
  auto design_stat = vg.GetDesignStatistics();
  design_stat.StoreToFile(os_portable_append_dir(outDir, "design_stat.txt"));
  ILA_INFO << "========== Design Info ==========" ;
  ILA_INFO << "#bits= " << design_stat.NumOfDesignStateBits;
  ILA_INFO << "#vars=" << design_stat.NumOfDesignStateVars;
  ILA_INFO << "#extra_bits= " << design_stat.NumOfExtraStateBits;
  ILA_INFO << "#extra_vars=" << design_stat.NumOfExtraStateVars;
  ILA_INFO << "t(eq)= " << design_stat.TimeOfEqCheck;
  ILA_INFO << "t(syn)=" << design_stat.TimeOfInvSyn;
  ILA_INFO << "t(proof)= " << design_stat.TimeOfInvProof;
  ILA_INFO << "t(validate)=" << design_stat.TimeOfInvValidate;
  design_stat.LoadFromFile(os_portable_append_dir(outDir, "design_stat.txt"));

  vg.LoadPrevStatisticsState(os_portable_append_dir(outDir, "design_stat.txt"));
  // test save invariants / load invariants
  vg.GetInvariants().ExportToFile(os_portable_append_dir(outDir, "inv.txt"));
  vg.LoadCandidateInvariantsFromFile(os_portable_append_dir(outDir, "inv.txt"));
  EXPECT_EQ(vg.GetCandidateInvariants().NumInvariant(), vg.GetInvariants().NumInvariant());
  vg.RemoveInvariantsByIdx(0);
  EXPECT_EQ(vg.GetInvariants().NumInvariant(),0);
  vg.LoadInvariantsFromFile(os_portable_append_dir(outDir, "inv.txt"));
  EXPECT_EQ(vg.GetInvariants().NumInvariant(),1);
} // CegarPipelineExample



TEST(TestVlgVerifInvSyn, SimpleCntCegarPassed) {
  auto ila_model = CntTest::BuildModel();

  VerilogVerificationTargetGenerator::vtg_config_t cfg;
  cfg.InvariantSynthesisReachableCheckKeepOldInvariant = false;
  cfg.CosaAddKeep = false;
  cfg.VerificationSettingAvoidIssueStage = true;
  cfg.YosysSmtFlattenDatatype = false; // let's test flatten datatype also
  cfg.YosysSmtFlattenHierarchy = true;

  auto dirName = os_portable_append_dir( std::string(ILANG_TEST_SRC_ROOT) , 
    P({ "unit-data","inv_syn","cnt2"}) );
  auto outDir  = os_portable_append_dir( std::string(ILANG_TEST_SRC_ROOT) , 
    P({"unit-data","inv_syn","cnt2-pass"}) );

  InvariantSynthesizerCegar vg(
      {},                          // no include
      {os_portable_append_dir(dirName , P({"verilog", "opposite.v" }))} , //
      "opposite",                // top_module_name
      os_portable_append_dir(dirName , P({ "rfmap","vmap.json" })), // variable mapping
      os_portable_append_dir(dirName , P({ "rfmap","cond-noinv.json" })),
      outDir, ila_model.get(),
      VerilogVerificationTargetGenerator::backend_selector::COSA,
      VerilogVerificationTargetGenerator::synthesis_backend_selector::Z3,
      cfg);

  EXPECT_FALSE(vg.in_bad_state());

  vg.GenerateVerificationTarget();
  EXPECT_TRUE(vg.RunVerifAuto("INC", "", true));
} // SimpleCntCegarPassed

}; // namespace ilang
