2022. 05. 24 written by Namhoon Jang

 --- Desinged for OctoPrint server OS ---

Updated functionalities

1. Custom M-codes

1.1 M130:
	M130 V for Vaccum ON
	M130 D for Door Switch ON
	M130 L for Light ON
	M130 R for LED Red Light ON
	M130 G for LED Green Light ON
	M130 B for LED Blue Light ON

1.2 M131:
	M130 V for Vaccum OFF
	M130 D for Door Switch OFF
	M130 L for Light OFF
	M130 R for LED Red Light OFF
	M130 G for LED Green Light OFF
	M130 B for LED Blue Light OFF

1.3 M132:
	Z-probing function for measuring the two extruder nozzle's height difference
	Probe Tool 0 first, and probe Tool 1 next.

1.4 M133:
	Calibrate the two nozzle by the calculated difference on M133 code

1.5 M134: 
	Set the Tool 1 on Home position.

1.6 M135:
	Temperature annealing for the printed parts.
	Proper use by three parameters: S, P, T
	* S: Target temperature for heating 2(or more/less) hours. Units are seconds.
     	* P: Post-Processing time for Target temperature(Parameter S).
     	* T: Decreasing ratio for Target temperature to Room termperature.

1.7 M136:
	Just for testing. 
	Use for testing other customized M codes.
