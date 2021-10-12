// Automatically modified by insert_gate.py

module comparator (_mux_sel_u0_, _A_1_, _u0_1_Z_mux_input_, _A_2_, _u0_2_Z_mux_input_, _A_3_, 
	_u0_3_Z_mux_input_, _mux_sel_u1_, _nt1_1_, _B_1_, _u1_1_Z_mux_input_, _nt1_2_, 
	_B_2_, _u1_2_Z_mux_input_, _nt1_3_, _B_3_, _u1_3_Z_mux_input_, _mux_sel_u2_, 
	_A_1_, _B_1_, _u2_1_Z_mux_input_, _A_2_, _B_2_, _u2_2_Z_mux_input_, 
	_A_3_, _B_3_, _u2_3_Z_mux_input_, _mux_sel_u3_, _tmp2_1_, _L_1_, 
	_u3_1_Z_mux_input_, _tmp2_2_, _L_2_, _u3_2_Z_mux_input_, _tmp2_3_, _L_3_, 
	_u3_3_Z_mux_input_, _mux_sel_u4_, _tmp1_1_, _tmp3_1_, _u4_1_Z_mux_input_, _tmp1_2_, 
	_tmp3_2_, _u4_2_Z_mux_input_, _tmp1_3_, _tmp3_3_, _u4_3_Z_mux_input_, _mux_sel_u6_, 
	_tmp2_1_, _E_1_, _u6_1_Z_mux_input_, _tmp2_2_, _E_2_, _u6_2_Z_mux_input_, 
	_tmp2_3_, _E_3_, _u6_3_Z_mux_input_, _mux_sel_u7_, _B_1_, _u7_1_Z_mux_input_, 
	_B_2_, _u7_2_Z_mux_input_, _B_3_, _u7_3_Z_mux_input_, _mux_sel_u8_, _A_1_, 
	_nt2_1_, _u8_1_Z_mux_input_, _A_2_, _nt2_2_, _u8_2_Z_mux_input_, _A_3_, 
	_nt2_3_, _u8_3_Z_mux_input_, _mux_sel_u10_, _tmp2_1_, _G_1_, _u10_1_Z_mux_input_, 
	_tmp2_2_, _G_2_, _u10_2_Z_mux_input_, _tmp2_3_, _G_3_, _u10_3_Z_mux_input_, 
	_mux_sel_u11_, _tmp5_1_, _tmp7_1_, _u11_1_Z_mux_input_, _tmp5_2_, _tmp7_2_, 
	_u11_2_Z_mux_input_, _tmp5_3_, _tmp7_3_, _u11_3_Z_mux_input_, _A_le_B_1_, _A_le_B_2_, 
	_A_le_B_3_, _A_equal_B_1_, _A_equal_B_2_, _A_equal_B_3_, _A_greater_B_1_, _A_greater_B_2_, 
	_A_greater_B_3_);

input _mux_sel_u0_, _A_1_, _u0_1_Z_mux_input_, _A_2_, 
	_u0_2_Z_mux_input_, _A_3_, _u0_3_Z_mux_input_, _mux_sel_u1_, 
	_nt1_1_, _B_1_, _u1_1_Z_mux_input_, _nt1_2_, 
	_B_2_, _u1_2_Z_mux_input_, _nt1_3_, _B_3_, 
	_u1_3_Z_mux_input_, _mux_sel_u2_, _A_1_, _B_1_, 
	_u2_1_Z_mux_input_, _A_2_, _B_2_, _u2_2_Z_mux_input_, 
	_A_3_, _B_3_, _u2_3_Z_mux_input_, _mux_sel_u3_, 
	_tmp2_1_, _L_1_, _u3_1_Z_mux_input_, _tmp2_2_, 
	_L_2_, _u3_2_Z_mux_input_, _tmp2_3_, _L_3_, 
	_u3_3_Z_mux_input_, _mux_sel_u4_, _tmp1_1_, _tmp3_1_, 
	_u4_1_Z_mux_input_, _tmp1_2_, _tmp3_2_, _u4_2_Z_mux_input_, 
	_tmp1_3_, _tmp3_3_, _u4_3_Z_mux_input_, _mux_sel_u6_, 
	_tmp2_1_, _E_1_, _u6_1_Z_mux_input_, _tmp2_2_, 
	_E_2_, _u6_2_Z_mux_input_, _tmp2_3_, _E_3_, 
	_u6_3_Z_mux_input_, _mux_sel_u7_, _B_1_, _u7_1_Z_mux_input_, 
	_B_2_, _u7_2_Z_mux_input_, _B_3_, _u7_3_Z_mux_input_, 
	_mux_sel_u8_, _A_1_, _nt2_1_, _u8_1_Z_mux_input_, 
	_A_2_, _nt2_2_, _u8_2_Z_mux_input_, _A_3_, 
	_nt2_3_, _u8_3_Z_mux_input_, _mux_sel_u10_, _tmp2_1_, 
	_G_1_, _u10_1_Z_mux_input_, _tmp2_2_, _G_2_, 
	_u10_2_Z_mux_input_, _tmp2_3_, _G_3_, _u10_3_Z_mux_input_, 
	_mux_sel_u11_, _tmp5_1_, _tmp7_1_, _u11_1_Z_mux_input_, 
	_tmp5_2_, _tmp7_2_, _u11_2_Z_mux_input_, _tmp5_3_, 
	_tmp7_3_, _u11_3_Z_mux_input_;
