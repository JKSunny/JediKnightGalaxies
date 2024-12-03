-- Exported by JKG Dialogue Creator

DLG.Name = "medical_droid_dlg"
DLG.RootNode = "E1"
DLG.Nodes = {
	E1 = {
		Type = 1,
		SubNode = "S4",
		HasCondition = false,
	},
	S4 = {
		Type = 6,
		NextNode = "T2",
		ScriptFunc = function(owner, ply, data)
			if ply.Health < ply.MaxHealth
			then
			ply.IsHurt = true
			end
			
		end,
		HasCondition = false,
	},
	T2 = {
		Type = 2,
		SubNode = "O3",
		NextNode = "T5",
		Text = "Hello, can I offer you a bacta treatment for your wounds?",
		Duration = 5000,
		HasCondition = true,
		ConditionFunc = function(owner, ply, data)
			return ply.IsHurt ~= true
		end,
		HasResolver = false,
	},
	O3 = {
		Type = 3,
		SubNode = "S11",
		NextNode = "O7",
		Text = "Yes, please!",
		HasCondition = false,
		HasResolver = false,
	},
	S11 = {
		Type = 6,
		NextNode = "T10",
		ScriptFunc = function(owner, ply, data)
			ply.Health = ply.MaxHealth
		end,
		HasCondition = false,
	},
	T10 = {
		Type = 2,
		SubNode = "D12",
		Text = "Excellent!",
		Duration = 2500,
		HasCondition = false,
		HasResolver = false,
	},
	D12 = {
		Type = 5,
	},
	O7 = {
		Type = 3,
		SubNode = "T8",
		Text = "No, thanks.",
		HasCondition = false,
		HasResolver = false,
	},
	T8 = {
		Type = 2,
		SubNode = "D9",
		Text = "I hate to see you injured, sir, but, if you insist...",
		Duration = 4500,
		HasCondition = false,
		HasResolver = false,
	},
	D9 = {
		Type = 5,
	},
	T5 = {
		Type = 2,
		SubNode = "D6",
		Text = "It's good to see that you are in top shape! My assistance is available should you need it in the future!",
		Duration = 3000,
		HasCondition = false,
		HasResolver = false,
	},
	D6 = {
		Type = 5,
	},
}
