(
SynthDef("simpleSine", {
	arg freq = 440, mul = 0, detune=1.01;
	var out;
	out = SinOsc.ar([freq, freq*detune], pi.rand2, mul);
	Out.ar(3, out);
}).store;

SynthDef("fx", {
	var out;
	out = In.ar(3, 2);
	//2.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 1.0) });
	//8.do { out = AllpassL.ar(out, 0.04, 0.04.rand, 2) };
	out = LeakDC.ar(out);
	out = CompanderD.ar(out, out,
		thresh:0.1,
		slopeBelow: 1,
		slopeAbove: 0.1,
		clampTime: 0.01,
		relaxTime: 0.01,
		mul: 1.0);
	out = GVerb.ar(out,roomsize: 99, revtime: 1);

	Out.ar(0, out);
}).store;
)