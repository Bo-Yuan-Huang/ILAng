# ILA for Halide Gaussian Blur (GB) accelerator that abstracts buffering.
# write instruction - child-instruction 1

import ila

from gb_arch import GBArch

# Define next state functions for child-instruction 1
def WRU1 (gb):
    m = gb.abst

    READY_T     = gb.READY_TRUE
    READY_F     = gb.READY_FALSE
    VALID_T     = gb.VALID_TRUE
    VALID_F     = gb.VALID_FALSE
    DATA_SIZE   = gb.DATA_SIZE

    decode = (gb.arg_1_TREADY == READY_F) & \
             (gb.arg_0_TVALID == VALID_F) & \
             (gb.arg_0_TREADY == READY_F)

    # next state functions for child-states
    def genRows (idx):
        l = gb.DATA_SIZE * idx
        h = l + DATA_SIZE - 1
        res = ila.concat ([gb.stencil[8] [h:l],
                           gb.stencil[7] [h:l],
                           gb.stencil[6] [h:l],
                           gb.stencil[5] [h:l],
                           gb.stencil[4] [h:l],
                           gb.stencil[3] [h:l],
                           gb.stencil[2] [h:l],
                           gb.stencil[1] [h:l],
                           gb.stencil[0] [h:l]])
        return res

    stencil_rows = []
    for i in xrange (gb.stencil_size-1, -1, -1):
        stencil_rows.append (genRows (i))

    proc_in_nxt = ila.ite (gb.RAM_x > gb.stencil_size,
                           ila.concat (stencil_rows),
                           gb.proc_in)
    gb.proc_in_nxt = ila.ite (decode, proc_in_nxt, gb.proc_in_nxt)

    # next state functions for output ports
    arg_1_TREADY_nxt = READY_T
    gb.arg_1_TREADY_nxt = ila.ite (decode, arg_1_TREADY_nxt, gb.arg_1_TREADY_nxt)

    arg_0_TVALID_nxt = ila.ite (gb.RAM_x > gb.stencil_size - 1,
                                VALID_T, VALID_F)
    gb.arg_0_TVALID_nxt = ila.ite (decode, arg_0_TVALID_nxt, gb.arg_0_TVALID_nxt)

    arg_0_TDATA_nxt = ila.appfun (gb.fun, proc_in_nxt)
    gb.arg_0_TDATA_nxt = ila.ite (decode, arg_0_TDATA_nxt, gb.arg_0_TDATA_nxt)

    # next state functions for internal arch-states
    gb.RAM_x_nxt = ila.ite (decode, gb.RAM_x, gb.RAM_x_nxt)
    gb.RAM_y_nxt = ila.ite (decode, gb.RAM_y, gb.RAM_y_nxt)
    gb.RAM_w_nxt = ila.ite (decode, gb.RAM_w, gb.RAM_w_nxt)

    for i in xrange (0, gb.RAM_size):
        gb.RAM_nxt[i] = ila.ite (decode, gb.RAM[i], gb.RAM_nxt[i])

    for i in xrange (0, gb.stencil_size-1):
        stencil_i_nxt = ila.ite (gb.RAM_y < gb.RAM_size,
                                 gb.stencil[i],
                                 gb.stencil[i+1])
        gb.stencil_nxt[i] = ila.ite (decode, stencil_i_nxt, gb.stencil_nxt[i])

    n = gb.stencil_size - 1
    stencil_n_nxt = gb.stencil[n]
    gb.stencil_nxt[n] = ila.ite (decode, stencil_n_nxt, gb.stencil_nxt[n])

