/// \file Source of variable extractor
/// This is use to extract variable from expression (string)
/// See whether it is ila-state(I/O) / vlg-state and ...
/// and change their name if needed and generate a string
// --- Hongce Zhang

#include <ilang/util/log.h>
#include <ilang/util/str_util.h>
#include <ilang/vtarget-out/var_extract.h>
#include <cctype> 

namespace ilang {

  // mi == ila_inst_name / vlg_inst_name
  bool VarExtractor::contains_mod_inst_name(const std::string & s, const std::string & mi) {
    ILA_ERROR_IF(mi == "") << "Implementation bug: set the module instances name first";
    return Split(s,".").front() == mi;
  }

  
  void VarExtractor::set_module_inst_name(const std::string & i, const std::string & v) {
    ila_inst_name = i; vlg_inst_name = v;
  }

  std::string VarExtractor::GenString () const {
    std::string ret;
    for (auto && t_s_pair : _tokens) 
      ret += t_s_pair.second;
    return ret;
  }

  bool isStateBegin(unsigned char c) {
    return std::isalpha(c);
  }

  bool isStateCont(unsigned char c) {
    return std::isalpha(c) || std::isdigit(c) || c == '.';
  }

  bool isNumBegin(unsigned char c) {
    return isdigit(c) || c == '\'';
  }

  bool isNumCont(unsigned char c) {
    return isdigit(c) || isalpha(c) || c == '\'';
  }

  // [A-Za-z_][A-Za-z0-9\.]+ ==> state
  // ['0-9][A-Za-z0-9']+ ==> num
  void VarExtractor::ParseToExtract(const std::string & in, bool force_vlg_statename) {
    _tokens.clear();
    if ( in.empty() ) {
      ILA_ERROR << "Parsing an empty refinement string!";
      return ;
    }

    auto l = in.length();

    bool is_num = isNumBegin(in.at(0));
    bool is_state = isStateBegin(in.at(0));
    ILA_ASSERT( !(is_num && is_state) ) << "Implementation bug";

    size_t left = 0;
    size_t idx  = 1;

    for( ; idx < l; ++ idx ) {
      bool is_num_new = (is_num && isNumCont( in.at(idx) )) || isNumBegin( in.at(idx) ) ;
      bool is_state_new = (is_state && isStateCont( in.at(idx) )) || isStateBegin( in.at(idx) ) ;

      if(is_num && is_state)  {
        ILA_ASSERT(false) << "This should not be possible";
      } else if(is_num && !is_state) { // in the num matching
        if (!is_num_new) { // leave matching
          is_num = false;
          _tokens.push_back( { token_type::NUM , in.substr(left, idx - left ) } ); 
          left = idx;
          if(is_state_new) 
            is_state = true;
        }
      } else if(is_state && !is_num) { // in the state matching
        if(!is_state_new) { // leave matching
          is_state = false;
          auto subs = in.substr(left, idx - left );
          token_type tp;
          if(_is_ila_state(subs) && !force_vlg_statename )        
            tp = ILA_S;
          else if (_is_vlg_state(subs) )  
            tp = VLG_S;  
          else                            
            tp = UNKN_S;
          _tokens.push_back( { tp , subs } ); 
          left = idx;
          if(is_num_new) 
            is_num = true;
        }
      } else if(!is_state && !is_num) { // not in the matching
        // see if we need to start matching
        ILA_ASSERT( !(is_num_new && is_state_new ) ) << "This should not be possible";
        if (is_num_new || is_state_new) {
          _tokens.push_back( { token_type::KEEP , in.substr(left, idx - left ) } ); 
          left = idx;
        }
        if(is_num_new) {
          // copy [left, idx (not including) ] to KEEP
          is_num = true;
          is_state = false;
        } else if (is_state_new) {
          // copy [left, idx (not including) ] to KEEP
          is_num = false;
          is_state = true;
        }

      } else 
        ILA_ASSERT(false) <<"Implementation bug, should not be reachable!";
    }
    ILA_ASSERT( !(is_num && is_state) ) << "Implementation bug";
    // copy the last if necessary
    if(left < idx) {
      auto subs = in.substr(left, idx - left );
      if (is_num) 
        _tokens.push_back( { token_type::NUM , subs } );
      else if (is_state) {
        token_type tp;
        if(_is_ila_state(subs) && !force_vlg_statename)       
         tp = ILA_S;
        else if (_is_vlg_state(subs) )  
          tp = VLG_S;
        else                            
          tp = UNKN_S;
        _tokens.push_back( { tp , subs } ); 
      }
    }
  }
  
  void VarExtractor::ForEachTokenReplace( str_r replacer ) {
    size_t idx = -1;
    for(auto && p : _tokens) {
      idx ++ ;
      auto rep = replacer(p);
      if (rep == p.second) continue;
      _tokens[idx] = std::make_pair(p.first, rep);
    }
  }


  
  //Find the strings like this : 

}; // namespace ilang