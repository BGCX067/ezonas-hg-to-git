class ai
{

	// concentration describes the mob ability to react to the situation, depending on what is happenning to him.
	// from lesser to greater
	enum concentration
	{
		distracted = -2,	// looking at something else: tv, birds, somebody else, etc
		tired = -1,			// sometimes, sleep deprivation makes the mob unable to concentrate, having "blanks".
		normal,				// plain normal (0)
		skeptical,			// has noticed something not long ago, and is trying to watch for anomalies
		dubious,			// worried about potential enemy presence
		cautious,			// after spotting an enemy, will look for intruders around him.
		alert				// knows where an intruder is, and is actively searching.
	};
	
	// this is assigned to a mob's target, (the player), and tells how much suspicious the target is.
	// from lesser to greater
	enum suspicion
	{
		distracting = -1,
		normal,
		noticed,
		suspicious,
		questionning,
		intruder
	};
	
	// Set those on the target itself
	enum clues
	{
		none,			// nothing special, everything normal
		armed,			// weapon is visible
		zone_uniform,	// dressed with an different uniform
		no_uniform,		// without a known uniform
		enemy_uniform,	// with an enemy uniform
		funny			// eg with a clown outfit or some distracting hat
	};

	// when evaluating an ID request
	enum id_evaluation
	{
		correct,	// passes
		okay,		// can be fake, but is okay
		suspicious,	// bad quality or unfit/invalid id, but the photo matches
		refused,	// bad id
		enemy		// was previously identified as a searched wanted target
	};
	
	
	
	
	
}