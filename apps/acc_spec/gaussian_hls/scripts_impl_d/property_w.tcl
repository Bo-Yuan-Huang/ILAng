# Assertions for proving equivalence between ILA and HLS
#
# instructions terminate
assert -name {terminate} \
{ (counter > 5) |-> (ila_complete == 0 | hls_step == 1) \
} -update_db;

assert -name {bound help 0} { counter == 0 |=> counter == 1 } -update_db;
assert -name {bound help 1} { counter == 1 |=> counter == 2 } -update_db;
assert -name {bound help 2} { counter == 2 |=> counter == 3 } -update_db;
assert -name {bound help 3} { counter == 3 |=> counter == 4 } -update_db;
assert -name {bound help 4} { counter == 4 |=> counter == 5 } -update_db;
assert -name {bound help 5} { counter == 5 |=> counter == 6 } -update_db;
assert -name {bound help 6} { counter == 6 |=> counter == 7 } -update_db;
assert -name {bound help 7} { counter == 7 |=> counter == 8 } -update_db;
assert -name {bound help 8} { counter == 8 |=> counter == 9 } -update_db;
assert -name {bound help 9} { counter == 9 |=> counter == 10 } -update_db;
assert -name {bound help 10} { counter == 10 |=> counter == 11 } -update_db;
assert -name {bound help 11} { counter == 11 |=> counter == 12 } -update_db;
assert -name {bound help 12} { counter == 12 |=> counter == 13 } -update_db;
assert -name {bound help 13} { counter == 13 |=> counter == 14 } -update_db;
assert -name {bound help 14} { counter == 14 |=> counter == 15 } -update_db;
assert -name {bound help 15} { counter == 15 |=> counter == 16 } -update_db;
assert -name {bound help 16} { counter == 16 |=> counter == 17 } -update_db;
assert -name {bound help 17} { counter == 17 |=> counter == 18 } -update_db;
assert -name {bound help 18} { counter == 18 |=> counter == 19 } -update_db;
assert -name {bound help 19} { counter == 19 |=> counter == 20 } -update_db;
assert -name {bound help 20} { counter == 20 |=> counter == 21 } -update_db;
assert -name {bound help 21} { counter == 21 |=> counter == 22 } -update_db;
assert -name {bound help 22} { counter == 22 |=> counter == 23 } -update_db;
assert -name {bound help 23} { counter == 23 |=> counter == 24 } -update_db;
assert -name {bound help 24} { counter == 24 |=> counter == 25 } -update_db;
assert -name {bound help 25} { counter == 25 |=> counter == 26 } -update_db;
assert -name {bound help 26} { counter == 26 |=> counter == 27 } -update_db;
assert -name {bound help 27} { counter == 27 |=> counter == 28 } -update_db;
assert -name {bound help 28} { counter == 28 |=> counter == 29 } -update_db;
assert -name {bound help 29} { counter == 29 |=> counter == 30 } -update_db;
assert -name {bound help 30} { counter == 30 |=> counter == 31 } -update_db;
assert -name {bound help 31} { counter == 31 |=> counter == 32 } -update_db;

assert -name {bound end} { counter == 30 |=> (counter > 30 & counter < 40) } -update_db;
assert -name {bound inv} { (counter > 30 & counter < 40) |=> (counter > 30 & counter < 40) } -update_db;
assert -name {bound - ila} { counter == 30 |-> ila_complete == 1 } -update_db;
assert -name {bound - hls} { counter == 30 |-> hls_step == 0 } -update_db;
assert -name {fix point entry - ila} { (counter > 30 & counter < 40) |-> ila_complete == 1 } -update_db;
assert -name {fix point entry - hls} { (counter > 30 & counter < 40) |-> hls_step == 0 } -update_db;
assert -name {fix point - ila} { ila_complete == 1 |=> ila_complete == 1 } -update_db;
assert -name {fix point - hls} { hls_step == 0 |=> hls_step == 0 } -update_db;