output _A_le_B_1_, _A_le_B_2_, _A_le_B_3_, _A_equal_B_1_, 
	_A_equal_B_2_, _A_equal_B_3_, _A_greater_B_1_, _A_greater_B_2_, 
	_A_greater_B_3_;
wire _nt1_1_, _nt1_1__debug_, _nt1_2_, _nt1_2__debug_, 
	_nt1_3_, _nt1_3__debug_, _tmp1_1_, _tmp1_1__debug_, 
	_tmp1_2_, _tmp1_2__debug_, _tmp1_3_, _tmp1_3__debug_, 
	_tmp2_1_, _tmp2_1__debug_, _tmp2_2_, _tmp2_2__debug_, 
	_tmp2_3_, _tmp2_3__debug_, _tmp3_1_, _tmp3_1__debug_, 
	_tmp3_2_, _tmp3_2__debug_, _tmp3_3_, _tmp3_3__debug_, 
	_A_le_B_1__debug_, _A_le_B_2__debug_, _A_le_B_3__debug_, _A_equal_B_1__debug_, 
	_A_equal_B_2__debug_, _A_equal_B_3__debug_, _nt2_1_, _nt2_1__debug_, 
	_nt2_2_, _nt2_2__debug_, _nt2_3_, _nt2_3__debug_, 
	_tmp5_1_, _tmp5_1__debug_, _tmp5_2_, _tmp5_2__debug_, 
	_tmp5_3_, _tmp5_3__debug_, _tmp7_1_, _tmp7_1__debug_, 
	_tmp7_2_, _tmp7_2__debug_, _tmp7_3_, _tmp7_3__debug_, 
	_A_greater_B_1__debug_, _A_greater_B_2__debug_, _A_greater_B_3__debug_;

GTECH_MUX2 _debug_mux_inst_u0_Z_1_ (.A(_nt1_1__debug_), .B(_u0_1_Z_mux_input_), .S(_mux_sel_u0_), 
	.Z(_nt1_1_));
GTECH_NOT _u0_copy_1_ (.A(_A_1_), .Z(_nt1_1__debug_));
GTECH_MUX2 _debug_mux_inst_u0_Z_2_ (.A(_nt1_2__debug_), .B(_u0_2_Z_mux_input_), .S(_mux_sel_u0_), 
	.Z(_nt1_2_));
GTECH_NOT _u0_copy_2_ (.A(_A_2_), .Z(_nt1_2__debug_));
GTECH_MUX2 _debug_mux_inst_u0_Z_3_ (.A(_nt1_3__debug_), .B(_u0_3_Z_mux_input_), .S(_mux_sel_u0_), 
	.Z(_nt1_3_));
GTECH_NOT _u0_copy_3_ (.A(_A_3_), .Z(_nt1_3__debug_));
GTECH_MUX2 _debug_mux_inst_u1_Z_1_ (.A(_tmp1_1__debug_), .B(_u1_1_Z_mux_input_), .S(_mux_sel_u1_), 
	.Z(_tmp1_1_));
GTECH_AND2 _u1_copy_1_ (.A(_nt1_1_), .B(_B_1_), .Z(_tmp1_1__debug_));
GTECH_MUX2 _debug_mux_inst_u1_Z_2_ (.A(_tmp1_2__debug_), .B(_u1_2_Z_mux_input_), .S(_mux_sel_u1_), 
	.Z(_tmp1_2_));
GTECH_AND2 _u1_copy_2_ (.A(_nt1_2_), .B(_B_2_), .Z(_tmp1_2__debug_));
GTECH_MUX2 _debug_mux_inst_u1_Z_3_ (.A(_tmp1_3__debug_), .B(_u1_3_Z_mux_input_), .S(_mux_sel_u1_), 
	.Z(_tmp1_3_));
