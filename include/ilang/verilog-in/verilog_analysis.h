///\file Header for Verilog Analyzer
///
/// This is to use the info generated by the parser
/// to gather the following informations
///   1. Design hierarchy (top module, which submodule is used in which module)
///     so we can determine if a reference of a signal is valid or not
///   2. where is the definition of a signal, is it a port or not
///   so we can determine if we need to add (* keep *) and where to do so
///
/// For the include part
///   may be we need to discourage the use of include
///   really no need
///   the design hierarchy is got through analysis
///
// ---Hongce Zhang

#ifndef VERILOG_ANALYSIS_H__
#define VERILOG_ANALYSIS_H__

#include <map>
#include <vector>

// I have to put this include here, because it needs to know the class
// VerilogAnalyzerBase
#include <ilang/verilog-in/verilog_analysis_wrapper.h>

extern "C" {
#include <verilogparser/verilog_ast_util.h>
#include <verilogparser/verilog_parser.h>
}

namespace ilang {

/// \brief Class to convert port to signal info
class SignalInfoPort : public SignalInfoBase {
protected:
  /// Stores its own definition
  ast_port_declaration* _def;

public:
  /// Constructor: from ast_port_declaration
  SignalInfoPort(ast_port_declaration* def, const std::string& full_name,
                 VerilogAnalyzerBase::hierarchical_name_type tp);
  /// Return its definition
  ast_port_declaration* get_def() { return _def; }
}; // class SignalInfoPort

/// \brief Class to convert reg to signal info
class SignalInfoReg : public SignalInfoBase {
protected:
  /// Stores its own definition
  ast_reg_declaration* _def;

public:
  /// Constructor: from ast_port_declaration
  SignalInfoReg(ast_reg_declaration* def, const std::string& full_name,
                VerilogAnalyzerBase::hierarchical_name_type tp);
  /// Return its definition
  ast_reg_declaration* get_def() { return _def; }
}; // class SignalInfoPort

/// \brief Class to convert wire to signal info
class SignalInfoWire : public SignalInfoBase {
protected:
  /// Stores its own definition
  ast_net_declaration* _def;

public:
  /// Constructor: from ast_port_declaration
  SignalInfoWire(ast_net_declaration* def, const std::string& full_name,
                 VerilogAnalyzerBase::hierarchical_name_type tp);
  /// Return its definition
  ast_net_declaration* get_def() { return _def; }
}; // class SignalInfoPort


/// \brief Class for Verilog analysis
class VerilogAnalyzer : public VerilogAnalyzerBase {
public:
  /// type to store multiple paths
  using path_vec_t = VerilogAnalyzerBase::path_vec_t;
  /// filename, line number pair : location type
  using vlg_loc_t = VerilogAnalyzerBase::vlg_loc_t;
  /// A map to find module ast faster
  typedef std::map<std::string, ast_module_declaration*> name_module_ast_map_t;
  /// A map of name -> names
  using name_names_map_t = VerilogAnalyzerBase::name_names_map_t;
  /// type of modulename instance name : instance_name->module_name
  using mod_inst_t = VerilogAnalyzerBase::mod_inst_t;
  /// A map of module name -> instantiation
  using name_insts_map_t = VerilogAnalyzerBase::name_insts_map_t;
  /// The result of querying a name (please don't change the order of them)
  using hierarchical_name_type = VerilogAnalyzerBase::hierarchical_name_type;
  /// hierarchical name -> hierarchical_name_type  map
  using name_type_buffer_t = VerilogAnalyzerBase::name_type_buffer_t;
  /// hierarchical name -> declaration pointer
  using name_decl_buffer_t = VerilogAnalyzerBase::name_decl_buffer_t;
  /// Top module signal list
  using module_io_vec_t = VerilogAnalyzerBase::module_io_vec_t;

protected:
  /// include path for all verilog modules
  path_vec_t vlg_include_path;
  /// verilog source files
  path_vec_t vlg_src_files;
  /// top module name
  std::string top_module_name;
  /// a map from name to module ast
  name_module_ast_map_t name_module_map;
  /// module -> instantiations
  name_names_map_t module_to_whereuses_map;
  /// module -> all sub modules
  name_insts_map_t modules_to_submodules_map;
  /// we need to know what instance name we would give for the topmodule,
  /// inorder to resolve signal names;
  std::string top_inst_name;

public:
  // --------------------- CONSTRUCTOR ---------------------------- //
  /// Analyze a set of file
  /// [in] the path to search for include
  /// [in] the source files
  /// [in] the instance name given to the topmodule
  VerilogAnalyzer(const path_vec_t& include_path, const path_vec_t& srcs,
                  const std::string& top_module_inst_name);
  // --------------------- DESTRUCTOR ---------------------------- //
  /// Destructor: clear vlg parser things
  ~VerilogAnalyzer();

protected:
  // --------------------- HELPER FUNCTIONS ---------------------------- //
  /// invoke the parser to parse the files
  void invoke_parser();
  /// extract the top module name
  void find_top_module(verilog_source_tree* source, const std::string & optional_top_module);
  /// check the result of module resolution and update the name_module_map;
  void check_resolve_modules(verilog_source_tree* source);
  /// Update the modules_to_submodules_map
  void create_module_submodule_map(verilog_source_tree* source);
  /// static instance count, we must make sure there is only one instance of it
  /// at a time o.w. it will mess up w. the C code
  static unsigned instance_count;

public:
  // --------------------- MEMBERS ---------------------------- //
  /// Return the type of a name (used externally, cached)
  hierarchical_name_type
  check_hierarchical_name_type(const std::string& net_name) const;
  /// Return the file location of the definition of a signal
  vlg_loc_t find_definition_of_signal(const std::string& net_name) const;
  /// Return the file location of the definition of a module
  vlg_loc_t find_definition_of_a_module(const std::string& module_name) const;
  /// Return the declaration of a name, which could be be converted to:
  /// ast_module_declaration, ast_net_declaration, ast_reg_declaration,
  /// ast_port_declaration
  void* find_declaration_of_name(const std::string& net_name) const;
  /// Return the location of a hierarchical name
  vlg_loc_t name2loc(const std::string& net_name) const;
  /// Return top module name
  std::string get_top_module_name() const { return top_module_name; }
  /// Return top module signal
  module_io_vec_t get_top_module_io() const;
  /// Find a signal 
  SignalInfoBase get_signal(const std::string & net_name) const;

