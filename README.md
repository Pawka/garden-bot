# Yet Another Garden Bot

## Tasks
- Monitor moisture.
- Monitor light period.
- Monitor temperature.
- Collect data.

## Interface

Controller can send and receive data via serial interface. Below is provided commands reference.

### Input

Input command format: ``XXX;Y``. Where ``XXX`` is command name (must be 3 symbols) and ``Y`` is value. Value is not required. If value is not provided, command must be follwed with semi colon symbol still.

Commands:
* ``NFO;`` Display expanded status of controller including timeout and moisture edge values.
* ``TIM;XX`` Change timeout value. Timeout defines how often stats are provided from controller via serial. ``XX`` - number of seconds.
* ``MOI;XX`` Change moisture edge value. Moisture indication LED is switched on when moisture drops below this value.

### Output

Stats data is provided in following format: ```DAT;AA;BB;CC```

* ``AA`` - Moisture level.
* ``BB`` - Light level.
* ``CC`` - Temperature in celsius.