GTECH_AND2 _u1_copy_3_ (.A(_nt1_3_), .B(_B_3_), .Z(_tmp1_3__debug_));
GTECH_MUX2 _debug_mux_inst_u2_Z_1_ (.A(_tmp2_1__debug_), .B(_u2_1_Z_mux_input_), .S(_mux_sel_u2_), 
	.Z(_tmp2_1_));
GTECH_XNOR2 _u2_copy_1_ (.A(_A_1_), .B(_B_1_), .Z(_tmp2_1__debug_));
GTECH_MUX2 _debug_mux_inst_u2_Z_2_ (.A(_tmp2_2__debug_), .B(_u2_2_Z_mux_input_), .S(_mux_sel_u2_), 
	.Z(_tmp2_2_));
GTECH_XNOR2 _u2_copy_2_ (.A(_A_2_), .B(_B_2_), .Z(_tmp2_2__debug_));
GTECH_MUX2 _debug_mux_inst_u2_Z_3_ (.A(_tmp2_3__debug_), .B(_u2_3_Z_mux_input_), .S(_mux_sel_u2_), 
	.Z(_tmp2_3_));
GTECH_XNOR2 _u2_copy_3_ (.A(_A_3_), .B(_B_3_), .Z(_tmp2_3__debug_));
GTECH_MUX2 _debug_mux_inst_u3_Z_1_ (.A(_tmp3_1__debug_), .B(_u3_1_Z_mux_input_), .S(_mux_sel_u3_), 
	.Z(_tmp3_1_));
GTECH_XNOR2 _u3_copy_1_ (.A(_tmp2_1_), .B(_L_1_), .Z(_tmp3_1__debug_));
GTECH_MUX2 _debug_mux_inst_u3_Z_2_ (.A(_tmp3_2__debug_), .B(_u3_2_Z_mux_input_), .S(_mux_sel_u3_), 
	.Z(_tmp3_2_));
GTECH_XNOR2 _u3_copy_2_ (.A(_tmp2_2_), .B(_L_2_), .Z(_tmp3_2__debug_));
GTECH_MUX2 _debug_mux_inst_u3_Z_3_ (.A(_tmp3_3__debug_), .B(_u3_3_Z_mux_input_), .S(_mux_sel_u3_), 
	.Z(_tmp3_3_));
GTECH_XNOR2 _u3_copy_3_ (.A(_tmp2_3_), .B(_L_3_), .Z(_tmp3_3__debug_));
GTECH_MUX2 _debug_mux_inst_u4_Z_1_ (.A(_A_le_B_1__debug_), .B(_u4_1_Z_mux_input_), .S(_mux_sel_u4_), 
	.Z(_A_le_B_1_));
GTECH_OR2 _u4_copy_1_ (.A(_tmp1_1_), .B(_tmp3_1_), .Z(_A_le_B_1__debug_));
GTECH_MUX2 _debug_mux_inst_u4_Z_2_ (.A(_A_le_B_2__debug_), .B(_u4_2_Z_mux_input_), .S(_mux_sel_u4_), 
	.Z(_A_le_B_2_));
GTECH_OR2 _u4_copy_2_ (.A(_tmp1_2_), .B(_tmp3_2_), .Z(_A_le_B_2__debug_));
GTECH_MUX2 _debug_mux_inst_u4_Z_3_ (.A(_A_le_B_3__debug_), .B(_u4_3_Z_mux_input_), .S(_mux_sel_u4_), 
	.Z(_A_le_B_3_));
GTECH_OR2 _u4_copy_3_ (.A(_tmp1_3_), .B(_tmp3_3_), .Z(_A_le_B_3__debug_));
GTECH_MUX2 _debug_mux_inst_u6_Z_1_ (.A(_A_equal_B_1__debug_), .B(_u6_1_Z_mux_input_), .S(_mux_sel_u6_), 
	.Z(_A_equal_B_1_));
GTECH_AND2 _u6_copy_1_ (.A(_tmp2_1_), .B(_E_1_), .Z(_A_equal_B_1__debug_));
GTECH_MUX2 _debug_mux_inst_u6_Z_2_ (.A(_A_equal_B_2__debug_), .B(_u6_2_Z_mux_input_), .S(_mux_sel_u6_), 
	.Z(_A_equal_B_2_));
GTECH_AND2 _u6_copy_2_ (.A(_tmp2_2_), .B(_E_2_), .Z(_A_equal_B_2__debug_));
GTECH_MUX2 _debug_mux_inst_u6_Z_3_ (.A(_A_equal_B_3__debug_), .B(_u6_3_Z_mux_input_), .S(_mux_sel_u6_), 
	.Z(_A_equal_B_3_));
