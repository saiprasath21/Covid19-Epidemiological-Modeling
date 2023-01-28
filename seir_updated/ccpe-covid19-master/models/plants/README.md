# Plants

This directory stores the plant models that were made for this research which vary in their complexity and the amount of dynamics which they can capture.
Each of these models have parameters which allow them to be configured for different populations or countries.

These plant models can be run in closed loop with a controller through the provided I/O signals.

## [PL-1](pl1.yaml)

A simple SEIR model which splits cases up by confirmed and untested cases and uses an additional pre-symptomatic case.
This model uses a single transmission rate for both confirmed and untested cases.

By default, this model is parametrised to New Zealand.

### Inputs
| Name | Type | Description |
|---|---|---|
| R0 | REAL | The reproduction number which should be applied to the model |

### Outputs
| Name | Type | Description |
|---|---|---|
| Ic | REAL | The number of confirmed (and active) cases |
| C_dot | REAL | The rate of change of cases (new cases per day) |

## [PL-2](pl2.yaml)

An extended version of `PL-1` which uses separate transmission rates for confirmed and untested cases, along with the testing rate, which allows for the modelling of enforced isolation of positive cases.

By default, this model is parametrised to New Zealand.

### Inputs
| Name | Type | Description |
|---|---|---|
| R0 | REAL | The reproduction number which should be applied to untested people in the model |
| R0c | REAL | The reproduction number which should be applied to confirmed cases in the model |
| c | REAL | Current testing rate, represented as the likelihood of an infected person being tested each day |

### Outputs
| Name | Type | Description |
|---|---|---|
| Ic | REAL | The number of confirmed (and active) cases |
| C_dot | REAL | The rate of change of cases (new cases per day) |

## [PL-3](pl3.yaml)

An extended version of `PL-2` which includes the ability to specify a date and size for a second wave of infections.

By default, this model is parametrised to New Zealand.

### Inputs
| Name | Type | Description |
|---|---|---|
| R0 | REAL | The reproduction number which should be applied to untested people in the model |
| R0c | REAL | The reproduction number which should be applied to confirmed cases in the model |
| c | REAL | Current testing rate, represented as the likelihood of an infected person being tested each day |

### Outputs
| Name | Type | Description |
|---|---|---|
| Ic | REAL | The number of confirmed (and active) cases |
| C_dot | REAL | The rate of change of cases (new cases per day) |
