--[[ ------------------------------------------------
	Jedi Knight Galaxies Lua Code
	Entity commands
	
	Written by BobaFett
--------------------------------------------------]]

local function ShowSpawnVars(ply, argc, argv)
	if ply.isLoggedIn ~= true then
		ply:SendPrint("^7System: ^1You are not logged in.")
		return
	end

	local rank = GetRank(ply)
	if rank["can-showspawnvars"] ~= true then
		ply:SendPrint("^7System: ^1You are not allowed to use this command")
		return
	end

	local ent
	if argc == 2 then
		ent = ents.GetByIndex(argv[1])
	else
		ent = ply:GetEyeTrace().Entity
	end
	if not ent or not ent:IsValid() then
		ply:SendPrint("No entity targetted")
		return
	end
	local SB = sys.CreateStringBuilder()
	SB:Append("Targetted: " .. tostring(ent) .. "\n\nSpawn vars:\n")
	if ent:HasSpawnVars() then
		local k,v
		for k,v in pairs(ent:GetSpawnVars()) do
			SB:Append(k .. " = " .. v .. "\n")
		end
	else
		SB:Append("^1Entity has no spawn vars\n")
	end
	ply:SendPrint(SB:ToString())
end

-- Replica of lugormod's delent~
local function delent(ply, argc, argv)
	if ply.isLoggedIn ~= true then
		ply:SendPrint("^7System: ^1You are not logged in.")
		return
	end

	local rank = GetRank(ply)
	if rank["can-delent"] ~= true then
		ply:SendPrint("^7System: ^1You are not allowed to use this command")
		return
	end

	local ent
	if argc < 2 then
		-- Minor improvement...let's delent what we're looking at --eez
		ent = ply:GetEyeTrace().Entity
		if ent == nil then
			ply:SendPrint("Usage: /delent <entity index> (use with caution)")
			return
		end
	else
		ent = ents.GetByIndex(argv[1])
	end

	if ent:IsPlayer() then
		ply:SendPrint("You cannot delete player entities")
		return
	end
	if ent:IsValid() then
		ply:SendPrint("Freeing entity " .. tostring(ent) .. "...")
		ent:Free()
	else
		ply:SendPrint("Specified entity does not exist")
	end
end

-- Replica of lugormod's place command
-- Syntax: /place <entity name> <distance from aimed surface (* for explicit origin)> [key,value,key,value etc..]
local function place(ply, argc, argv)
	if ply.isLoggedIn ~= true then
		ply:SendPrint("^7System: ^1You are not logged in.")
		return
	end

	local rank = GetRank(ply)
	if rank["can-place"] ~= true then
		ply:SendPrint("^7System: ^1You are not allowed to use this command")
		return
	end

	if argc < 2 then
		ply:SendPrint("Usage: /place <entity name> <distance (* for explicit origin)> [keys/values, separated by ,]")
		return
	end
	local entname = argv[1]
	local offset = argv[2]
	local entfact = ents.CreateEntityFactory(entname)
	if offset ~= "*" then
		-- Determine the spawn location
		local tr = ply:GetEyeTrace()
		local entpos = tr.EndPos + (tr.HitNormal * (tonumber(offset) or 0))
		entfact:SetSpawnVar("origin", string.format("%i %i %i", entpos.x, entpos.y, entpos.z))
	end
	local tokens = table.concat(argv," ",3, argc-1)
	if string.trim(tokens) ~= "" then
		local tokens = string.split(tokens,",")
		local tokencount = #tokens % 2
		if tokencount ~= 0 then
			ply:SendPrint("Invalid spawnvars provided, uneven count")
			return
		end
		local i = 1
		local k,v
		while (i <= #tokens) do
			k = string.trim(tokens[i])
			v = string.trim(tokens[i+1])
			entfact:SetSpawnVar(k,v)
			i = i + 2
		end
	end
	local ent = entfact:Create()
	if ent:IsValid() then
		ply:SendPrint("Entity spawned successfully: " .. tostring(ent))
	else
		ply:SendPrint("Failed to spawn entity")
	end
end

local function entcount(ply, argc, argv)
	if ply.isLoggedIn ~= true then
		ply:SendPrint("^7System: ^1You are not logged in.")
		return
	end

	local rank = GetRank(ply)
	if rank["can-entcount"] ~= true then
		ply:SendPrint("^7System: ^1You are not allowed to use this command")
		return
	end

	ply:SendPrint(string.format("Entity count - Normal: %i (%i slots allocated) / Logical: %i (%i slots allocated)", ents.EntCount(), ents.EntCountAllocated(), ents.LogicalEntCount(), ents.LogicalEntCountAllocated()))
end

local function rotate(ply, argc, argv)
	if ply.isLoggedIn ~= true then
		ply:SendPrint("^7System: ^1You are not logged in.")
		return
	end

	local rank = GetRank(ply)
	if rank["can-rotate"] ~= true then
		ply:SendPrint("^7System: ^1You are not allowed to use this command")
		return
	end

	if argc < 4 then
		-- We physically can NOT operate without pitch/yaw/roll
		ply:SendPrint("Usage: /bRotate <entity index> <Pitch> <Yaw> <Roll>")
		return
	end

	local ent
	if argc < 5 then
		ent = ply:GetEyeTrace().Entity
		if ent:IsValid() == false then
			ply:SendPrint("Usage: /bRotate <entity index> <Pitch> <Yaw> <Roll>")
			return
		end
	else
		ent = ents.GetByIndex(argv[1])
	end

	if ent:IsValid() then
		local angles
		if argc < 5 then
			angles = Vector(argv[1] .. " " .. argv[2] .. " " .. argv[3])
		else
			angles = Vector(argv[2] .. " " .. argv[3] .. " " .. argv[4])
		end

		ent:Rotate( angles, 5000 )
	else
		ply:SendPrint("Specified ent is invalid.")
	end
end

local function InitEntCmds()
	cmds.Add("entcount", entcount)
	cmds.Add("place", place)
	cmds.Add("delent", delent)
	cmds.Add("showspawnvars", ShowSpawnVars)
	cmds.Add("rotate", rotate)

	cmds.Add("bEntCount", entcount)
	cmds.Add("bPlace", place)
	cmds.Add("bDelent", delent)
	cmds.Add("bShowSpawnVars", ShowSpawnVars)
	cmds.Add("bRotate", rotate)

	chatcmds.Add("entcount", entcount)
	chatcmds.Add("place", place)
	chatcmds.Add("delent", delent)
	chatcmds.Add("showspawnvars", ShowSpawnVars)
	chatcmds.Add("rotate", rotate)

	chatcmds.Add("bEntCount", entcount)
	chatcmds.Add("bPlace", place)
	chatcmds.Add("bDelent", delent)
	chatcmds.Add("bShowSpawnVars", ShowSpawnVars)
	chatcmds.Add("bRotate", rotate)
end

InitEntCmds()