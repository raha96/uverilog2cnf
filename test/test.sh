mkdir test_out
../build/uverilog2cnf -v comparator_debug.v -l gtechsubset.cnflib -s ce.sol -d cardinality.card -m test_out/ -c test_out/