  // --------------------- HELPERS ---------------------------- //
  /// Print Meta info (Usage PrintMeta(os, ?? ) << ?? ;  )
  static std::ostream& PrintMeta(std::ostream& os, const ast_metadata& md) {
    return (os << (md.file) << ":" << (md.line));
  }
  /// Print the meta of an Ast node (cannot be void* , has to be converted)
  template <class T>
  static std::ostream& PrintMetaAst(std::ostream& os, const T* n) {
    return PrintMeta(os, n->meta);
  }
  /// Convert ast_meta to location
  static vlg_loc_t Meta2Loc(const ast_metadata& md) {
    return vlg_loc_t(md.file, md.line);
  }

private:
  // --------------------- MEMBERS ---------------------------- //
  /// Cache: used and updated by check_hierarchical_name_type
  mutable name_type_buffer_t name_type_buffer;
  /// Cache: to store a name->declaration map
  mutable name_decl_buffer_t name_decl_buffer;
  /// return the type of a name (used internally, not cached)
  hierarchical_name_type
  _check_hierarchical_name_type(const std::string& net_name) const;

private:
  /// Track if we are in a bad state. do nothing
  bool _bad_state;
  /// We prompt if it is in a bad state
  bool _bad_state_return() const;
  /// we can instantiate this class
  void virtual should_not_instantiate() override{};

}; // class VerilogAnalyzer

}; // namespace ilang

#endif // VERILOG_ANALYSIS_H__
