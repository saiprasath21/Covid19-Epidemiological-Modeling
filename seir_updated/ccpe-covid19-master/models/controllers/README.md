# Controllers

This directory stores the controller models that were made for this research which vary in their complexity and the number of control actions which they perform.

These controller models can be run in closed loop with a plant (epidemiological) model through the provided I/O signals.

## [NZ-C1](nz-c1.yaml)

A trivial controller which transitions to a lockdown after a predefined amount of time and remains there indefinitely.

### Outputs
| Name | Type | Description |
|---|---|---|
| R0 | REAL | The reproduction number depending on which state the controller is currently in |
| Level | REAL | The control level (state) that the controller is currently in |

## [NZ-C2](nz-c2.yaml)

A controller which implements the four-level alert system of the New Zealand government.
This model transitions between the different levels (which have their own respective R0 values).

### Inputs
| Name | Type | Description |
|---|---|---|
| Ic | REAL | The current number of active cases of COVID-19 |
| C_dot | REAL | The current rate of change of new cases per day |

### Outputs
| Name | Type | Description |
|---|---|---|
| R0 | REAL | The reproduction number for **untested cases** depending on which state the controller is currently in |
| R0c | REAL | The reproduction number for **confirmed cases** depending on which state the controller is currently in |
| Level | REAL | The control level (state) that the controller is currently in |

## [NZ-C3](nz-c3.yaml)

A simplified version of the `NZ-C2` controller which consists of only two levels - no controls being implemented and a full lockdown.

### Inputs
| Name | Type | Description |
|---|---|---|
| Ic | REAL | The current number of active cases of COVID-19 |

### Outputs
| Name | Type | Description |
|---|---|---|
| R0 | REAL | The reproduction number depending on which state the controller is currently in |
| Level | REAL | The control level (state) that the controller is currently in |

## [I-C1](i-c1.yaml)

A controller which implements a four-level alert system of the Italian government.
This model transitions between the different levels (which have their own respective R0 values).

### Inputs
| Name | Type | Description |
|---|---|---|
| Ic | REAL | The current number of active cases of COVID-19 |
| C_dot | REAL | The current rate of change of new cases per day |

### Outputs
| Name | Type | Description |
|---|---|---|
| R0 | REAL | The reproduction number for **untested cases** depending on which state the controller is currently in |
| R0c | REAL | The reproduction number for **confirmed cases** depending on which state the controller is currently in |
| Phase | REAL | The control phase (state) that the controller is currently in |