GTECH_AND2 _u6_copy_3_ (.A(_tmp2_3_), .B(_E_3_), .Z(_A_equal_B_3__debug_));
GTECH_MUX2 _debug_mux_inst_u7_Z_1_ (.A(_nt2_1__debug_), .B(_u7_1_Z_mux_input_), .S(_mux_sel_u7_), 
	.Z(_nt2_1_));
GTECH_NOT _u7_copy_1_ (.A(_B_1_), .Z(_nt2_1__debug_));
GTECH_MUX2 _debug_mux_inst_u7_Z_2_ (.A(_nt2_2__debug_), .B(_u7_2_Z_mux_input_), .S(_mux_sel_u7_), 
	.Z(_nt2_2_));
GTECH_NOT _u7_copy_2_ (.A(_B_2_), .Z(_nt2_2__debug_));
GTECH_MUX2 _debug_mux_inst_u7_Z_3_ (.A(_nt2_3__debug_), .B(_u7_3_Z_mux_input_), .S(_mux_sel_u7_), 
	.Z(_nt2_3_));
GTECH_NOT _u7_copy_3_ (.A(_B_3_), .Z(_nt2_3__debug_));
GTECH_MUX2 _debug_mux_inst_u8_Z_1_ (.A(_tmp5_1__debug_), .B(_u8_1_Z_mux_input_), .S(_mux_sel_u8_), 
	.Z(_tmp5_1_));
GTECH_AND2 _u8_copy_1_ (.A(_A_1_), .B(_nt2_1_), .Z(_tmp5_1__debug_));
GTECH_MUX2 _debug_mux_inst_u8_Z_2_ (.A(_tmp5_2__debug_), .B(_u8_2_Z_mux_input_), .S(_mux_sel_u8_), 
	.Z(_tmp5_2_));
GTECH_AND2 _u8_copy_2_ (.A(_A_2_), .B(_nt2_2_), .Z(_tmp5_2__debug_));
GTECH_MUX2 _debug_mux_inst_u8_Z_3_ (.A(_tmp5_3__debug_), .B(_u8_3_Z_mux_input_), .S(_mux_sel_u8_), 
	.Z(_tmp5_3_));
GTECH_AND2 _u8_copy_3_ (.A(_A_3_), .B(_nt2_3_), .Z(_tmp5_3__debug_));
GTECH_MUX2 _debug_mux_inst_u10_Z_1_ (.A(_tmp7_1__debug_), .B(_u10_1_Z_mux_input_), .S(_mux_sel_u10_), 
	.Z(_tmp7_1_));
GTECH_AND2 _u10_copy_1_ (.A(_tmp2_1_), .B(_G_1_), .Z(_tmp7_1__debug_));
GTECH_MUX2 _debug_mux_inst_u10_Z_2_ (.A(_tmp7_2__debug_), .B(_u10_2_Z_mux_input_), .S(_mux_sel_u10_), 
	.Z(_tmp7_2_));
GTECH_AND2 _u10_copy_2_ (.A(_tmp2_2_), .B(_G_2_), .Z(_tmp7_2__debug_));
GTECH_MUX2 _debug_mux_inst_u10_Z_3_ (.A(_tmp7_3__debug_), .B(_u10_3_Z_mux_input_), .S(_mux_sel_u10_), 
	.Z(_tmp7_3_));
GTECH_AND2 _u10_copy_3_ (.A(_tmp2_3_), .B(_G_3_), .Z(_tmp7_3__debug_));
GTECH_MUX2 _debug_mux_inst_u11_Z_1_ (.A(_A_greater_B_1__debug_), .B(_u11_1_Z_mux_input_), .S(_mux_sel_u11_), 
	.Z(_A_greater_B_1_));
GTECH_OR2 _u11_copy_1_ (.A(_tmp5_1_), .B(_tmp7_1_), .Z(_A_greater_B_1__debug_));
GTECH_MUX2 _debug_mux_inst_u11_Z_2_ (.A(_A_greater_B_2__debug_), .B(_u11_2_Z_mux_input_), .S(_mux_sel_u11_), 
	.Z(_A_greater_B_2_));
GTECH_OR2 _u11_copy_2_ (.A(_tmp5_2_), .B(_tmp7_2_), .Z(_A_greater_B_2__debug_));
GTECH_MUX2 _debug_mux_inst_u11_Z_3_ (.A(_A_greater_B_3__debug_), .B(_u11_3_Z_mux_input_), .S(_mux_sel_u11_), 
	.Z(_A_greater_B_3_));
GTECH_OR2 _u11_copy_3_ (.A(_tmp5_3_), .B(_tmp7_3_), .Z(_A_greater_B_3__debug_));

endmodule