assert -name {bound dec 29 - ila} { counter == 29 |-> ila_complete == 1} -update_db;
assert -name {bound dec 28 - ila} { counter == 28 |-> ila_complete == 1} -update_db;
assert -name {bound dec 27 - ila} { counter == 27 |-> ila_complete == 1} -update_db;
assert -name {bound dec 26 - ila} { counter == 26 |-> ila_complete == 1} -update_db;
assert -name {bound dec 25 - ila} { counter == 25 |-> ila_complete == 1} -update_db;
assert -name {bound dec 24 - ila} { counter == 24 |-> ila_complete == 1} -update_db;
assert -name {bound dec 23 - ila} { counter == 23 |-> ila_complete == 1} -update_db;
assert -name {bound dec 22 - ila} { counter == 22 |-> ila_complete == 1} -update_db;
assert -name {bound dec 21 - ila} { counter == 21 |-> ila_complete == 1} -update_db;
assert -name {bound dec 20 - ila} { counter == 20 |-> ila_complete == 1} -update_db;
assert -name {bound dec 19 - ila} { counter == 19 |-> ila_complete == 1} -update_db;
assert -name {bound dec 18 - ila} { counter == 18 |-> ila_complete == 1} -update_db;
assert -name {bound dec 17 - ila} { counter == 17 |-> ila_complete == 1} -update_db;
assert -name {bound dec 16 - ila} { counter == 16 |-> ila_complete == 1} -update_db;
assert -name {bound dec 15 - ila} { counter == 15 |-> ila_complete == 1} -update_db;

assert -name {bound dec 29 - hls} { counter == 29 |-> hls_step == 0} -update_db;
assert -name {bound dec 28 - hls} { counter == 28 |-> hls_step == 0} -update_db;
assert -name {bound dec 27 - hls} { counter == 27 |-> hls_step == 0} -update_db;
assert -name {bound dec 26 - hls} { counter == 26 |-> hls_step == 0} -update_db;
assert -name {bound dec 25 - hls} { counter == 25 |-> hls_step == 0} -update_db;
assert -name {bound dec 24 - hls} { counter == 24 |-> hls_step == 0} -update_db;
assert -name {bound dec 23 - hls} { counter == 23 |-> hls_step == 0} -update_db;
assert -name {bound dec 22 - hls} { counter == 22 |-> hls_step == 0} -update_db;
assert -name {bound dec 21 - hls} { counter == 21 |-> hls_step == 0} -update_db;
assert -name {bound dec 20 - hls} { counter == 20 |-> hls_step == 0} -update_db;
assert -name {bound dec 19 - hls} { counter == 19 |-> hls_step == 0} -update_db;
assert -name {bound dec 18 - hls} { counter == 18 |-> hls_step == 0} -update_db;
assert -name {bound dec 17 - hls} { counter == 17 |-> hls_step == 0} -update_db;
assert -name {bound dec 16 - hls} { counter == 16 |-> hls_step == 0} -update_db;
assert -name {bound dec 15 - hls} { counter == 15 |-> hls_step == 0} -update_db;

#assert -name {bound help 0} \
{ counter == 0 |=> \
  counter == 1 |=> \
  counter == 2 |=> \
  counter == 3 |=> \
  counter == 4 |=> \
  counter == 5 |=> \
  counter == 6 |=> \
  counter == 7 |=> \
  counter == 8 |=> \
  counter == 9 |=> \
  counter == 10 } -update_db;
#
#assert -name {bound help 1} \
{ counter == 10 |=> \
  counter == 11 |=> \
  counter == 12 |=> \
  counter == 13 |=> \
  counter == 14 |=> \
  counter == 15 |=> \
  counter == 16 |=> \
  counter == 17 |=> \
  counter == 18 |=> \
  counter == 19 |=> \
  counter == 20 } -update_db;
#
#assert -name {bound help 2} \
{ counter == 20 |=> \
  counter == 21 |=> \
  counter == 22 |=> \
  counter == 23 |=> \
  counter == 24 |=> \
  counter == 25 |=> \
  counter == 26 |=> \
  counter == 27 |=> \
  counter == 28 |=> \
  counter == 29 |=> \
  counter == 30 } -update_db;
#

# equivalence on arch states
# arg_1_TREADY
assert -name {eq - arg_1_TREADY} \
{ (counter == 30) |-> ( \
    ila_U.arg_1_TREADY == hls_U.arg_1_TREADY \
) } -update_db;

# arg_0_TVALID
assert -name {eq - arg_0_TVALID} \
{ (counter == 30) |-> ( \
    ila_U.arg_0_TVALID == hls_U.arg_0_TVALID \
) } -update_db;

# LB1D_p_cnt
assert -name {eq - LB1D_p_cnt} \
{ (counter == 30) |-> ( \
    ila_LB1D_p_cnt == hls_LB1D_p_cnt \
) } -update_db;

# in_stream_empty
assert -name {eq - in_stream_empty} \
{ (counter == 30) |-> ( \
    ila_in_stream_empty == hls_in_stream_empty \
) } -update_db;

