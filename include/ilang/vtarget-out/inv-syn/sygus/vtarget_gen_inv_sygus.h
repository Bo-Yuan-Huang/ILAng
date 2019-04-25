/// \file Verilog Verification Target Generator -- generating one SyGuS target
/// This is only one round of the cex based sygus
/// but it should be allowd to call dp/chc
// ---Hongce Zhang (hongcez@princeton.edu)

#ifndef VTARGET_GEN_INV_SYGUS_H__
#define VTARGET_GEN_INV_SYGUS_H__

#include <ilang/config.h>

#include <ilang/ila/instr_lvl_abs.h>
#include <ilang/vtarget-out/vlg_mod.h>
#include <ilang/vtarget-out/vtarget_gen_impl.h>
#include <ilang/vtarget-out/inv-syn/sygus/sygus_dp.h>
#include <ilang/vtarget-out/inv-syn/sygus/sygus_chc.h>
#include <ilang/smt-inout/yosys_smt_parser.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace ilang {

class VlgSglTgtGen_Cvc4SyGuS;

/// \brief a class to store (and generate) the problem for Chc
class design_problem {
  friend class VlgSglTgtGen_Cvc4SyGuS;
  /// Type of assertions and assumptions
  typedef std::vector<std::string> prop_t;
  /// Type of a problem --- we  can handle multiple several problems (may not
  /// needed)
  typedef struct {
    // the name in [??]
    // std::string  problem_name;
    /// will be conjuncted and put in the question
    prop_t exprs;
  } problem_t;
  /// set of problems
  typedef std::map<std::string, problem_t> problemset_t;

protected:
  /// assumptions are not shared (unlike CoSA)
  problemset_t assumptions;
  /// problems are splitted into items
  problemset_t assertions;

}; // Chc_problem


/// \brief a class to interface w.  Chc
class VlgSglTgtGen_Cvc4SyGuS : public VlgSglTgtGen {
  /// using the target type
  using target_type_t = VlgSglTgtGen::target_type_t;
  /// a tuple to store all related info for modification
  using info_t = VerilogModifier::info_t;
  /// filename -> (lineno, varname, is_port_sig) vec
  using fn_l_map_t = VerilogModifier::fn_l_map_t;
  /// Type of advanced parameter
  using advanced_parameters_t = VlgVerifTgtGenBase::advanced_parameters_t;
  /// Type of synthesis_backend_selector

public:
  // --------------------- CONSTRUCTOR ---------------------------- //
  ///
  /// \param[in] output path (ila-verilog, wrapper-verilog, problem.txt,
  /// run-verify-by-???, modify-impl, it there is ) \param[in] pointer to the
  /// instruction \param[in] the default configuration for outputing verilog
  /// \param[in] the variable map
  /// \param[in] the conditions
  /// \param[in] pointer to verify info class
  /// \param[in] verilog module name
  /// \param[in] ila module name,
  /// \param[in] all implementation sources
  /// \param[in] all include paths
  /// \param[in] which backend to use, it needs this info to gen proper
  /// properties
  VlgSglTgtGen_Cvc4SyGuS(
      const std::string& output_path, // will be a sub directory of the
                                      // output_path of its parent
      const InstrPtr& instr_ptr, // which could be an empty pointer, and it will
                                 // be used to verify invariants
      const InstrLvlAbsPtr& ila_ptr,
      const VerilogGenerator::VlgGenConfig& config, nlohmann::json& _rf_vmap,
      nlohmann::json& _rf_cond,  VlgTgtSupplementaryInfo & _sup_info , VerilogInfo* _vlg_info_ptr,
      const std::string& vlg_mod_inst_name,
      const std::string& ila_mod_inst_name, const std::string& wrapper_name,
      const std::vector<std::string>& implementation_srcs,
      const std::vector<std::string>& include_dirs,
      const vtg_config_t& vtg_config, backend_selector vbackend,
      synthesis_backend_selector sbackend,
      const target_type_t& target_tp,
      advanced_parameters_t * adv_ptr,
      TraceDataPoints * dp, // datapoint can be NULL if th configuration is transfer function
      const std::vector<std::string> & var_name_set,
      bool enumerate);

