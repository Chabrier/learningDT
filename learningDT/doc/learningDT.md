The package **learningDT** is a track of the learning of the DT foralism.
It does provide a list of User Stories. Each User Story does match a simulator tested

### Use case OO: simulator00.vpz is a kind of hello world DT simulator

This a  very simple simulator with a single DT atomic model with a single variable varA.

The compute function :

```
    varA = varA(-1) + 1;
```

* The **varA** variable is initialized by the port paramater **init_value_varA**
* The **time_step** port parameter is also used.
* The **varA** is observed using the **varA** observation port.

### Use case O1: meteoSolo.vpz