# in_stream_full
assert -name {eq - in_stream_full} \
{ (counter == 30) |-> ( \
    ila_in_stream_full == hls_in_stream_full \
) } -update_db;

# LB2D_proc_x
assert -name {eq - LB2D_proc_x} \
{ (counter == 30) |-> ( \
    ila_LB2D_proc_x == hls_LB2D_proc_x \
) } -update_db;

# LB2D_proc_y
assert -name {eq - LB2D_proc_y} \
{ (counter == 30) |-> ( \
    ila_LB2D_proc_y == hls_LB2D_proc_y \
) } -update_db;

# LB2D_proc_w
assert -name {eq - LB2D_proc_w} \
{ (counter == 30) |-> ( \
    ila_LB2D_proc_w == hls_LB2D_proc_w \
) } -update_db;

# slice_stream_empty
assert -name {eq - slice_stream_empty} \
{ (counter == 30) |-> ( \
    ila_slice_stream_empty == hls_slice_stream_empty \
) } -update_db;

# slice_stream_full
assert -name {eq - slice_stream_full} \
{ (counter == 30) |-> ( \
    ila_slice_stream_full == hls_slice_stream_full \
) } -update_db;

# LB2D_shift_x
assert -name {eq - LB2D_shift_x} \
{ (counter == 30) |-> ( \
    ila_LB2D_shift_x == hls_LB2D_shift_x \
) } -update_db;

# LB2D_shift_y
assert -name {eq - LB2D_shift_y} \
{ (counter == 30) |-> ( \
    ila_LB2D_shift_y == hls_LB2D_shift_y \
) } -update_db;

# stencil_stream_empty
assert -name {eq - stencil_stream_empty} \
{ (counter == 30) |-> ( \
    ila_stencil_stream_empty == hls_stencil_stream_empty \
) } -update_db;

# stencil_stream_full
assert -name {eq - stencil_stream_full} \
{ (counter == 30) |-> ( \
    ila_stencil_stream_full == hls_stencil_stream_full \
) } -update_db;

# pp it
assert -name {eq - pp_it_1} \
{ (counter == 30) |-> ( \
    ila_gb_pp_it_1 == hls_gb_pp_it_1 \
) } -update_db;
#
assert -name {eq - pp_it_2} \
{ (counter == 30) |-> ( \
    ila_gb_pp_it_2 == hls_gb_pp_it_2 \
) } -update_db;
#
assert -name {eq - pp_it_3} \
{ (counter == 30) |-> ( \
    ila_gb_pp_it_3 == hls_gb_pp_it_3 \
) } -update_db;
#
assert -name {eq - pp_it_4} \
{ (counter == 30) |-> ( \
    ila_gb_pp_it_4 == hls_gb_pp_it_4 \
) } -update_db;
#
assert -name {eq - pp_it_5} \
{ (counter == 30) |-> ( \
    ila_gb_pp_it_5 == hls_gb_pp_it_5 \
) } -update_db;
#
assert -name {eq - pp_it_6} \
{ (counter == 30) |-> ( \
    ila_gb_pp_it_6 == hls_gb_pp_it_6 \
) } -update_db;
#
assert -name {eq - pp_it_7} \
{ (counter == 30) |-> ( \
    ila_gb_pp_it_7 == hls_gb_pp_it_7 \
) } -update_db;
#
assert -name {eq - pp_it_8} \
{ (counter == 30) |-> ( \
    ila_gb_pp_it_8 == hls_gb_pp_it_8 \
) } -update_db;
#
assert -name {eq - pp_it_9} \
{ (counter == 30) |-> ( \
    ila_gb_pp_it_9 == hls_gb_pp_it_9 \
) } -update_db;

