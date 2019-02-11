/// \file Verilog Verification Target Generator -- for Yosys 
/// We use yosys to convert Verilog to smt-lib2, and then
/// it will be converted to horn clause
/// This file should not be included, as it requires the impl.
/// Internally, we use the
// ---Hongce Zhang

#ifndef VTARGET_GEN_YOSYS_H__
#define VTARGET_GEN_YOSYS_H__

#include <ilang/config.h>

#include <ilang/ila/instr_lvl_abs.h>
#include <ilang/vtarget-out/vlg_mod.h>
#include <ilang/vtarget-out/vtarget_gen_impl.h>
#include <iostream>
#include <string>
#include <vector>

namespace ilang {

class VlgSglTgtGen_Yosys;
class VlgSglTgtGen_Yosys_design_only;

/// \brief a class to store (and generate) the problem for Yosys
class Yosys_problem {
  friend class VlgSglTgtGen_Yosys;
  friend class VlgSglTgtGen_Yosys_design_only;
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

}; // Yosys_problem

/// \brief the information that the design target
/// can get for the instruction target
struct YosysDesignSmtInfo {
  /// Type of vector of names in the design verilog
  typedef std::vector<std::string> pos_name_map_t;
  /// The pos -> name map
  pos_name_map_t state_pos_name_map; 
  /// the top module name of the design_only_module
  std::string top_mod_name;
};

/// \brief a class to interface w.  Yosys
class VlgSglTgtGen_Yosys : public VlgSglTgtGen {
  /// using the target type
  using target_type_t = VlgSglTgtGen::target_type_t;
  /// a tuple to store all related info for modification
  using info_t = VerilogModifier::info_t;
  /// filename -> (lineno, varname, is_port_sig) vec
  using fn_l_map_t = VerilogModifier::fn_l_map_t;

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
  VlgSglTgtGen_Yosys(
      const std::string& output_path, // will be a sub directory of the
                                      // output_path of its parent
      const InstrPtr& instr_ptr, // which could be an empty pointer, and it will
                                 // be used to verify invariants
      const InstrLvlAbsPtr& ila_ptr,
      const VerilogGenerator::VlgGenConfig& config, nlohmann::json& _rf_vmap,
      nlohmann::json& _rf_cond, VerilogInfo* _vlg_info_ptr,
      const std::string& vlg_mod_inst_name,
      const std::string& ila_mod_inst_name, const std::string& wrapper_name,
      const std::vector<std::string>& implementation_srcs,
      const std::vector<std::string>& include_dirs,
      const vtg_config_t& vtg_config, backend_selector backend,
      const target_type_t& target_tp);

protected:
  /// Yosys problem generate
  Yosys_problem _problems;
  /// Yosys problem file name
  std::string yosys_prob_fname;
  /// Yosys script 'run.sh' name
  std::string yosys_run_script_name;

protected:
  /// template for generating yosys script wo arrays
  std::string yosysGenerateSmtScript_wo_Array;
  /// template for generating yosys script
  std::string yosysGenerateSmtScript_w_Array;

protected:
  /// Add an assumption
  virtual void add_an_assumption(const std::string& aspt,
                                 const std::string& dspt) override;
  /// Add an assertion
  virtual void add_an_assertion(const std::string& asst,
                                const std::string& dspt) override;
  /// Add a direct assumption
  virtual void add_a_direct_assumption(const std::string& aspt,
                                       const std::string& dspt) override;
  /// Add a direct assertion
  virtual void add_a_direct_assertion(const std::string& asst,
                                      const std::string& dspt) override;
  /// Add an assignment which in JasperGold could be an assignment, but in Yosys
  /// has to be an assumption
  virtual void add_wire_assign_assumption(const std::string& varname,
                                          const std::string& expression,
                                          const std::string& dspt) override;
  /// Add an assignment to a register which in JasperGold could be an
  /// assignment, but in Yosys has to be an assumption
  virtual void add_reg_cassign_assumption(const std::string& varname,
                                          const std::string& expression,
                                          const std::string& cond,
                                          const std::string& dspt) override;

  /// Pre export work : add assume and asssert to the top level
  void virtual PreExportProcess() override;
  /// export the script to run the verification
  virtual void Export_script(const std::string& script_name) override;
  /// export extra things: the yosys script, the smt template
  virtual void
  Export_problem(const std::string& extra_name) override;

