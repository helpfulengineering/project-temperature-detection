# Requirements list

## High level
|Id|Category|Subject|Description|
|-|-|-|-|
|G001|General| Detect person presence| Detect the presence of a person subject to a measurement|
|G002|General| Detect person presence| Differentiate passerby to people wanting to be temperature checked|
|G003|General| Enable the person to be at good distance|Provide feedback to the person so as to enable to have an appropriate location regarding the sensor|
|G004|General| Check temperature| Check temperature of the person against a referential of acceptable/warning/critic temperature|
|G005|General| Provide feedback| Give the information to the person of its temperature situation against the referential|

## Low level

|Id|Category|Subject|Description|
|-|-|-|-|
|S001|Software| Detect person presence| Measure the distance of the nearest person in the range of 5cm to 2 meters|
|S002|Software| Detect person presence| Measure the time the person is in front of the sensor at a fixed distance and following this time value indicate the need to be closer, further or validate the person position|
|S003|Software| Detect person presence| Measure the time the person is in front of the sensor at a fixed distance and following this time value indicate the need to be closer|
|S004|Software| Detect person presence| Measure the time the person is in front of the sensor at a fixed distance and following this time value indicate the need to be further|
|S005|Software| Detect person presence| Measure the time the person is in front of the sensor at a fixed distance and following this time value validate the person position|
|S006|Software| Check temperature| Measure the temperature of the person (sampling TBD) |
|S007|Software| Check temperature| Compare the average of the sampling against a referential |
|S008|Software| Provide feedback| If the temperature average is < to limit A display a positive indicator|
|S009|Software| Provide feedback| If the temperature average is >= to limit A & < limit B display a warning indicator|
|S010|Software| Provide feedback| If the temperature average is >=  limit B display an alert indicator|
|S011|Software| Provide feedback| Indicate to go to the next person|
