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
	in = GVerb.ar(in, 100, 1, drylevel:0.5);
	out = (in*0.75).softclip;
	Out.ar(0, out);
}).store;
)



//a = Synth("simpleSine");