#!/bin/sh


# Attach Vbuddy USB
~/Documents/iac/lab0-devtools/tools/attach_usb.sh

# Cleanup old files
rm -rf obj_dir
rm -f f1_fsm.vcd

# Run Verilator to translate Verilog + testbench to C++
# Note: Make sure f1_fsm_tb.cpp is in the SAME directory as this script.
verilator -Wall --cc --trace f1_fsm.sv --exe f1_fsm_tb.cpp

# Build the C++ executable (Verilator auto-generates the makefile)
make -j -C obj_dir -f Vf1_fsm.mk Vf1_fsm

# Run simulation (Vbuddy must already be attached)
./obj_dir/Vf1_fsm