  /// export extra things: the yosys script, the smt template
  /// for the dual ind-inv option
  virtual void
  Export_problem(const std::string& extra_name, const smt_info & smtinfo);

  /// Export problem for getting the smt of the wrapper
  virtual void Export_problem_smt(const std::string& extra_name);

  /// Export script for getting the smt of the wrapper
  virtual void Export_script_smt(const std::string& script_name);
  
  /// export the memory abstraction (implementation)
  /// Yes, this is also implementation specific, (jasper may use a different
  /// one)
  virtual void Export_mem(const std::string& mem_name) override;
  /// For jasper, this means do nothing, for yosys, you need to add (*keep*)
  virtual void Export_modify_verilog() override;

  /// extract state info from design
  static YosysDesignSmtInfo::pos_name_map_t 
  extract_state_info_from_smt(const std::string &fname);

  /// generate smt encoding for the wrapper, return true if succeeded
  virtual bool VlgSglTgtGen_Yosys::Gen_wrapper_smt() const;

public:
  /// Need the smt info
  /// Take care of exporting all of a single target
  void virtual ExportAll(const std::string& wrapper_name,
                         const std::string& ila_vlg_name,
                         const std::string& script_name,
                         const std::string& extra_name,
                         const std::string& mem_name,
                         const YosysDesignSmtInfo& smt_info);
                         
  /// Deprecation of the one without smt info
  void virtual ExportAll(const std::string& wrapper_name,
                         const std::string& ila_vlg_name,
                         const std::string& script_name,
                         const std::string& extra_name,
                         const std::string& mem_name) override;
  

  /// It is okay to instantiation
  virtual void do_not_instantiate(void) override{};

}; // class VlgVerifTgtGenYosys


/// \brief a class to interface w.  Yosys : generating the design itself only
class VlgSglTgtGen_Yosys_design_only : public VlgSglTgtGen_Yosys {
  /// using the target type
  using target_type_t = VlgSglTgtGen::target_type_t;
  /// a tuple to store all related info for modification
  using info_t = VerilogModifier::info_t;
  /// filename -> (lineno, varname, is_port_sig) vec
  using fn_l_map_t = VerilogModifier::fn_l_map_t;

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
  VlgSglTgtGen_Yosys_design_only(
      const std::string& output_path, // will be a sub directory of the
                                      // output_path of its parent
      const InstrPtr& instr_ptr, // which could be an empty pointer, and it will
                                 // be used to verify invariants
      const InstrLvlAbsPtr& ila_ptr,
      const VerilogGenerator::VlgGenConfig& config, nlohmann::json& _rf_vmap,
      nlohmann::json& _rf_cond, VerilogInfo* _vlg_info_ptr,
      const std::string& vlg_mod_inst_name,
      const std::string& ila_mod_inst_name, const std::string& wrapper_name,
      const std::vector<std::string>& implementation_srcs,
      const std::vector<std::string>& include_dirs,
      const vtg_config_t& vtg_config, backend_selector backend,
      const target_type_t& target_tp);

  /// recover the one without smt info
  void virtual ExportAll(const std::string& wrapper_name,
                         const std::string& ila_vlg_name,
                         const std::string& script_name,
                         const std::string& extra_name,
                         const std::string& mem_name) override;

protected:
  /// Pre export work : add assume and asssert to the top level
  void virtual PreExportProcess() override;
  /// export the script to run the verification
  virtual void Export_script(const std::string& script_name) override;
  /// export extra things: the yosys script, the smt template
  virtual void
  Export_problem(const std::string& extra_name) override;

public:
  // -------------- MEMBER functions -------------------- //
  /// run the smt generation and get the yosys_design_info_that_is_used 
  /// for the Yosys inv gen class
  YosysDesignSmtInfo RunSmtGeneration();

protected:
  /// the generated smt_file_name 
  /// not including directory name
  /// - created by Export_problem
  /// - used by RunSmtGeneration
  std::string smt_file_name;

}; // class VlgVerifTgtGenYosys

}; // namespace ilang

#endif // VTARGET_GEN_YOSYS_H__