# exit it
assert -name {eq - exit_it_1} \
{ (counter == 30) |-> ( \
    ila_gb_exit_it_1 == hls_gb_exit_it_1 \
) } -update_db;
#
assert -name {eq - exit_it_2} \
{ (counter == 30) |-> ( \
    ila_gb_exit_it_2 == hls_gb_exit_it_2 \
) } -update_db;
#
assert -name {eq - exit_it_3} \
{ (counter == 30) |-> ( \
    ila_gb_exit_it_3 == hls_gb_exit_it_3 \
) } -update_db;
#
assert -name {eq - exit_it_4} \
{ (counter == 30) |-> ( \
    ila_gb_exit_it_4 == hls_gb_exit_it_4 \
) } -update_db;
#
assert -name {eq - exit_it_5} \
{ (counter == 30) |-> ( \
    ila_gb_exit_it_5 == hls_gb_exit_it_5 \
) } -update_db;
#
assert -name {eq - exit_it_6} \
{ (counter == 30) |-> ( \
    ila_gb_exit_it_6 == hls_gb_exit_it_6 \
) } -update_db;
#
assert -name {eq - exit_it_7} \
{ (counter == 30) |-> ( \
    ila_gb_exit_it_7 == hls_gb_exit_it_7 \
) } -update_db;
#
assert -name {eq - LB1D_in} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
   hls_U.hls_target_linebuffer_1_U0.hls_target_linebuffer_Loop_1_proc_U0.in_axi_stream_V_value_V_0_has_vld_data_reg == 1 ) |-> ( \
    ila_LB1D_in == hls_LB1D_in \
) } -update_db;
#
assert -name {eq - LB1D_buff} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_LB1D_buff == hls_LB1D_buff \
) } -update_db;
#
assert -name {eq - in_stream_buff_0} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_in_stream_buff_0 == hls_in_stream_buff_0 \
) } -update_db;
#
assert -name {eq - in_stream_buff_1} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_in_stream_buff_1 == hls_in_stream_buff_1 \
) } -update_db;
#
assert -name {eq - slice_stream_buff_0} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_slice_stream_buff_0 == hls_slice_stream_buff_0 \
) } -update_db;
#
assert -name {eq - slice_stream_buff_1} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_slice_stream_buff_1 == hls_slice_stream_buff_1 \
) } -update_db;
#
assert -name {eq - stencil_stream_buff_0} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_stencil_stream_buff_0 == hls_stencil_stream_buff_0 \
) } -update_db;
#
assert -name {eq - stencil_stream_buff_1} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_stencil_stream_buff_1 == hls_stencil_stream_buff_1 \
) } -update_db;
#
assert -name {eq - LB2D_shift_0} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_LB2D_shift_0 == hls_LB2D_shift_0 \
) } -update_db;
#
assert -name {eq - LB2D_shift_1} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_LB2D_shift_1 == hls_LB2D_shift_1 \
) } -update_db;
#
assert -name {eq - LB2D_shift_2} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_LB2D_shift_2 == hls_LB2D_shift_2 \
) } -update_db;
#
assert -name {eq - LB2D_shift_3} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_LB2D_shift_3 == hls_LB2D_shift_3 \
) } -update_db;
#
assert -name {eq - LB2D_shift_4} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_LB2D_shift_4 == hls_LB2D_shift_4 \
) } -update_db;
#
assert -name {eq - LB2D_shift_5} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_LB2D_shift_5 == hls_LB2D_shift_5 \
) } -update_db;
#
assert -name {eq - LB2D_shift_6} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_LB2D_shift_6 == hls_LB2D_shift_6 \
) } -update_db;
#
assert -name {eq - LB2D_shift_7} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_LB2D_shift_7 == hls_LB2D_shift_7 \
) } -update_db;
#
assert -name {eq - arg_0_TDATA} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0 & ila_arg_0_TVALID == 1 & hls_arg_0_TVALID == 1) |-> ( \
    ila_arg_0_TDATA == hls_arg_0_TDATA \
) } -update_db;
#
assert -name {eq - LB2D_proc_0} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_U.LB2D_proc_0 == hls_LB2D_proc_0 \
) } -update_db;
#
assert -name {eq - LB2D_proc_1} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_U.LB2D_proc_1 == hls_LB2D_proc_1 \
) } -update_db;
#
assert -name {eq - LB2D_proc_2} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_U.LB2D_proc_2 == hls_LB2D_proc_2 \
) } -update_db;
#
assert -name {eq - LB2D_proc_3} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_U.LB2D_proc_3 == hls_LB2D_proc_3 \
) } -update_db;
#
assert -name {eq - LB2D_proc_4} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_U.LB2D_proc_4 == hls_LB2D_proc_4 \
) } -update_db;
#
assert -name {eq - LB2D_proc_5} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_U.LB2D_proc_5 == hls_LB2D_proc_5 \
) } -update_db;
#
assert -name {eq - LB2D_proc_6} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_U.LB2D_proc_6 == hls_LB2D_proc_6 \
) } -update_db;
#
assert -name {eq - LB2D_proc_7} \
{ (counter > 5 & ila_complete == 1 & hls_step == 0) |-> ( \
    ila_U.LB2D_proc_7 == hls_LB2D_proc_7 \
) } -update_db;
