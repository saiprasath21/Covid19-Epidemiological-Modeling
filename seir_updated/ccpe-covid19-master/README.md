# Compositional Epidemiology of COVID-19

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.4033967.svg)](https://doi.org/10.5281/zenodo.4033967)

This repository contains the models and data used for our work on modelling COVID-19 in a compositional manner.

This work combined existing work on SEIR modelling for COVID-19 with controller models which captured government interventions.
This allows for the evaluation of complex control strategies in closed loop with epidemiological models.

## Models
Each of the models used in this work can be found in the [models](models) directory.
For this we provide a set of epidemiological models and controllers for New Zealand and Italy in [HAML](https://github.com/PRETgroup/modular-code-generation/blob/master/specs/HAML.md).
To run these models, please follow the steps for our compiler of these models [Modular Code Generation](https://github.com/PRETgroup/modular-code-generation)

## Data
Pre-computed data for each of the models is available in the [data](data) directory.
Each of these are presented as a CSV file with fields that correspond to the SEIR model.
