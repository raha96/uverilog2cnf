module comparator (...);

input _mux_sel_u0_, _A_1_, ...;
output _A_le_B_1_, ...;
wire _nt1_1_, ...;

GTECH_MUX2 _debug_mux_inst_u0_Z_1_ (.A(_nt1_1__debug_), .B(_u0_1_Z_mux_input_), .S(_mux_sel_u0_), 
	.Z(_nt1_1_));
GTECH_NOT _u0_copy_1_ (.A(_A_1_), .Z(_nt1_1__debug_));
GTECH_AND2 _u1_copy_1_ (.A(_nt1_1_), .B(_B_1_), .Z(_tmp1_1__debug_));
GTECH_XNOR2 _u2_copy_1_ (.A(_A_1_), .B(_B_1_), .Z(_tmp2_1__debug_));
GTECH_OR2 _u4_copy_1_ (.A(_tmp1_1_), .B(_tmp3_1_), .Z(_A_le_B_1__debug_));

endmodule
