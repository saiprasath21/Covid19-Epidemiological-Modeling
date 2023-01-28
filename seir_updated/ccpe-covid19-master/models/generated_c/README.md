# Generated C

Pre-generated software code for running the associated models.
This is provided in order to allow for using these models without a need for the HAML compiler.
Please see the [Systems](../systems) for more information about the operation of each of these.

*Please note that the HAML files are the definitive source of information on this work.*
*These files may be out of date.*

## Running the models

Each of the models can be compiled by simply running `make` in the respective directory.
This will generate a binary which matches the system name and can then be executed.

For example, `./nz_c1` inside the [NZ-C1](nz-c1) directory will run that model and generate an output CSV in a file named `out.csv`.