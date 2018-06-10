
        // ------------------------- Instruction: LUI ------------------------------ //
        {
            auto instr = model.NewInstr("LUI" NAME_SUFFIX);
            auto decode = ( opcode == LUI ) & interruptCondition() & EXEC_COND ;
            instr.SetDecode(decode);

            UPDATE_PC(nxt_pc);
            UPDATE_R( rd,  immU );
            EXECUTE_IF_SPEC;
            
            RECORD_INST("LUI" NAME_SUFFIX);
        }
        // ------------------------- Instruction: AUIPC ------------------------------ //
        {
            auto instr = model.NewInstr("AUIPC" NAME_SUFFIX) ;
            auto decode = ( opcode == AUIPC ) & interruptCondition() & EXEC_COND ;
            instr.SetDecode(decode);

            UPDATE_PC(nxt_pc);
            UPDATE_R( rd,  pc + immU ); // will be replaced with spc
            EXECUTE_IF_SPEC;
            
            RECORD_INST("AUIPC" NAME_SUFFIX);
        }