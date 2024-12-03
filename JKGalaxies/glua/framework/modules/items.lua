--[[ ------------------------------------------------
	Jedi Knight Galaxies Lua Framework
	Items Module
	
	DO NOT MODIFY THIS FILE
	
	This module handles everything related to items.
--------------------------------------------------]]

-- Start the hook module, all subsequent functions are variables, are stored within the hook. table, and access to the global environment is gone
module("items")

local ConsumableFunctions = {}

function GetConsumableFunctions()
	return ConsumableFunctions
end

--[[----------------------------------------------------------------------------------------
	items.AddConsumableFunction
	
	Adds a new named consumable item function.
-------------------------------------------------------------------------------------------]]
function AddConsumableFunction(consume_name, consume_func)
	ConsumableFunctions[consume_name] = consume_func
end


--[[----------------------------------------------------------------------------------------
	items.RemoveConsumableFunction
	
	Remove a previously registered consumable function.
-------------------------------------------------------------------------------------------]]
function RemoveConsumableFunction(consume_name)
	ConsumableFunctions[consume_name] = nil
end


--[[----------------------------------------------------------------------------------------
	items.ConsumeItem (Internal function)
	
	This function is called by the engine when an item is consumed.
	Do not call this from a script unless you have a very good reason to do so.
-------------------------------------------------------------------------------------------]]
function ConsumeItem(ply, consumeFuncName, quantity)
	local func = ConsumableFunctions[consumeFuncName]

	if ply.Health <= 0 then
		return
	end

	func(ply, quantity)
end