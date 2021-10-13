# uverilog2cnf

This tool is intended for converting gate-level Verilog netlists to CNF format, suitable for 
SAT solvers. The main use case is debugging, for which a sample command, along with sample files 
are available in `test` directory. 

**NOTE**: Currently the authoritative manual is the Persian manual and api manual included in the `doc` folder. 
The English version is incomplete. In case of any questions, feel free to contact me: `raham9619@gmail.com`. 
I might be able to spare the time to translate the manual, but currently do not intend to do so. If you need it, 
contact me and I'll try to help. Like any other opensource project, any contribution is greatly appreciated ;)

## Build Instructions

    make linux
    make windows
    make docs

For other choices, refer to the `Makefile`.

## License

GPL3
