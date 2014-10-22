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
	in = GVerb.ar(in, roomsize: 80, revtime: 1);
	out = LeakDC.ar(in);
	Out.ar(0, out);
}).store;
)



//a = Synth("simpleSine");