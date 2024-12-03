-- Exported by JKG Dialogue Creator

DLG.Name = "apathetic_stormie"
DLG.RootNode = "E1"
DLG.Nodes = {
	E1 = {
		Type = 1,
		SubNode = "T2",
		NextNode = "E28",
		HasCondition = false,
	},
	T2 = {
		Type = 2,
		SubNode = "O3",
		Text = "What do you want?",
		Duration = 3000,
		HasCondition = false,
		HasResolver = false,
	},
	O3 = {
		Type = 3,
		SubNode = "T6",
		NextNode = "O8",
		Text = "Why have you been staring out this window?",
		HasCondition = true,
		ConditionFunc = function(owner, ply, data)
			--[[-----------------------------------------------
				Conditional Script
			
				Available Variables:
				owner - Entity that runs this conversation
				ply - Player the owner is talking to
				data - Local storage table
			
				Wanted return value: Bool (true/false)
			--]]-----------------------------------------------
			owner.HasSpokenTo[ply:GetID()] = false
		end,
		HasResolver = false,
	},
	T6 = {
		Type = 2,
		SubNode = "O9",
		Text = "What's it to you?",
		Duration = 3000,
		HasCondition = false,
		HasResolver = false,
	},
	O9 = {
		Type = 3,
		SubNode = "T10",
		Text = "Could I help you?",
		HasCondition = false,
		HasResolver = false,
	},
	T10 = {
		Type = 2,
		SubNode = "O11",
		Text = "Probably not. ",
		Duration = 3000,
		HasCondition = false,
		HasResolver = false,
	},
	O11 = {
		Type = 3,
		SubNode = "T12",
		NextNode = "O14",
		Text = "Fine, good-bye.",
		HasCondition = false,
		HasResolver = false,
	},
	T12 = {
		Type = 2,
		SubNode = "S19",
		Text = "Mhm.",
		Duration = 3000,
		HasCondition = false,
		HasResolver = false,
	},
	S19 = {
		Type = 6,
		SubNode = "D26",
		ScriptFunc = function(owner, ply, data)
			--[[-----------------------------------------------
				Dialogue Script
			
				Available Variables:
				owner - Entity that runs this conversation
				ply	  - Player the owner is talking to
				data - Local storage table
			--]]-----------------------------------------------
			owner.HasSpokenTo[ply:GetID()] = true
		end,
		HasCondition = false,
	},
	D26 = {
		Type = 5,
	},
	O14 = {
		Type = 3,
		SubNode = "T15",
		Text = "You're clearly troubled.",
		HasCondition = false,
		HasResolver = false,
	},
	T15 = {
		Type = 2,
		SubNode = "T16",
		Text = "Aren't you, in a place like this?",
		Duration = 3000,
		HasCondition = false,
		HasResolver = false,
	},
	T16 = {
		Type = 2,
		SubNode = "T17",
		Text = "I mean, don't go spreading this around or anything.\nI just really hate it here, you know. I was swooned\nby those recruitment ads on Coruscant last year.",
		Duration = 4000,
		HasCondition = false,
		HasResolver = false,
	},
	T17 = {
		Type = 2,
		SubNode = "T32",
		Text = "You know, that big push they had to double their ranks.\nStrength in numbers, but what good is it when the\nindividual soldier feels like they're not trusted to shoot\nmore than a baby hive rat.",
		Duration = 3000,
		HasCondition = false,
		HasResolver = false,
	},
	T32 = {
		Type = 2,
		SubNode = "D34",
		Text = "Anyway, that's my story. Have a good one. Stay safe.",
		Duration = 2000,
		HasCondition = false,
		HasResolver = false,
	},
	D34 = {
		Type = 5,
	},
	O8 = {
		Type = 3,
		SubNode = "T18",
		NextNode = "O22",
		Text = "You're not helping our cause by window-shopping for rocks.",
		HasCondition = true,
		ConditionFunc = function(owner, ply, data)
			owner.HasSpokenTo[ply:GetID()] = false
		end,
		HasResolver = false,
	},
	T18 = {
		Type = 2,
		SubNode = "S20",
		Text = "You aren't helping your career much either.\nYou can bet I'm not voting for you when you\napply for lieutenant rank! ",
		Duration = 3000,
		HasCondition = false,
		HasResolver = false,
	},
	S20 = {
		Type = 6,
		SubNode = "D25",
		ScriptFunc = function(owner, ply, data)
			--[[-----------------------------------------------
				Dialogue Script
			
				Available Variables:
				owner - Entity that runs this conversation
				ply	  - Player the owner is talking to
				data - Local storage table
			--]]-----------------------------------------------
			owner.HasSpokenTo[ply:GetID()] = true
		end,
		HasCondition = false,
	},
	D25 = {
		Type = 5,
	},
	O22 = {
		Type = 3,
		SubNode = "T21",
		Text = "Just saying hi!",
		HasCondition = true,
		ConditionFunc = function(owner, ply, data)
			--[[-----------------------------------------------
				Conditional Script
			
				Available Variables:
				owner - Entity that runs this conversation
				ply - Player the owner is talking to
				data - Local storage table
			
				Wanted return value: Bool (true/false)
			--]]-----------------------------------------------
			owner.HasSpokenTo[ply:GetID()] = false
		end,
		HasResolver = false,
	},
	T21 = {
		Type = 2,
		SubNode = "D27",
		NextNode = "T29",
		Text = "Go away!",
		Duration = 2000,
		HasCondition = true,
		ConditionFunc = function(owner, ply, data)
			owner.HasSpokenTo[ply:GetID()] = true
		end,
		HasResolver = false,
	},
	D27 = {
		Type = 5,
	},
	T29 = {
		Type = 2,
		SubNode = "S30",
		Text = "Ok. Stay safe.",
		Duration = 3000,
		HasCondition = true,
		ConditionFunc = function(owner, ply, data)
			--[[-----------------------------------------------
				Conditional Script
			
				Available Variables:
				owner - Entity that runs this conversation
				ply - Player the owner is talking to
				data - Local storage table
			
				Wanted return value: Bool (true/false)
			--]]-----------------------------------------------
			owner.HasSpokenTo[ply:GetID()] = false
		end,
		HasResolver = false,
	},
	S30 = {
		Type = 6,
		SubNode = "D31",
		ScriptFunc = function(owner, ply, data)
			--[[-----------------------------------------------
				Dialogue Script
			
				Available Variables:
				owner - Entity that runs this conversation
				ply	  - Player the owner is talking to
				data - Local storage table
			--]]-----------------------------------------------
			owner.HasSpokenTo[ply:GetID()] = true
		end,
		HasCondition = false,
	},
	D31 = {
		Type = 5,
	},
	E28 = {
		Type = 1,
		SubNode = "L35",
		HasCondition = true,
		ConditionFunc = function(owner, ply, data)
			--[[-----------------------------------------------
				Conditional Script
			
				Available Variables:
				owner - Entity that runs this conversation
				ply - Player the owner is talking to
				data - Local storage table
			
				Wanted return value: Bool (true/false)
			--]]-----------------------------------------------
			owner.HasSpokenTo[ply:GetID()] = false
		end,
	},
	L35 = {
		Type = 4,
		Target = "T2",
	},
}
