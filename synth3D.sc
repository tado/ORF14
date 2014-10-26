(
SynthDef("simpleSine", {
	arg freq = 440, mul = 0, detune=1.01;
	var out;
	out = SinOsc.ar([freq, freq*detune], pi.rand2, mul);
	Out.ar(3, out);
}).store;

SynthDef("fx", {
	var in, out;
	in = In.ar(3, 2);
	out = LeakDC.ar(in);
	out = CompanderD.ar(out, out,
		thresh:0.1,
		slopeBelow: 1,
		slopeAbove: 0.1,
		clampTime: 0.01,
		relaxTime: 0.01,
		mul: 0.8);
	out = GVerb.ar(out);

	Out.ar(0, out);
}).store;
)