  // --------------------- Destructor ---------------------------- //
  /// do nothing
  virtual ~VlgSglTgtGen_Cvc4SyGuS();

protected:
  /// design's problem generate
  design_problem _problems;
  /// Chc problem file name
  std::string design_prob_fname;
  /// Chc script 'run.sh' name
  std::string sygus_run_script_name;
  /// the invariants on the design
  std::vector<std::string> vlg_mod_inv_vec;
  /// the synthesis backend
  synthesis_backend_selector s_backend;
  /// the smt info of the design
  std::shared_ptr<smt::YosysSmtParser> design_smt_info;
  /// the sygus datapoint
  TraceDataPoints * datapoints;
  /// the var name set
  const std::vector<std::string> & var_names;
  /// how hard to try: try enumerate
  bool enumerate;

protected:
  /// Add an assumption -- needed by base class
  virtual void add_an_assumption(const std::string& aspt,
                                 const std::string& dspt) override;
  /// Add an assertion -- needed by base class
  virtual void add_an_assertion(const std::string& asst,
                                const std::string& dspt) override;
  /// Add a direct assumption -- needed by base class
  virtual void add_a_direct_assumption(const std::string& aspt,
                                       const std::string& dspt) override;
  /// Add a direct assertion -- needed by base class
  virtual void add_a_direct_assertion(const std::string& asst,
                                      const std::string& dspt) override;
  /// Add an assignment which in JasperGold could be an assignment, but in Chc
  /// has to be an assumption -- needed by base class
  virtual void add_wire_assign_assumption(const std::string& varname,
                                          const std::string& expression,
                                          const std::string& dspt) override;
  /// Add an assignment to a register which in JasperGold could be an
  /// assignment, but in Chc has to be an assumption -- needed by base class
  virtual void add_reg_cassign_assumption(const std::string& varname,
                                          const std::string& expression,
                                          int width,
                                          const std::string& cond,
                                          const std::string& dspt) override;

  /// Pre export work : add assume and asssert to the top level
  void virtual PreExportProcess() override;
  /// export the script to run the verification
  virtual void Export_script(const std::string& script_name) override;
  /// export extra things: the chc script, the smt template
  virtual void
  Export_problem(const std::string& extra_name) override;
  /// export the memory abstraction (implementation)
  /// Yes, this is also implementation specific, (jasper may use a different
  /// one)
  virtual void Export_mem(const std::string& mem_name) override;
  /// For jasper, this means do nothing, for chc, you need to add (*keep*)
  virtual void Export_modify_verilog() override;

private:
 
  /// Convert the smt file to CHC format's sygus
  void convert_smt_to_chc_sygus(
    const std::string & smt_fname, const std::string & sygus_chc_fname);
  /// Convert the datapoints to the CHC format (in this case, it does not heavily depend on the chc)
  /// but you still need to read it in, I think
  void convert_datapoints_to_sygus(const std::string & smt_fname,
    TraceDataPoints * dp, const std::string & sygus_fname);

  /// load smt info from the output of design_only_gen_smt
  void load_smt_from_file(const std::string & smt_fname, std::string & smt_converted);

  /// generate the wrapper's smt first
  void design_only_gen_smt(
    const std::string & smt_name,
    const std::string & ys_script_name);  

public:
  /// overwrite the Export
  void virtual ExportAll(const std::string& wrapper_name,
                         const std::string& ila_vlg_name,
                         const std::string& script_name,
                         const std::string& extra_name,
                         const std::string& mem_name) override;
  /// accessor of the design info 
  std::shared_ptr<smt::YosysSmtParser> GetDesignSmtInfo() const;
  /// It is okay to instantiation
  virtual void do_not_instantiate(void) override{};

}; // class VlgVerifTgtGenChc


}; // namespace ilang

#endif // VTARGET_GEN_INV_SYGUS_H__
